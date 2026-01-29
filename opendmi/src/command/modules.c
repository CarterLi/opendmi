//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/modules.h>

static void dmi_modules_usage(void);
static int dmi_modules_main(dmi_context_t *context, int argc, char *argv[]);

static const dmi_option_set_t dmi_modules_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_command_config.show_usage
        },
        {}
    }
};

const dmi_command_t dmi_modules_command =
{
    .name        = "modules",
    .description = "List available modules",
    .options     = dmi_options(&dmi_modules_options),
    .flags       = DMI_COMMAND_FLAG_DETACHED,
    .handlers    = {
        .usage = dmi_modules_usage,
        .main  = dmi_modules_main
    }
};

static void dmi_modules_usage(void)
{
    dmi_command_usage(&dmi_modules_command);
}

static int dmi_modules_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);
    dmi_unused(argc);
    dmi_unused(argv);

    dmi_command_message_ex(&dmi_modules_command, "Not implemented yet");

    return EXIT_FAILURE;
}
