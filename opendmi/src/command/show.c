//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/command/show.h>

static int dmi_show_main(void);

const dmi_command_t dmi_show_command =
{
    .name        = "show",
    .description = "Show SMBIOS structures data",
    .handler     = dmi_show_main
};

static int dmi_show_main(void)
{
    return EXIT_SUCCESS;
}
