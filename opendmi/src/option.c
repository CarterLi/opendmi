//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <opendmi/option.h>
#include <opendmi/command.h>
#include <opendmi/tty.h>

static bool dmi_option_toggle(
        dmi_context_t      *context,
        const dmi_option_t *option);

static bool dmi_option_set(
        dmi_context_t      *context,
        const dmi_option_t *option,
        const char         *value);

void dmi_option_list(const dmi_option_set_t *set)
{
    const dmi_option_t *option;
    const dmi_argument_t *arg;

    assert(set != nullptr);

    for (option = set->options; option->short_names || option->long_names; option++) {
        arg = &option->argument;

        if (option->flags & DMI_OPTION_FLAG_HIDDEN)
            continue;

        int count = 0;

        if (option->short_names != nullptr) {
            const char *name = option->short_names;

            while (*name != 0) {
                printf("%s", count > 0 ? ", " : "    ");

                dmi_tty_cprintf(DMI_TTY_COLOR_AQUA, "-%c", *name);
                if (arg->type != DMI_ARGUMENT_TYPE_NONE) {
                    printf(arg->required ? " " : " [");
                    dmi_tty_cprintf(DMI_TTY_COLOR_LIME, "<%s>", arg->name);
                    printf(arg->required ? "" : "]");
                }
                name++, count++;
            }
        }

        if (option->long_names != nullptr) {
            const char **name = option->long_names;

            while (*name != nullptr) {
                printf("%s", count > 0 ? ", " : "    ");

                dmi_tty_cprintf(DMI_TTY_COLOR_AQUA, "--%s", *name);
                if (arg->type != DMI_ARGUMENT_TYPE_NONE) {
                    printf(arg->required ? "=" : "[=");
                    dmi_tty_cprintf(DMI_TTY_COLOR_LIME, "<%s>", arg->name);
                    printf(arg->required ? "" : "]");
                }
                name++, count++;
            }
        }

        dmi_tty_cprintf(DMI_TTY_COLOR_WHITE, "\n%8s%s\n", "", option->description);
    }
}

const dmi_option_t *dmi_option_find_short(const dmi_option_set_t *set, char name)
{
    const dmi_option_t *option;

    assert(set != nullptr);
    assert(name != 0);

    for (option = set->options; option->short_names || option->long_names; option++) {
        if (!option->short_names)
            continue;

        for (const char *item = option->short_names; *item != 0; item++) {
            if (name == *item)
                return option;
        }
    }

    return nullptr;
}

const dmi_option_t *dmi_option_find_short_ex(const dmi_option_set_t **options, char name)
{
    const dmi_option_t *option;

    assert(options != nullptr);
    assert(name != 0);

    while (*options) {
        option = dmi_option_find_short(*options, name);
        if (option != nullptr)
            return option;

        options++;
    }

    return nullptr;
}

const dmi_option_t *dmi_option_find_long(const dmi_option_set_t *set, const char *name)
{
    const dmi_option_t *option;

    assert(set != nullptr);
    assert(name != nullptr);

    for (option = set->options; option->short_names || option->long_names; option++) {
        if (!option->short_names)
            continue;

        for (const char **item = option->long_names; *item != nullptr; item++) {
            if (strcmp(name, *item) == 0)
                return option;
        }
    }

    return nullptr;
}

const dmi_option_t *dmi_option_find_long_ex(const dmi_option_set_t **options, const char *name)
{
    const dmi_option_t *option;

    assert(options != nullptr);
    assert(name != 0);

    while (*options) {
        option = dmi_option_find_long(*options, name);
        if (option != nullptr)
            return option;

        options++;
    }

    return nullptr;
}

int dmi_option_parse(
        dmi_context_t           *context,
        const dmi_option_set_t **options,
        int                      argc,
        char                    *argv[])
{
    int count = 0;
    const dmi_option_t *option;

    while (argc > 0) {
        char *arg = *argv;
        char *value = nullptr;

        if (*arg++ != '-')
            break;

        argc--, argv++;

        if (*arg == '-') {
            arg++;

            if (*arg == 0) {
                count++;
                break;
            }

            value = strchr(arg, '=');
            if (value != nullptr)
                *value++ = 0;

            option = dmi_option_find_long_ex(options, arg);
            if (option == nullptr) {
                dmi_command_message("Unknown option: --%s\n", arg);
                return -1;
            }

            if (option->argument.type == DMI_ARGUMENT_TYPE_NONE) {
                if (value != nullptr) {
                    dmi_command_message("Option --%s doesn't have arguments\n", arg);
                    return -1;
                }

                if (not dmi_option_toggle(context, option))
                    return false;
            } else if (option->argument.required) {
                if (value == nullptr) {
                    if ((argc == 0) or (*argv[0] == '-')) {
                        dmi_command_message("Option --%s requires an argument\n", arg);
                        return -1;
                    }

                    value = *argv;
                    argc--, argv++, count++;
                }

                if (not dmi_option_set(context, option, value))
                    return -1;
            } else {
                if ((value == nullptr) and (argc > 0) and (*argv[0] != '-')) {
                    value = *argv;
                    argc--, argv++, count++;
                }

                if (not dmi_option_set(context, option, value))
                    return -1;
            }

            count++;
        } else {
            while (*arg != 0) {
                char flag = *arg;
    
                value = nullptr;

                option = dmi_option_find_short_ex(options, flag);
                if (option == nullptr) {
                    dmi_command_message("Unknown option: -%c\n", flag);
                    return -1;
                }

                if (option->argument.type == DMI_ARGUMENT_TYPE_NONE) {
                    if (not dmi_option_toggle(context, option))
                        return false;

                    arg++, count++;
                } else if (option->argument.required) {
                    arg++;

                    if (*arg == 0) {
                        if ((argc == 0) or (*argv[0] == '-')) {
                            dmi_command_message("Option -%c requires an argument\n", flag);
                            return -1;
                        }

                        value = *argv;
                        argc--, argv++;
                    } else {
                        value = arg;
                    }

                    if (not dmi_option_set(context, option, value))
                        return -1;

                    count++;
                    break;
                } else {
                    if (*arg != 0) {
                        value = arg;
                    } else if ((argc > 0) and (*argv[0] != '-')) {
                        value = *argv;
                        argc--, argv++;
                    }

                    if (not dmi_option_set(context, option, value))
                        return -1;

                    count++;
                    break;
                }  
            }
        }
    }

    return count;
}

static bool dmi_option_toggle(
        dmi_context_t      *context,
        const dmi_option_t *option)
{
    assert(context != nullptr);
    assert(option != nullptr);

    if (option->handler != nullptr)
        return option->handler(context, nullptr);

    bool *flag = dmi_cast(flag, option->value);
    if (option->flags & DMI_OPTION_FLAG_REVERSE)
        *flag = false;
    else
        *flag = true;

    return true;
}

static bool dmi_option_set(
        dmi_context_t      *context,
        const dmi_option_t *option,
        const char         *value)
{
    assert(context != nullptr);
    assert(option != nullptr);

    if (option->handler != nullptr)
        return option->handler(context, value);

    switch (option->argument.type) {
    case DMI_ARGUMENT_TYPE_STRING:
        *((const char **)option->value) = value;
        break;

    default:
        assert(false);
    }

    return true;
}
