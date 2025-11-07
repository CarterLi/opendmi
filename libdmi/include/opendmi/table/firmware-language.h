//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_FIRMWARE_LANGUAGE_H
#define OPENDMI_TABLE_FIRMWARE_LANGUAGE_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Firmware language information table (type 13).
 */
DMI_PACKED_STRUCT(dmi_firmware_language_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Number of languages available. Each available language has a
     * description string. This field contains the number of strings that
     * follow the formatted area of the structure.
     * 
     * @since SMBIOS 2.0
     */
    dmi_byte_t count;

    /**
     * @brief Flags.
     * @since SMBIOS 2.1
     */
    dmi_byte_t flags;

    /**
     * @brief Reserved for future use.
     * @since SMBIOS 2.0
     */
    dmi_byte_t reserved[15];

    /**
     * @brief String number (one-based) of the currently installed language.
     */
    dmi_string_t curent_language;
};

/**
 * @brief Firmware language information table specification.
 */
extern const dmi_table_spec_t dmi_firmware_language_table;

#endif // !OPENDMI_TABLE_FIRMWARE_LANGUAGE_H
