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
#include <opendmi/types.h>

static void dmi_option_toggle(const dmi_option_t *opt);
static bool dmi_option_set(const dmi_option_t *opt, const char *value);

void dmi_option_list(const dmi_option_group_t *group)
{
    const dmi_option_t *opt;
    const dmi_argument_t *arg;

    assert(group != nullptr);

    printf("%s:\n", group->name);

    for (opt = group->options; opt->short_names || opt->long_names; opt++) {
        arg = &opt->argument;

        if (opt->flags & DMI_OPTION_FLAG_HIDDEN)
            continue;

        int count = 0;

        if (opt->short_names != nullptr) {
            const char *name = opt->short_names;

            while (*name != 0) {
                printf("%s-%c", count > 0 ? ", " : "    ", *name);
                if (arg->type != DMI_ARGUMENT_TYPE_NONE)
                    printf(arg->required ? " <%s>" : " [%s]", arg->name);
                name++, count++;
            }
        }

        if (opt->long_names != nullptr) {
            const char **name = opt->long_names;

            while (*name != nullptr) {
                printf("%s--%s", count > 0 ? ", " : "    ", *name);
                if (arg->type != DMI_ARGUMENT_TYPE_NONE)
                    printf(arg->required ? "=<%s>" : "[=<%s>]", arg->name);
                name++, count++;
            }
        }

        printf("\n%8s%s\n", "", opt->description);
    }

    printf("\n");
}

const dmi_option_t *dmi_option_find_short(const dmi_option_group_t *group, char name)
{
    const dmi_option_t *opt;

    assert(group != nullptr);
    assert(name != 0);

    for (opt = group->options; opt->short_names || opt->long_names; opt++) {
        if (!opt->short_names)
            continue;

        for (const char *item = opt->short_names; *item != 0; item++) {
            if (name == *item)
                return opt;
        }
    }

    return nullptr;
}

const dmi_option_t *dmi_option_find_long(const dmi_option_group_t *group, const char *name)
{
    const dmi_option_t *opt;

    assert(group != nullptr);
    assert(name != nullptr);

    for (opt = group->options; opt->short_names || opt->long_names; opt++) {
        if (!opt->short_names)
            continue;

        for (const char **item = opt->long_names; *item != nullptr; item++) {
            if (strcmp(name, *item) == 0)
                return opt;
        }
    }

    return nullptr;
}

int dmi_option_parse(const dmi_option_group_t *group, int argc, char *argv[])
{
    int count = 0;
    const dmi_option_t *opt;

    while (argc > 0) {
        char *arg = *argv;
        char *value = nullptr;

        if (*arg++ != '-')
            break;

        argc--, argv++;

        if (*arg == '-') {
            arg++;

            if (*arg == 0)
                break;

            value = strchr(arg, '=');
            if (value != nullptr)
                *value++ = 0;

            opt = dmi_option_find_long(group, arg);
            if (opt == nullptr) {
                fprintf(stderr, "Unknown option: --%s\n", arg);
                return -1;
            }

            if (opt->argument.type == DMI_ARGUMENT_TYPE_NONE) {
                if (value != nullptr) {
                    fprintf(stderr, "Option --%s doesn't have arguments\n", arg);
                    return -1;
                }

                dmi_option_toggle(opt);
            } else if (opt->argument.required) {
                if (value == nullptr) {
                    if ((argc == 0) or (*argv[0] == '-')) {
                        fprintf(stderr, "Option --%s requires an argument\n", arg);
                        return -1;
                    }

                    value = *argv;
                    argc--, argv++;

                    if (not dmi_option_set(opt, value))
                        return false;
                }
            } else {
                if ((value == nullptr) and (argc > 0) and (*argv[0] != '-')) {
                    value = *argv;
                    argc--, argv++;
                }

                if (not dmi_option_set(opt, value))
                        return false;
            }

            count++;
        } else {
            while (*arg != 0) {
                char flag = *arg;
    
                value = nullptr;

                opt = dmi_option_find_short(group, flag);
                if (opt == nullptr) {
                    fprintf(stderr, "Unknown option: -%c\n", flag);
                    return -1;
                }

                if (opt->argument.type == DMI_ARGUMENT_TYPE_NONE) {
                    dmi_option_toggle(opt);
                    arg++, count++;
                } else if (opt->argument.required) {
                    arg++;

                    if (*arg == 0) {
                        if ((argc == 0) or (*argv[0] == '-')) {
                            fprintf(stderr, "Option -%c requires an argument\n", flag);
                            return -1;
                        }

                        value = *argv;
                        argc--, argv++;
                    } else {
                        value = arg;
                    }

                    if (not dmi_option_set(opt, value))
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

                    if (not dmi_option_set(opt, value))
                        return -1;

                    count++;
                    break;
                }  
            }
        }
    }

    return count;
}

static void dmi_option_toggle(const dmi_option_t *opt)
{
    assert(opt != nullptr);

    bool *flag = dmi_cast(flag, opt->value);
    if (opt->flags & DMI_OPTION_FLAG_REVERSE)
        *flag = false;
    else
        *flag = true;
}

static bool dmi_option_set(const dmi_option_t *opt, const char *value)
{
    assert(opt != nullptr);

    switch (opt->argument.type) {
    case DMI_ARGUMENT_TYPE_STRING:
        *((const char **)opt->value) = value;
        break;

    default:
        assert(false);
    }

    return true;
}
