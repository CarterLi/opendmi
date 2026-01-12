//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/command/modules.h>

static int dmi_modules_main(void);

const dmi_command_t dmi_modules_command =
{
    .name        = "modules",
    .description = "List OpenDMI extensions",
    .handler     = dmi_modules_main
};

static int dmi_modules_main(void)
{
    return EXIT_SUCCESS;
}
