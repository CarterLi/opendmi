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

#ifndef DMI_OEM_STRINGS_DATA_T
#define DMI_OEM_STRINGS_DATA_T
typedef struct dmi_oem_strings_data dmi_oem_strings_data_t;
#endif // !DMI_OEM_STRINGS_DATA_T

/**
 * @brief OEM strings table (type 11).
 */
DMI_PACKED_STRUCT(dmi_oem_strings_data)
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

#ifndef DMI_OEM_STRINGS_T
#define DMI_OEM_STRINGS_T
typedef struct dmi_oem_strings dmi_oem_strings_t;
#endif // !DMI_OEM_STRINGS_T

/**
 * @brief OEM strings.
 */
struct dmi_oem_strings
{
    /**
     * @brief Number of strings.
     */
    size_t string_count;

    /**
     * @brief String values.
     */
    const char **strings;
};

/**
 * @brief OEM strings table specification.
 */
extern const dmi_table_spec_t dmi_oem_strings_table;

__BEGIN_DECLS

dmi_oem_strings_t *dmi_oem_strings_decode(const dmi_table_t *table);
void dmi_oem_strings_free(dmi_oem_strings_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_OEM_STRINGS_H
