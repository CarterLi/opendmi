//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_H
#define OPENDMI_TABLE_H

#pragma once

#include <opendmi/types.h>

#ifndef DMI_TABLE_SPEC_T
#define DMI_TABLE_SPEC_T
typedef struct dmi_table_spec dmi_table_spec_t;
#endif // !DMI_TABLE_SPEC_T

#ifndef DMI_TABLE_HEADER_T
#define DMI_TABLE_HEADER_T
typedef struct dmi_table_header dmi_table_header_t;
#endif // !DMI_TABLE_HEADER_T

#ifndef DMI_TABLE_T
#define DMI_TABLE_T
typedef struct dmi_table dmi_table_t;
#endif // !DMI_TABLE_T

/**
 * DMI table specification.
 */
struct dmi_table_spec
{
    /**
     * @brief DMI type.
     */
    dmi_type_t type;

    /**
     * @brief Minimum length. Zero means that the minimum length is not
     * specified.
     *
     * Starting with SMBIOS 2.3, each SMBIOS structure type has a minimum
     * length - enabling the addition of new, but optional, fields to SMBIOS
     * structures. In no case shall a structure’s length result in a field
     * being less than fully populated. For example, a voltage probe structure
     * with length of 0x15 is invalid because the nominal value field would
     * not be fully specified.
     *
     * @since SMBIOS 2.3
     */
    size_t min_length;

    /**
     * @brief Decode handler.
     */
    bool (*decode)(dmi_table_t *table);

    /**
     * @brief Free handler.
     */
    bool (*free)(dmi_table_t *table);
};

/**
 * @brief DMI table header.
 */
struct dmi_table_header
{
    /**
     * @brief Specifies the type of structure. Types 0 through 127 (7Fh) are
     * reserved for and defined by this specification. Types 128 through 256
     * (0x80 to 0xFF) are available for system- and OEM-specific information.
     */
    enum dmi_type type;

    /**
     * @brief Specifies the length of the formatted area of the structure,
     * starting at the Type field. The length of the structure’s string-set is
     * not included.
     */
    uint8_t length;

    /**
     * @brief Specifies the structure’s handle.
     *
     * If the system configuration changes, a previously assigned handle might
     * no longer exist. However, after a handle has been assigned by the
     * platform firmware, the firmware cannot re-assign that handle number to
     * another structure.
     *
     * Unless otherwise specified, when referring to another structure’s
     * handle, the value 0x0FFFF is used to indicate that the referenced handle
     * is not applicable or does not exist.
     *
     * @see dmi_handle_t
     */
    dmi_handle_t handle;
} __attribute__((packed));

/**
 * @brief DMI table descriptor.
 */
struct dmi_table
{
    /**
     * @brief DMI context handle.
     */
    dmi_context_t *context;

    /**
     * @brief Table type.
     */
    dmi_type_t type;

    /**
     * @brief Pointer to table specification.
     */
    dmi_table_spec_t *spec;

    /**
     * @brief DMI handle.
     */
    dmi_handle_t handle;

    /**
     * @brief Pointer to raw table data, including header.
     */
    const dmi_data_t *data;

    /**
     * @brief Total length of the table.
     */
    size_t total_length;

    /**
     * @brief Formatted section length.
     */
    size_t body_length;

    /**
     * @brief Unformed section length. The unformed section of the structure
     * is used for passing variable data such as text strings.
     */
    size_t extra_length;

    /**
     * @brief String data.
     */
    const char **strings;

    /**
     * @brief Number of strings in the table.
     */
    size_t string_count;

    /**
     * @brief Decoded table information.
     */
    void *info;
};

__BEGIN_DECLS

/**
 * @brief Decode DMI table.
 */
dmi_table_t *dmi_table_decode(dmi_context_t *context, const void *data);

/**
 * @brief Get DMI table handle.
 */
dmi_handle_t dmi_table_handle(struct dmi_table *table);

/**
 * @brief Get DMI handle name.
 */
const char *dmi_table_name(struct dmi_table *table);

/**
 * @brief Get DMI table string.
 */
const char *dmi_table_string(struct dmi_table *table, dmi_string_t num);

/**
 * @brief Destroy DMI table handle.
 */
void dmi_table_destroy(struct dmi_table *table);

__END_DECLS

#endif // !OPENDMI_TABLE_H
