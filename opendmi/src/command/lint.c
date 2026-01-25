//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/lint.h>

typedef struct dmi_lint_params
{
    bool help;
    bool check_all;
    bool check_links;
} dmi_lint_params_t;

static int dmi_lint_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_lint_usage(void);

static dmi_lint_params_t dmi_lint_params =
{
    .help        = false,
    .check_all   = false,
    .check_links = false
};

const dmi_command_t dmi_lint_command =
{
    .name        = "lint",
    .description = "Check SMBIOS structures for errors",
    .handler     = dmi_lint_main
};

static const dmi_option_group_t dmi_lint_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_lint_params.help
        },
        {
            .short_names = "a",
            .long_names  = (const char *[]){ "all" },
            .description = "Enable all checks",
            .value       = &dmi_lint_params.check_links
        },
        {
            .short_names = "l",
            .long_names  = (const char *[]){ "links" },
            .description = "Enable link checking",
            .value       = &dmi_lint_params.check_links
        },
        {}
    }
};

static int dmi_lint_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_lint_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_lint_params.help) {
        dmi_lint_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_lint_usage(void)
{
}
