//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "config.h"

#ifdef HAVE_UNISTD_H
#   include <unistd.h>
#endif // HAVE_UNISTD_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <libgen.h>
#include <getopt.h>
#include <errno.h>
#include <assert.h>

#include <opendmi/context.h>
#include <opendmi/command.h>
#include <opendmi/pager.h>
#include <opendmi/entity.h>
#include <opendmi/filter.h>
#include <opendmi/format.h>
#include <opendmi/format/text.h>
#include <opendmi/tty.h>

/**
 * @brief Command line usage error.
 * 
 * @note Status `2` is what command line utilities actually return when
 * called improperly. The `EX_USAGE`status from `<sysexits.h>` doesn't
 * reflect reality and common practice.
 */
#define EXIT_USAGE 2

typedef enum dmi_command_type
{
    DMI_COMMAND_DUMP_TABLE,
    DMI_COMMAND_LIST_KEYWORDS,
    DMI_COMMAND_LIST_TYPES,
    DMI_COMMAND_LIST_ENTITIES
} dmi_command_type_t;

typedef struct dmi_config
{
    dmi_command_type_t command;
    bool show_version;
    bool show_help;
    char *log_file;
    char *memory_device;
    bool quiet;
    bool debug;
    bool link;
    bool dump;
    char *input_path;
    char *output_path;
    const dmi_format_t *output_format;
    dmi_filter_t filter;
} dmi_config_t;

static bool parse_args(dmi_context_t *context, int argc, char *argv[], int *rv);
static dmi_handle_t parse_handle(const char *str);
static dmi_type_t parse_type(dmi_context_t *context, const char *str);

static void show_version(void);
static void show_usage(const char *proc);

static bool list_keywords(dmi_context_t *context);
static bool list_types(dmi_context_t *context);
static bool list_entities(dmi_context_t *context);

static void print_all(dmi_context_t *context, const dmi_format_t *format);
static void print_entity(const dmi_format_t *format, const dmi_entity_t *entity, void *session);

static void log_error(
        dmi_context_t   *context,
        dmi_log_level_t  level,
        const char      *format,
        va_list          args);

dmi_config_t config =
{
    .command       = DMI_COMMAND_DUMP_TABLE,
    .memory_device = nullptr,
    .quiet         = false,
    .debug         = false,
    .link          = false,
    .dump          = false,
    .input_path    = nullptr,
    .output_path   = nullptr,
    .output_format = &dmi_text_format,
    .filter        = {}
};

const dmi_option_group_t global_opts =
{
    .name    = "Global options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "v",
            .long_names  = (const char *[]){ "version", nullptr },
            .description = "Print version information and exit",
            .value       = &config.show_version
        },
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &config.show_help
        },
        {
            .short_names = "q",
            .long_names  = (const char *[]){ "quiet", nullptr },
            .description = "Less verbose output",
            .value       = &config.quiet
        },
        {
            .short_names = "g",
            .long_names  = (const char *[]){ "debug", nullptr },
            .description = "Turn on debug logging",
            .value       = &config.debug
        },
        {
            .short_names = "l",
            .long_names  = (const char *[]){ "log", nullptr },
            .description = "Write log to file",
            .value       = &config.log_file,
            .argument    = {
                .name     = "path",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "S",
            .long_names  = (const char *[]){ "no-sysfs", nullptr },
            .description = "Do not attempt to read DMI data from SysFS"
        },
        {
            .short_names = "d",
            .long_names  = (const char *[]){ "device", nullptr },
            .description = "Set path to memory device (default: /dev/mem)",
            .value       = &config.memory_device,
            .argument    = {
                .name     = "path",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            },
        },
        {
            .short_names = "i",
            .long_names  = (const char *[]){ "file", nullptr },
            .description = "Read the DMI data from a binary file",
            .value       = &config.output_path,
            .argument    = {
                .name     = "path",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "m",
            .long_names  = (const char *[]){ "module", nullptr },
            .description = "Load specified module",
            .argument    = {
                .name     = "module",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {}
    }
};

int main(int argc, char *argv[])
{
    dmi_context_t *context;
    bool status = false;

    // Initialize terminal
    dmi_tty_init();

    // Create DMI context
    context = dmi_create(DMI_CONTEXT_FLAG_RELAXED);
    if (context == nullptr) {
        fprintf(stderr, "Unable to create DMI context\n");
        return EXIT_FAILURE;
    }

    int rv = EXIT_SUCCESS;
    if (not parse_args(context, argc, argv, &rv))
        return rv;

    argc -= optind;
    argv += optind;

    // Initialize logging
    dmi_set_logger(context, log_error);
    if (config.quiet)
        dmi_set_log_level(context, DMI_LOG_WARNING);
    else if (config.debug)
        dmi_set_log_level(context, DMI_LOG_DEBUG);

    if (config.link)
        dmi_set_flags(context, DMI_CONTEXT_FLAG_LINK);

    do {
        if (isatty(STDOUT_FILENO) and (config.output_path == nullptr)) {
            if (not dmi_pager_start(context))
                break;
        }

        if (config.command == DMI_COMMAND_LIST_KEYWORDS) {
            status = list_keywords(context);
            break;
        }

        if (config.command == DMI_COMMAND_LIST_TYPES) {
            status = list_types(context);
            break;
        }

        if (config.input_path != nullptr)
            status = dmi_dump_load(context, config.input_path);
        else
            status = dmi_open(context);

        if (not status)
            break;

        if (config.command == DMI_COMMAND_LIST_ENTITIES) {
            list_entities(context);
            break;
        }

        if (config.output_path != nullptr) {
            status = dmi_dump_save(context, config.output_path, false);
            if (not status)
                break;
        } else {
            print_all(context, config.output_format);
        }

        status = true;
    } while (false);

    // Close DMI context
    dmi_destroy(context);

    return status ? EXIT_SUCCESS : EXIT_FAILURE;
}

static bool parse_args(dmi_context_t *context, int argc, char *argv[], int *rv)
{
    static struct option long_options[] =
    {
        { "dev-mem",   required_argument, nullptr, 'd' },
        { "debug",     no_argument,       nullptr, 'g' },
        { "quiet",     no_argument,       nullptr, 'q' },
        { "link",      no_argument,       nullptr, 'L' },
        { "string",    optional_argument, nullptr, 's' },
        { "type",      optional_argument, nullptr, 't' },
        { "list",      no_argument,       nullptr, 'l' },
        { "handle",    required_argument, nullptr, 'H' },
        { "dump",      no_argument,       nullptr, 'u' },
        { "dump-bin",  required_argument, nullptr, 'o' },
        { "format",    required_argument, nullptr, 'f' },
        { "from-dump", required_argument, nullptr, 'i' },
        { "help",      no_argument,       nullptr, 'h' },
        { "version",   no_argument,       nullptr, 'v' }
    };

    const char *proc = basename(argv[0]);

    while (true) {
        int idx = 0;
        int opt = getopt_long(argc, argv, "d:qLs?tl?H:uo:i:hv", long_options, &idx);

        if (opt < 0)
            break;

        switch (opt) {
        case 'd':
            config.memory_device = optarg;
            break;

        case 'q':
            config.quiet = true;
            break;

        case 'g':
            config.debug = true;
            break;

        case 'L':
            config.link = true;
            break;

        case 's':
            if (optarg == nullptr)
                config.command = DMI_COMMAND_LIST_KEYWORDS;
            break;

        case 't':
            if (optarg == nullptr) {
                config.command = DMI_COMMAND_LIST_TYPES;
                break;
            }

            dmi_type_t type = parse_type(context, optarg);
            if (type == DMI_TYPE_INVALID) {
                *rv = EXIT_USAGE;
                return false;
            }
            if (not dmi_filter_add_type(&config.filter, type)) {
                *rv = EXIT_USAGE;
                return false;
            }
            break;

        case 'l':
            config.command = DMI_COMMAND_LIST_ENTITIES;
            break;

        case 'H':
            dmi_handle_t handle = parse_handle(optarg);
            if (handle == DMI_HANDLE_INVALID) {
                *rv = EXIT_USAGE;
                return false;
            }
            if (not dmi_filter_add_handle(&config.filter, handle)) {
                *rv = EXIT_USAGE;
                return false;
            }
            break;

        case 'u':
            config.dump = true;
            break;

        case 'o':
            config.output_path = optarg;
            break;

        case 'i':
            config.input_path = optarg;
            break;

        case 'f':
            config.output_format = dmi_format_get(optarg);
            if (config.output_format == nullptr) {
                *rv = EXIT_USAGE;
                fprintf(stderr, "%s: Invalid output format: %s", proc, optarg);
                return false;
            }
            break;

        case 'v':
            show_version();
            return false;

        case 'h':
            show_usage(proc);
            return false;

        default:
            *rv = EXIT_USAGE;
            return false;
        }
    }

    return true;
}

static dmi_handle_t parse_handle(const char *str)
{
    char *ep;
    unsigned long value;

    errno = 0;
    value = strtoul(str, &ep, 16);

    if ((*str == 0) or (*ep != 0)) {
        fprintf(stderr, "Invalid handle value: %s\n", str);
        return DMI_HANDLE_INVALID;
    }
    if (((errno == ERANGE) and (value == ULONG_MAX)) or (value >= DMI_HANDLE_INVALID)) {
        fprintf(stderr, "Handle is out of range: %s\n", str);
        return DMI_HANDLE_INVALID;
    }

    return (dmi_handle_t)value;
}

static dmi_type_t parse_type(dmi_context_t *context, const char *str)
{
    char *ep;
    long value;

    if (*str == 0) {
        fprintf(stderr, "Empty type value: %s\n", str);
        return DMI_TYPE_INVALID;
    }
    if ((*str == '+') or (*str == '-')) {
        fprintf(stderr, "Invalid type value: %s\n", str);
        return DMI_TYPE_INVALID;
    }

    errno = 0;
    value = strtol(str, &ep, 10);

    if (*ep != 0) {
        value = dmi_type_find(context, str);
        if (value == DMI_TYPE_INVALID)
            fprintf(stderr, "Unknown type code: %s\n", str);

        return value;
    }

    if (((errno == ERANGE) and ((value == LONG_MIN) or (value == LONG_MAX))) or
        (value < 0) or (value > DMI_TYPE_MAX))
    {
        fprintf(stderr, "Type is out of range: %s\n", str);
        return DMI_TYPE_INVALID;
    }

    return (dmi_type_t)value;
}

static void show_version(void)
{
    dmi_tty_header("OpenDMI Framework, version %s", OPENDMI_VERSION);

    dmi_tty_cprintf(DMI_TTY_COLOR_GREY, "Copyright (c) 2025-2026, The OpenDMI contributors\n");
    dmi_tty_cprintf(DMI_TTY_COLOR_GREY, "Licensed under the BSD 3-Clause License\n\n");
}

static void show_usage(const char *proc)
{
    show_version();

    dmi_tty_header("Usage:");

    printf("    %s [global options] <command> [command options] [--] [command args]\n\n", proc);

    dmi_command_list();
    dmi_option_list(&global_opts);

    printf("Use %s <command> --help for more information\n\n", proc);
}

static bool list_keywords(dmi_context_t *context)
{
    dmi_unused(context);

    return true;
}

static bool list_types(dmi_context_t *context)
{
    const char *format;

    if (isatty(STDIN_FILENO))
        format = "%3d %-24s %s\n";
    else
        format = "%d\t%s\t%s\n";

    for (size_t type = 0; type < 0x100; type++) {
        const dmi_entity_spec_t *spec = dmi_type_spec(context, (dmi_type_t)type);

        if (spec == nullptr)
            continue;

        printf(format, (int)spec->type, spec->code, spec->name);
    }

    return true;
}

static bool list_entities(dmi_context_t *context)
{
    dmi_registry_iter_t iter;
    dmi_entity_t *entity;

    dmi_registry_iter_init(&iter, context->registry, &config.filter);
    while ((entity = dmi_registry_iter_next(&iter)) != nullptr) {
        printf("0x%04hX %-3u %s\n", entity->handle, entity->type, dmi_entity_name(entity));
    }

    return true;
}

static void print_all(dmi_context_t *context, const dmi_format_t *format)
{
    void *session;
    dmi_registry_iter_t iter;
    dmi_entity_t *entity;

    session = format->handlers.initialize(context, stdout);
    if (not session)
        return;

    if (format->handlers.dump_start != nullptr)
        format->handlers.dump_start(session);

    format->handlers.entry(session);

    if (format->handlers.table_start != nullptr)
        format->handlers.table_start(session);

    dmi_registry_iter_init(&iter, context->registry, &config.filter);
    while ((entity = dmi_registry_iter_next(&iter)) != nullptr) {
        print_entity(format, entity, session);
    }

    if (format->handlers.table_end != nullptr)
        format->handlers.table_end(session);

    if (format->handlers.dump_end != nullptr)
        format->handlers.dump_end(session);

    format->handlers.finalize(session);
}

static void print_entity(
        const dmi_format_t *format,
        const dmi_entity_t *entity,
        void               *session)
{
    assert(format != nullptr);
    assert(entity != nullptr);
    assert(session != nullptr);

    const dmi_entity_spec_t *spec = entity->spec;
    const dmi_attribute_t   *attr = nullptr;

    format->handlers.entity_start(session, entity);

    if (entity->info and not config.dump) {
        if (format->handlers.entity_attrs_start != nullptr)
            format->handlers.entity_attrs_start(session, entity);

        for (attr = spec->attributes; attr->params.name; attr++) {
            const dmi_data_t *value = dmi_member_ptr(entity->info, attr->value, dmi_data_t);

            // Check attribute level
            if (attr->params.level != DMI_VERSION_NONE) {
                if (entity->level < attr->params.level)
                    continue;
            }

            format->handlers.entity_attr(session, entity, attr, value);
        }

        if (format->handlers.entity_attrs_end != nullptr)
            format->handlers.entity_attrs_end(session, entity);
    } else if (entity->type != DMI_TYPE_END_OF_TABLE) {
        format->handlers.entity_data(session, entity);
        format->handlers.entity_strings(session, entity);
    }

    format->handlers.entity_end(session, entity);
}

static void log_error(
        dmi_context_t   *context __attribute__((unused)),
        dmi_log_level_t  level,
        const char      *format,
        va_list          args)
{
    FILE *out = stderr;

    if (dmi_has_tty())
        out = stdout;

    switch (level) {
    case DMI_LOG_DEBUG:
        dmi_tty_set_fg_color(8);
        break;

    case DMI_LOG_INFO:
        dmi_tty_set_fg_color(DMI_TTY_COLOR_GREEN);
        break;

    case DMI_LOG_NOTICE:
        dmi_tty_set_fg_color(DMI_TTY_COLOR_TEAL);
        break;

    case DMI_LOG_WARNING:
        dmi_tty_set_fg_color(DMI_TTY_COLOR_YELLOW);
        break;

    case DMI_LOG_ERROR:
        dmi_tty_set_fg_color(DMI_TTY_COLOR_RED);
        break;

    default:
        // fallthrough
    }

    fprintf(out, "[%s] ", dmi_log_level_name(level));

    dmi_tty_exit_attr_mode();

    vfprintf(out, format, args);
    fprintf(out, "\n");
}
