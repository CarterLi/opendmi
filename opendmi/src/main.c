//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
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
#include <limits.h>
#include <libgen.h>
#include <getopt.h>

#ifdef ENABLE_CURSES
#   if defined(CURSES_HAVE_NCURSES_NCURSES_H)
#       include <ncurses/ncurses.h>
#   elif defined(CURSES_HAVE_NCURSES_CURSES_H)
#       include <ncurses/curses.h>
#   elif defined(CURSES_HAVE_NCURSES_H)
#       include <ncurses.h>
#   elif defined(CURSES_HAVE_CURSES_H)
#       include <curses.h>
#   endif
#   include <term.h>
#endif // ENABLE_CURSES

#include <opendmi/context.h>
#include <opendmi/format.h>
#include <opendmi/table.h>
#include <opendmi/format/text.h>

typedef enum dmi_command
{
    DMI_COMMAND_DUMP_TABLES,
    DMI_COMMAND_LIST_KEYWORDS,
    DMI_COMMAND_LIST_TYPES
} dmi_command_t;

typedef struct dmi_config
{
    dmi_command_t command;
    char *memory_device;
    bool quiet;
    bool debug;
    bool dump;
    char *input_path;
    char *output_path;
    const dmi_format_t *output_format;
} dmi_config_t;

static bool parse_args(int argc, char *argv[], int *rv);

static void show_version(void);
static void show_usage(const char *proc);

static bool list_keywords(dmi_context_t *context);
static bool list_types(dmi_context_t *context);

static void print_all(dmi_context_t *context);
static void print_table(const dmi_table_t *table);
static void print_table_attrs(const dmi_table_t *table);
static void print_table_attr_array(const dmi_attribute_t *attr, const dmi_data_t *info, const void *value);
static void print_table_attr_struct(const dmi_attribute_t *attr, const void *value);
static void print_table_attr_value(const dmi_attribute_t *attr, const void *value);
static void print_table_attr_set(const dmi_attribute_t *attr, const void *value);
static void print_table_dump(const dmi_table_t *table);
static void print_hex_data(const void *data, size_t length);

static void log_error(dmi_context_t *context, dmi_log_level_t level, const char *format, va_list args);

dmi_config_t config =
{
    .command       = DMI_COMMAND_DUMP_TABLES,
    .memory_device = nullptr,
    .quiet         = false,
    .debug         = false,
    .dump          = false,
    .input_path    = nullptr,
    .output_path   = nullptr,
    .output_format = &dmi_text_format
};

static bool tty = false;

int main(int argc, char *argv[])
{
    dmi_context_t *context;
    bool status;

    int rv = EXIT_SUCCESS;
    if (!parse_args(argc, argv, &rv))
        return rv;

    argc -= optind;
    argv += optind;

#ifdef ENABLE_CURSES
    // Initialize terminal
    if (isatty(STDOUT_FILENO)) {
        if (setupterm(nullptr, STDOUT_FILENO, nullptr) == 0)
            tty = has_colors() and (start_color() != 0);
    }
#endif // ENABLE_CURSES

    // Create DMI context
    context = dmi_create();
    if (context == nullptr) {
        printf("Unable to create DMI context\n");
        return EXIT_FAILURE;
    }

    dmi_set_logger(context, log_error);
    if (config.quiet)
        dmi_set_log_level(context, DMI_LOG_WARNING);
    else if (config.debug)
        dmi_set_log_level(context, DMI_LOG_DEBUG);

    if (config.command == DMI_COMMAND_LIST_KEYWORDS) {
        status = list_keywords(context);
        goto exit;
    }

    if (config.command == DMI_COMMAND_LIST_TYPES) {
        status = list_types(context);
        goto exit;
    }

    // Open DMI context
    do {
        if (config.input_path != nullptr)
            status = dmi_dump_load(context, config.input_path);
        else
            status = dmi_open(context);

        if (not status)
            break;

        if (config.output_path != nullptr) {
            status = dmi_dump_save(context, config.output_path, false);
            if (not status)
                break;
        } else {
            print_all(context);
        }

        status = true;
    } while (false);

exit:
    // Close DMI context
    dmi_destroy(context);

    return status ? EXIT_SUCCESS : EXIT_FAILURE;
}

static bool parse_args(int argc, char *argv[], int *rv)
{
    static struct option long_options[] =
    {
        { "dev-mem",   required_argument, nullptr, 'd' },
        { "debug",     no_argument,       nullptr, 'g' },
        { "quiet",     no_argument,       nullptr, 'q' },
        { "string",    optional_argument, nullptr, 's' },
        { "type",      optional_argument, nullptr, 't' },
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
        int opt = getopt_long(argc, argv, "d:qs?t?uo:i:hv", long_options, &idx);

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

        case 's':
            if (optarg == nullptr)
                config.command = DMI_COMMAND_LIST_KEYWORDS;
            break;

        case 't':
            if (optarg == nullptr)
                config.command = DMI_COMMAND_LIST_TYPES;
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
                *rv = EXIT_FAILURE;
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
            *rv = EXIT_FAILURE;
            return false;
        }
    }

    return true;
}

static void show_version(void)
{
    printf("OpenDMI, version %s\n", OPENDMI_VERSION);
    printf("Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>\n\n");
}

static void show_usage(const char *proc)
{
    show_version();

    printf("Usage:\n");
    printf("    %s [options]\n", proc);
}

static bool list_keywords(dmi_context_t *context __attribute__((unused)))
{
    return true;
}

static bool list_types(dmi_context_t *context)
{
    const char *format;

    if (isatty(STDIN_FILENO))
        format = "%3d %-24s %s\n";
    else
        format = "%d\t%s\t%s\n";

    for (unsigned int type = 0; type < 0x100; type++) {
        const dmi_table_spec_t *spec = dmi_type_spec(context, (dmi_type_t)type);

        if (spec == nullptr)
            continue;

        printf(format, (int)spec->type, spec->code, spec->name);
    }

    return true;
}

static void print_all(dmi_context_t *context)
{
    dmi_registry_entry_t *entry;

    for (entry = context->registry->head; entry; entry = entry->seq_next) {
        print_table(entry->table);
    }
}

static void print_table(const dmi_table_t *table)
{
#ifdef ENABLE_CURSES
    if (tty)
        tputs(tparm(tigetstr("setaf"), COLOR_YELLOW), 1, putchar);
#endif // ENABLE_CURSES

    printf("Handle 0x%04x, DMI type %d, %zu bytes\n",
           (unsigned int)dmi_table_handle(table),
           dmi_table_type(table),
           table->total_length);
    printf("%s\n", dmi_table_name(table));

#ifdef ENABLE_CURSES
    if (tty)
        tputs(tparm(tigetstr("sgr0")), 1, putchar);
#endif // ENABLE_CURSES

    if (table->info and !config.dump)
        print_table_attrs(table);
    else
        print_table_dump(table);

    printf("\n");
}

static void print_table_attrs(const dmi_table_t *table)
{
    const dmi_table_spec_t *spec = table->spec;
    const dmi_attribute_t *attr = nullptr;

    // Process all attributes
    for (attr = spec->attributes; attr->params.name; attr++) {
        const dmi_data_t *ptr = (dmi_data_t *)table->info + attr->offset;

        // Check attribute level
        if (attr->params.level != DMI_VERSION_NONE) {
            if (table->level < attr->params.level)
                continue;
        }

        // Print attribute name
        printf("\t%s: ", attr->params.name);

        // Print attribute value
        if (attr->counter < 0) {
            if (attr->type == DMI_ATTRIBUTE_TYPE_STRUCT)
                print_table_attr_struct(attr, ptr);
            else
                print_table_attr_value(attr, ptr);
        } else {
            print_table_attr_array(attr, table->info, ptr);
        }
    }
}

static void print_table_attr_array(const dmi_attribute_t *attr, const dmi_data_t *info, const void *value)
{
    size_t count = *(size_t *)(info + attr->counter);

    printf("%zu items\n", count);

    const dmi_data_t *ptr = *(const dmi_data_t **)value;

    for (size_t i = 0; i < count; i++, ptr += attr->size) {
        printf("\t\t%zu: ", i);

        if (attr->type == DMI_ATTRIBUTE_TYPE_STRUCT)
            print_table_attr_struct(attr, ptr);
        else
            print_table_attr_value(attr, ptr);
    }
}

static void print_table_attr_struct(const dmi_attribute_t *attr, const void *value)
{
    const dmi_attribute_t *child_attr = nullptr;

    printf("\n");
    for (child_attr = attr->params.attrs; child_attr->params.name; child_attr++) {
        const dmi_data_t *ptr = (dmi_data_t *)value + child_attr->offset;

        printf("\t\t\t%s: ", child_attr->params.name);
        print_table_attr_value(child_attr, ptr);
    }
}

static void print_table_attr_value(const dmi_attribute_t *attr, const void *value)
{
    char *str;

    if (dmi_attribute_is_unspecified(attr, value)) {
        printf("<unspecified>\n");
        return;
    }
    if (dmi_attribute_is_unknown(attr, value)) {
        printf("<unknown>\n");
        return;
    }

    str = dmi_attribute_format(attr, value);
    if (str == nullptr) {
        printf("<error>\n");
        return;
    }

    if (attr->params.unit)
        printf("%s %s\n", str, attr->params.unit);
    else
        printf("%s\n", str);

    free(str);

    if (attr->type == DMI_ATTRIBUTE_TYPE_SET)
        print_table_attr_set(attr, value);
}

static void print_table_attr_set(const dmi_attribute_t *attr, const void *value)
{
    uint64_t mask;

    if (attr->size == sizeof(int8_t))
        mask = *(uint8_t *)value;
    else if (attr->size == sizeof(uint16_t))
        mask = *(uint16_t *)value;
    else if (attr->size == sizeof(uint32_t))
        mask = *(uint32_t *)value;
    else if (attr->size == sizeof(uint64_t))
        mask = *(uint64_t *)value;
    else
        return;

    for (unsigned i = 0; i < attr->size * CHAR_BIT; i++) {
        const char *name = dmi_name_lookup(attr->params.values, i);
        if (!name)
            continue;

        bool flag = mask & (1 << i);
        printf("\t\t%s: %s\n", name, flag ? "yes" : "no");
    }
}

static void print_table_dump(const dmi_table_t *table)
{
    printf("\tHeader and data:\n");
    print_hex_data(table->data, table->body_length);

    if (table->string_count > 0) {
        printf("\tStrings:\n");
        for (dmi_string_t i = 1; i <= table->string_count; i++) {
            const char *str = dmi_table_string(table, i);

            print_hex_data(str, strlen(str) + 1);
            printf("\t\t\"%s\"\n", str);
        }
    }
}

static void print_hex_data(const void *data, size_t length)
{
    const unsigned char *ptr = dmi_cast(ptr, data);

    for (size_t i = 0; i < length; i++) {
        char sp = ' ';

        if (i % 0x10 == 0)
            printf("\t\t");
        if (i % 0x10 == 0x0f)
            sp = '\n';

        printf("%02X%c", (int)ptr[i], sp);
    }

    if (length % 0x10 != 0)
        printf("\n");
}

static void log_error(dmi_context_t *context __attribute__((unused)), dmi_log_level_t level, const char *format, va_list args)
{
    FILE *out = stderr;

#ifdef ENABLE_CURSES
    if (tty) {
        out = stdout;

        switch (level) {
        case DMI_LOG_DEBUG:
            tputs(tparm(tigetstr("setaf"), 8), 1, putchar);
            break;

        case DMI_LOG_INFO:
            tputs(tparm(tigetstr("setaf"), COLOR_GREEN), 1, putchar);
            break;

        case DMI_LOG_NOTICE:
            tputs(tparm(tigetstr("setaf"), COLOR_CYAN), 1, putchar);
            break;

        case DMI_LOG_WARNING:
            tputs(tparm(tigetstr("setaf"), COLOR_YELLOW), 1, putchar);
            break;

        case DMI_LOG_ERROR:
            tputs(tparm(tigetstr("setaf"), COLOR_RED), 1, putchar);
            break;

        default:
            // fallthrough
        }
    }
#endif // ENABLE_CURSES

    fprintf(out, "[%s] ", dmi_log_level_name(level));

#ifdef ENABLE_CURSES
    if (tty)
        tputs(tparm(tigetstr("sgr0")), 1, putchar);
#endif // ENABLE_CURSES

    vfprintf(out, format, args);
    fprintf(out, "\n");
}
