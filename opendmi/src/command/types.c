//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "../config.h"

#if __has_include(<unistd.h>)
#   include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <opendmi/context.h>
#include <opendmi/command/types.h>

typedef struct dmi_types_config
{
    bool show_all;
} dmi_types_config_t;

static void dmi_types_usage(void);
static int dmi_types_main(dmi_context_t *context, int argc, char *argv[]);

static dmi_types_config_t dmi_types_config =
{
    .show_all = false
};

static const dmi_option_set_t dmi_types_options =
{
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_command_config.show_usage
        },
        {
            .short_names = "a",
            .long_names  = (const char *[]){ "all", nullptr },
            .description = "List all available types",
            .value       = &dmi_types_config.show_all
        },
        {}
    }
};

const dmi_command_t dmi_types_command =
{
    .name        = "types",
    .description = "List SMBIOS structure types",
    .options     = dmi_options(&dmi_types_options),
    .flags       = DMI_COMMAND_FLAG_DETACHED | DMI_COMMAND_FLAG_PAGER,
    .handlers    = {
        .usage = dmi_types_usage,
        .main  = dmi_types_main
    }
};

static void dmi_types_usage(void)
{
    dmi_command_usage(&dmi_types_command);
}

static int dmi_types_main(dmi_context_t *context, int argc, char *argv[])
{
    const char *format;

    assert(context != nullptr);
    dmi_unused(argc);
    dmi_unused(argv);

    if (isatty(STDIN_FILENO))
        format = "%3d %-24s %s\n";
    else
        format = "%d\t%s\t%s\n";

    for (size_t type = 0; type < 0x100; type++) {
        const dmi_entity_spec_t *spec = dmi_type_spec(context, (dmi_type_t)type);

        if (spec == nullptr)
            continue;

        printf(format, (int)spec->type, spec->code, spec->name);
    }

    return EXIT_SUCCESS;
}
