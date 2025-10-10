//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <opendmi/option.h>
#include <opendmi/context.h>

typedef struct dmi_config dmi_config_t;

struct dmi_config
{
};

static void show_version(void);
static void show_usage(void);

dmi_option_t dmi_global_options[] =
{
    {
        .short_name  = 'v',
        .long_name   = "version",
        .description = "Display the version and exit",
    },
    {
        .short_name  = 'h',
        .long_name   = "help",
        .description = "Display usage information and exit"
    },
    {
        .short_name  = 'x',
        .long_name   = "xml",
        .description = "Output in XML format"
    },
    {
        .short_name = 'j',
        .long_name  = "json",
        .description = "Output in JSON format"
    },
    {
        .short_name  = 'o',
        .long_name   = "output",
        .description = "Set output file name"
    },
    {
        .short_name  = 'q',
        .long_name   = "quiet",
        .description = "Be less verbose"
    }
};

int main(int argc, char *argv[])
{
    // Open DMI context
    dmi_context_t *dmi = dmi_open();
    if (dmi == nullptr) {
        printf("Unable to open DMI context: %s\n", dmi_error_message(dmi_get_error(nullptr)));
        return EXIT_FAILURE;
    }

    // Close DMI context
    dmi_close(dmi);

    return EXIT_SUCCESS;
}

static void show_version(void)
{
}

static void show_usage(void)
{
}
