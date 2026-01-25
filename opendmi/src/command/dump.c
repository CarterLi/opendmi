//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/dump.h>

typedef struct dmi_dump_params
{
    bool help;
    char *path;
} dmi_dump_params_t;

static int dmi_dump_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_dump_usage(void);

static dmi_dump_params_t dmi_dump_params =
{
    .help = false,
    .path = "smbios.bin"
};

const dmi_command_t dmi_dump_command =
{
    .name        = "dump",
    .description = "Dump entire SMBIOS table to file",
    .handler     = dmi_dump_main
};

static const dmi_option_group_t dmi_dump_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_dump_params.help
        },
        {
            .short_names = "o",
            .long_names  = (const char *[]){ "output", nullptr },
            .description = "Set output file path (default: smbios.bin)",
            .value       = &dmi_dump_params.path,
            .argument    = {
                .name     = "PATH",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {}
    }
};

static int dmi_dump_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_dump_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_dump_params.help) {
        dmi_dump_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_dump_usage(void)
{
}
