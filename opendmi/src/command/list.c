//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/command/list.h>

static int dmi_list_main(void);

const dmi_command_t dmi_list_command =
{
    .name        = "list",
    .description = "List available SMBIOS structures",
    .handler     = dmi_list_main
};

static int dmi_list_main(void)
{
    return EXIT_SUCCESS;
}
