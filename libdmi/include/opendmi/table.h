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

/**
 * DMI table specification.
 */
struct dmi_table_spec
{
    enum dmi_type type;
    char *name;
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
    struct dmi_table_header *header;
    unsigned int string_count;
    const char **strings;
};

__BEGIN_DECLS

struct dmi_table *dmi_table_open(void *ptr);
dmi_handle_t dmi_table_handle(struct dmi_table *table);
const char *dmi_table_string(struct dmi_table *table, dmi_string_t num);
void dmi_table_close(struct dmi_table *table);

__END_DECLS

#endif // !OPENDMI_TABLE_H
