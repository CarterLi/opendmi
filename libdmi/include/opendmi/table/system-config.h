//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_SYSTEM_CONFIG_H
#define OPENDMI_TABLE_SYSTEM_CONFIG_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief System configuration options table (type 12).
 */
DMI_PACKED_STRUCT(dmi_system_config_options_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Number of strings.
     */
    dmi_byte_t count;
};

/**
 * @brief System configuration options table specification.
 */
extern const dmi_table_spec_t dmi_system_config_options_table;

#endif // !OPENDMI_TABLE_SYSTEM_CONFIG_H
