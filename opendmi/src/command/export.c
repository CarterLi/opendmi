//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/format.h>
#include <opendmi/format/yaml.h>
#include <opendmi/command/export.h>
typedef struct dmi_export_params
{
    bool help;
    char *path;
    const dmi_format_t *format;
    bool pretty;
    bool force;
} dmi_export_params_t;

static int dmi_export_main(dmi_context_t *context, int argc, char *argv[]);
static void dmi_export_usage(void);

static dmi_export_params_t dmi_export_params =
{
    .help   = false,
    .path   = nullptr,
    .format = &dmi_yaml_format,
    .pretty = false,
    .force  = false
};

const dmi_command_t dmi_export_command =
{
    .name        = "export",
    .description = "Export SMBIOS data to external format",
    .handler     = dmi_export_main
};

static const dmi_option_group_t dmi_export_options =
{
    .name    = "Command options",
    .options = (const dmi_option_t[]){
        {
            .short_names = "?h",
            .long_names  = (const char *[]){ "help", nullptr },
            .description = "Print this help and exit",
            .value       = &dmi_export_params.help,
        },
        {
            .short_names = "o",
            .long_names  = (const char *[]){ "output", nullptr },
            .description = "Set output file path (default: stdout)",
            .value       = &dmi_export_params.path,
            .argument    = {
                .name     = "PATH",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "f",
            .long_names  = (const char *[]){ "format", nullptr },
            .description = "Set output format (default: yaml)",
            .argument    = {
                .name     = "FORMAT",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "p",
            .long_names  = (const char *[]){ "pretty", nullptr },
            .description = "Enable pretty output",
            .value       = &dmi_export_params.pretty
        },
        {
            .short_names = "F",
            .long_names  = (const char *[]){ "force", nullptr },
            .description = "Overwrite existing files",
            .value       = &dmi_export_params.force
        },
        {}
    }
};

static int dmi_export_main(dmi_context_t *context, int argc, char *argv[])
{
    dmi_unused(context);

    if (dmi_option_parse(&dmi_export_options, argc, argv) < 0)
        return EXIT_FAILURE;

    if (dmi_export_params.help) {
        dmi_export_usage();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static void dmi_export_usage(void)
{
}
