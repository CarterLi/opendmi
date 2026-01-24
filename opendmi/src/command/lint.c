//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/command/lint.h>

static int dmi_lint_main(dmi_context_t *context);

const dmi_command_t dmi_lint_command =
{
    .name        = "lint",
    .description = "Check SMBIOS structures for errors",
    .handler     = dmi_lint_main
};

static int dmi_lint_main(dmi_context_t *context)
{
    dmi_unused(context);

    return EXIT_SUCCESS;
}
