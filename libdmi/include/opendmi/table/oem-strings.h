//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_OEM_STRINGS_H
#define OPENDMI_TABLE_OEM_STRINGS_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief OEM strings table (type 11).
 */
struct dmi_oem_strings_table
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Number of strings.
     */
    uint8_t count;
} __attribute__((packed));

/**
 * @brief OEM strings table specification.
 */
extern const dmi_table_spec_t dmi_oem_strings_table_spec;

#endif // !OPENDMI_TABLE_OEM_STRINGS_H
