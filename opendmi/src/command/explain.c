//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/explain.h>

typedef struct dmi_explain_params
{
    bool help;
} dmi_explain_params_t;

static int dmi_explain_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_explain_usage(void);

static dmi_explain_params_t dmi_explain_params =
{
    .help = false
};

const dmi_command_t dmi_explain_command =
{
    .name        = "explain",
    .description = "Explain SMBIOS structure or type",
    .handler     = dmi_explain_main
};

static const dmi_option_group_t dmi_explain_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_explain_params.help
        },
        {}
    }
};

static int dmi_explain_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_explain_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_explain_params.help) {
        dmi_explain_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_explain_usage(void)
{
}
