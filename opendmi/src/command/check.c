//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/command/check.h>

static int dmi_check_main(void);

const dmi_command_t dmi_check_command =
{
    .name        = "check",
    .description = "Check SMBIOS table for errors",
    .handler     = dmi_check_main
};

static int dmi_check_main(void)
{
    return EXIT_SUCCESS;
}
