//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/list.h>

static int dmi_list_main(dmi_context_t *context);

const dmi_command_t dmi_list_command =
{
    .name        = "list",
    .description = "List SMBIOS structures",
    .handler     = dmi_list_main
};

static int dmi_list_main(dmi_context_t *context)
{
    dmi_unused(context);

    return EXIT_SUCCESS;
}
