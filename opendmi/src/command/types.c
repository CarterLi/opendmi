//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/types.h>

typedef struct dmi_types_params
{
    bool help;
} dmi_types_params_t;

static int dmi_types_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_types_usage(void);

static dmi_types_params_t dmi_types_params =
{
    .help = false
};

const dmi_command_t dmi_types_command =
{
    .name        = "types",
    .description = "List SMBIOS structure types",
    .handler     = dmi_types_main
};

static const dmi_option_group_t dmi_types_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_types_params.help
        },
        {
            .short_names = "a",
            .long_names  = (const char *[]){ "all", nullptr },
            .description = "List all available types"
        },
        {}
    }
};

static int dmi_types_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_types_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_types_params.help) {
        dmi_types_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_types_usage(void)
{
}
