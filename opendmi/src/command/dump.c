//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/dump.h>

static int dmi_dump_main(dmi_context_t *context, int argc, char *argv[]);

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
            .description = "Print this help and exit"
        },
        {}
    }
};

static int dmi_dump_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_dump_options, argc, argv) < 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
