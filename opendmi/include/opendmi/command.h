//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_COMMAND_H
#define OPENDMI_COMMAND_H

#pragma once

#include <opendmi/types.h>
#include <opendmi/option.h>

typedef struct dmi_command dmi_command_t;

/**
 * @brief Command handler function.
 *
 * @param[in] context Context handle.
 * @param[in] argc    Number of arguments.
 * @param[in] argv    Arguments array.
 */
typedef int dmi_command_handler_fn(dmi_context_t *context, int argc, char *argv[]);

/**
 * @brief Command specification.
 */
struct dmi_command
{
    /**
     * @brief Command name.
     */
    const char *name;

    /**
     * @brief Short description.
     */
    const char *description;

    /**
     * @brief Command options specification.
     */
    const dmi_option_t *options;

    /**
     * @brief Command arguments specification.
     */
    const dmi_argument_t *arguments;

    /**
     * @brief Command handler.
     */
    dmi_command_handler_fn *handler;
};

__BEGIN_DECLS

void dmi_command_list(void);

const dmi_command_t *dmi_command_find(const char *name);

int dmi_command_run(
        const dmi_command_t *command,
        dmi_context_t       *context,
        int                  argc,
        char                *argv[]);

__END_DECLS

#endif // !OPENDMI_COMMAND_H
