//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_DELL_H
#define OPENDMI_TABLE_DELL_H

#pragma once

#include <opendmi/table.h>
#include <opendmi/extension.h>

enum dmi_dell_type
{
    DMI_TYPE_DELL_INDEXED_IO        = 212, ///< Dell: Indexed IO
	DMI_TYPE_DELL_PROTECTED_AREA_1  = 214, ///< Dell: Protected Area Type 1
	DMI_TYPE_DELL_PROTECTED_AREA_2  = 215, ///< Dell: Protected Area Type 2
	DMI_TYPE_DELL_CALLING_INTERFACE = 218  ///< Dell: Calling interface
};

/**
 * @brief Dell SMI calling interface token.
 */
DMI_PACKED_STRUCT(dmi_dell_calling_interface_token)
{
    /**
     * @brief Token identifier.
     */
    uint16_t id;

    /**
     * @brief Location.
     */
    uint16_t location;

    /**
     * @brief Token value or string length.
     */
    uint16_t length;
};

/**
 * @brief Dell SMI calling interface table (type 218).
 */
DMI_PACKED_STRUCT(dmi_dell_calling_interface_table)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Command address.
     */
    uint16_t command_address;

    /**
     * @brief Command code.
     */
	uint8_t command_code;

    /**
     * @brief Supported commands.
     */
	uint32_t supported_commands;

    /**
     * @brief Tokens.
     */
	struct dmi_dell_calling_interface_token tokens[];
};

/**
 * @brief Dell DMI extension.
 */
extern const dmi_extension_t dmi_dell_ext;

#endif // !OPENDMI_TABLE_DELL_H
