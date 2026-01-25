//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/import.h>

typedef struct dmi_entry_params
{
    bool help;
} dmi_import_params_t;

static int dmi_import_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_import_usage(void);

static dmi_import_params_t dmi_import_params =
{
    .help = false
};

const dmi_command_t dmi_import_command =
{
    .name        = "import",
    .description = "Import SMBIOS data from external format",
    .handler     = dmi_import_main
};

static const dmi_option_group_t dmi_import_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_import_params.help
        },
        {}
    }
};

static int dmi_import_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_import_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_import_params.help) {
        dmi_import_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_import_usage(void)
{
}
