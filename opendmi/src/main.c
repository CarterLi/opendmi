//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "config.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <opendmi/option.h>
#include <opendmi/context.h>
#include <opendmi/table.h>

typedef struct dmi_config dmi_config_t;

struct dmi_config
{
};

static void show_version(void);
static void show_usage(void);

static void print_all(dmi_context_t *context);
static void print_table(const dmi_table_t *table);
static void print_hex_data(const void *data, size_t length);

static void log_error(dmi_context_t *context, dmi_log_level_t level, const char *format, va_list args);

dmi_option_t dmi_global_options[] =
{
    {
        .short_name  = 'v',
        .long_name   = "version",
        .description = "Display the version and exit",
    },
    {
        .short_name  = 'h',
        .long_name   = "help",
        .description = "Display usage information and exit"
    },
    {
        .short_name  = 'x',
        .long_name   = "xml",
        .description = "Output in XML format"
    },
    {
        .short_name = 'j',
        .long_name  = "json",
        .description = "Output in JSON format"
    },
    {
        .short_name  = 'o',
        .long_name   = "output",
        .description = "Set output file name"
    },
    {
        .short_name  = 'q',
        .long_name   = "quiet",
        .description = "Be less verbose"
    }
};

int main(int argc, char *argv[])
{
    dmi_context_t *context;

    show_version();

    // Create DMI context
    context = dmi_create();
    if (context == nullptr) {
        printf("Unable to create DMI context: %s\n", dmi_error_message(dmi_get_error(nullptr)));
        return EXIT_FAILURE;
    }

    dmi_set_logger(context, log_error);

    // Open DMI context
    if (argc > 1)
        dmi_dump_load(context, argv[1]);
    else
        dmi_open(context);

    // Print all SMBIOS tables
    print_all(context);

    // Close DMI context
    dmi_destroy(context);

    return EXIT_SUCCESS;
}

static void show_version(void)
{
    printf("OpenDMI, version %s\n", OPENDMI_VERSION);
    printf("Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>\n\n");
}

static void show_usage(void)
{
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
    printf("Handle 0x%04x, DMI type %d, %zu bytes\n",
           (unsigned int)dmi_table_handle(table),
           dmi_table_type(table),
           table->total_length);
    printf("%s\n", dmi_table_name(table));

    if (!table->spec) {
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

    printf("\n");
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

static void log_error(dmi_context_t *context, dmi_log_level_t level, const char *format, va_list args)
{
    fprintf(stderr, "[%s] ", dmi_log_level_name(level));
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
}
