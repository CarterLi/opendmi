//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <opendmi/tty.h>
#include <opendmi/command.h>
#include <opendmi/command/dump.h>
#include <opendmi/command/entry.h>
#include <opendmi/command/list.h>
#include <opendmi/command/modules.h>
#include <opendmi/command/show.h>
#include <opendmi/command/explain.h>
#include <opendmi/command/lint.h>
#include <opendmi/command/export.h>
#include <opendmi/command/import.h>
#include <opendmi/command/types.h>

const dmi_command_t *dmi_commands[] =
{
    &dmi_dump_command,
    &dmi_entry_command,
    &dmi_list_command,
    &dmi_show_command,
    &dmi_explain_command,
    &dmi_lint_command,
    &dmi_export_command,
    &dmi_import_command,
    &dmi_types_command,
    &dmi_modules_command,
    nullptr
};

void dmi_command_list(void)
{
    const dmi_command_t **pcommand;

    dmi_tty_header("Commands:");

    for (pcommand = dmi_commands; *pcommand != nullptr; pcommand++) {
        dmi_tty_cprintf(DMI_TTY_COLOR_YELLOW, "%4s%-8s", "", (*pcommand)->name);
        dmi_tty_cprintf(DMI_TTY_COLOR_WHITE, " %s\n", (*pcommand)->description);
    }
    printf("\n");
}

const dmi_command_t *dmi_command_find(const char *name)
{
    const dmi_command_t **pcommand;

    assert(name != nullptr);

    for (pcommand = dmi_commands; *pcommand != nullptr; pcommand++) {
        if (strcmp((*pcommand)->name, name) == 0)
            return *pcommand;
    }

    return nullptr;
}

int dmi_command_run(
        const dmi_command_t *command,
        dmi_context_t       *context,
        int                  argc,
        char                *argv[])
{
    assert(command != nullptr);
    assert(context != nullptr);
    assert(argv != nullptr);

    return command->handler(context, argc, argv);
}
