//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/command/types.h>

static int dmi_types_main(void);

const dmi_command_t dmi_types_command =
{
    .name        = "types",
    .description = "List SMBIOS structure types",
    .handler     = dmi_types_main
};

static int dmi_types_main(void)
{
    return EXIT_SUCCESS;
}
