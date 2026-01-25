//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/entry.h>

typedef struct dmi_entry_params
{
    bool help;
} dmi_entry_params_t;

static int dmi_entry_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_entry_usage(void);

static dmi_entry_params_t dmi_entry_params =
{
    .help = false
};

const dmi_command_t dmi_entry_command =
{
    .name        = "entry",
    .description = "Show SMBIOS entry point data",
    .handler     = dmi_entry_main
};

static const dmi_option_group_t dmi_entry_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_entry_params.help
        },
        {}
    }
};

static int dmi_entry_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_entry_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_entry_params.help) {
        dmi_entry_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_entry_usage(void)
{
}
