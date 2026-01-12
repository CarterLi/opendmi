//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/command/entry.h>

static int dmi_entry_main(void);

const dmi_command_t dmi_entry_command =
{
    .name        = "entry",
    .description = "Show SMBIOS entry point data",
    .handler     = dmi_entry_main
};

static int dmi_entry_main(void)
{
    return EXIT_SUCCESS;
}
