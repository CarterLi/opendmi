//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/explain.h>

static void dmi_explain_usage(void);
static int dmi_explain_main(dmi_context_t *context, int argc, char *argv[]);

static const dmi_option_set_t dmi_explain_options =
{
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

const dmi_command_t dmi_explain_command =
{
    .name        = "explain",
    .description = "Explain SMBIOS structure or type",
    .options     = dmi_options(&dmi_explain_options),
    .handlers    = {
        .usage = dmi_explain_usage,
        .main  = dmi_explain_main
    }
};

static void dmi_explain_usage(void)
{
    dmi_command_usage(&dmi_explain_command);
}

static int dmi_explain_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);
    dmi_unused(argc);
    dmi_unused(argv);

    dmi_command_message_ex(&dmi_explain_command, "Not implemented yet");

    return EXIT_FAILURE;
}
