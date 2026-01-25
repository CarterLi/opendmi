//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/show.h>

typedef struct dmi_show_params
{
    bool help;
} dmi_show_params_t;

static int dmi_show_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_show_usage(void);

static dmi_show_params_t dmi_show_params =
{
    .help = false
};

const dmi_command_t dmi_show_command =
{
    .name        = "show",
    .description = "Show SMBIOS structures data",
    .handler     = dmi_show_main
};

const dmi_option_group_t dmi_show_options =
{
    .name = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_show_params.help
        },
        {
            .short_names = "H",
            .long_names  = (const char *[]){ "handle", nullptr },
            .description = "Only display the entries of given handle(s)",
            .argument    = {
                .name     = "HANDLE",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "T",
            .long_names  = (const char *[]){ "type", nullptr },
            .description = "Only display the entries of given type(s)",
            .argument    = {
                .name     = "TYPE",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "f",
            .long_names  = (const char *[]){ "format", nullptr },
            .description = "Set output format",
            .argument    = {
                .name     = "FORMAT",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "o",
            .long_names  = (const char *[]){ "output", nullptr },
            .description = "Set output file",
            .argument    = {
                .name     = "PATH",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {}
    }
};

static int dmi_show_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_show_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_show_params.help) {
        dmi_show_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_show_usage(void)
{
}
