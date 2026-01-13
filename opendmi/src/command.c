//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <opendmi/command.h>
#include <opendmi/command/check.h>
#include <opendmi/command/dump.h>
#include <opendmi/command/entry.h>
#include <opendmi/command/list.h>
#include <opendmi/command/modules.h>
#include <opendmi/command/show.h>
#include <opendmi/command/types.h>

const dmi_command_t *dmi_commands[] =
{
    &dmi_check_command,
    &dmi_dump_command,
    &dmi_entry_command,
    &dmi_list_command,
    &dmi_modules_command,
    &dmi_show_command,
    &dmi_types_command,
    nullptr
};

void dmi_command_list(void)
{
    const dmi_command_t **pcommand;

    printf("Commands:\n");
    for (pcommand = dmi_commands; *pcommand != nullptr; pcommand++) {
        printf("    %-8s  %s\n", (*pcommand)->name, (*pcommand)->description);
    }
}

int dmi_command_run(const char *name, dmi_context_t *context)
{
    const dmi_command_t **pcommand;

    for (pcommand = dmi_commands; *pcommand != nullptr; pcommand++) {
        if (strcmp((*pcommand)->name, name) == 0)
            return (*pcommand)->handler(context);
    }

    fprintf(stderr, "Unexpected command: %s\n", name);
    fprintf(stderr, "Use --help or -h for help\n");

    return EXIT_FAILURE;
}
