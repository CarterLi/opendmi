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
#include <opendmi/tty.h>

static void dmi_show_version(void);
static void dmi_show_usage(void);

static void dmi_log_handler(
        dmi_context_t   *context,
        dmi_log_level_t  level,
        const char      *format,
        va_list          args);

int main(int argc, char *argv[])
{
    int rv;
    dmi_context_t *context;
    const dmi_option_set_t *options[] = { &dmi_global_options, nullptr };
    const dmi_command_t *command;

    // Initialize command environment
    dmi_command_init(basename(argv[0]));
    argc--, argv++;

    // Create DMI context
    context = dmi_create(DMI_CONTEXT_FLAG_RELAXED);
    if (context == nullptr) {
        fprintf(stderr, "Unable to create DMI context\n");
        return EXIT_FAILURE;
    }

    rv = EXIT_FAILURE;
    do {
        int count;

        // Parse global options
        count = dmi_option_parse(context, options, argc, argv);
        if (count < 0) {
            rv = EXIT_USAGE;
            break;
        }
        argc -= count, argv += count;

        if (dmi_global_config.show_version) {
            rv = EXIT_SUCCESS;
            dmi_show_version();
            break;
        }
        if (dmi_global_config.show_usage) {
            rv = EXIT_SUCCESS;
            dmi_show_usage();
            break;
        }

        if (argc == 0) {
            rv = EXIT_USAGE;
            dmi_command_message("Missing command");
            break;
        }

        // Find command
        command = dmi_command_find(argv[0]);
        if (command == nullptr) {
            rv = EXIT_USAGE;
            dmi_command_message("Invalid command: %s", argv[0]);
            break;
        }
        argc--, argv++;

        // Initialize logging
        if (dmi_global_config.log_enable) {
            dmi_set_logger(context, dmi_log_handler);
            dmi_set_log_level(context, dmi_global_config.log_level);
        }

        // Execute command
        rv = dmi_command_run(command, context, argc, argv);
    } while (false);

    // Close DMI context
    dmi_destroy(context);

    return rv;
}

static void dmi_show_version(void)
{
    dmi_tty_header("OpenDMI Framework, version %s", OPENDMI_VERSION);

    dmi_tty_cprintf(DMI_TTY_COLOR_GREY, "Copyright (c) 2025-2026, The OpenDMI contributors\n");
    dmi_tty_cprintf(DMI_TTY_COLOR_GREY, "Licensed under the BSD 3-Clause License\n\n");
}

static void dmi_show_usage(void)
{
    dmi_show_version();
    dmi_command_usage(nullptr);    
}

static void dmi_log_handler(
        dmi_context_t   *context,
        dmi_log_level_t  level,
        const char      *format,
        va_list          args)
{
    FILE *out = stderr;

    dmi_unused(context);

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
