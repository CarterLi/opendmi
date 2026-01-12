//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_COMMAND_H
#define OPENDMI_COMMAND_H

#pragma once

#include <opendmi/option.h>

typedef struct dmi_command dmi_command_t;

/**
 * @brief Command handler function.
 */
typedef int dmi_command_handler_fn(void);

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

__END_DECLS

#endif // !OPENDMI_COMMAND_H
