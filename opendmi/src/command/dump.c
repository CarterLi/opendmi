//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/command/dump.h>

static int dmi_dump_main(void);

const dmi_command_t dmi_dump_command =
{
    .name        = "dump",
    .description = "Dump entire SMBIOS table to file",
    .handler     = dmi_dump_main
};

static int dmi_dump_main(void)
{
    return EXIT_SUCCESS;
}
