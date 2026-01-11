//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_SYSTEM_CONFIG_H
#define OPENDMI_ENTITY_SYSTEM_CONFIG_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_system_config_opts      dmi_system_config_opts_t;
typedef struct dmi_system_config_opts_data dmi_system_config_opts_data_t;

/**
 * @brief System configuration options structure (type 12).
 */
dmi_packed_struct(dmi_system_config_opts_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Number of strings.
     */
    dmi_byte_t count;
};

/**
 * @brief System configuration options.
 */
struct dmi_system_config_opts
{
    /**
     * @brief Number of options.
     */
    size_t option_count;

    /**
     * @brief Option names.
     */
    const char **options;
};

/**
 * @brief System configuration options entity specification.
 */
extern const dmi_entity_spec_t dmi_system_config_opts_spec;

#endif // !OPENDMI_ENTITY_SYSTEM_CONFIG_H
