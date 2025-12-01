//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_GROUP_ASSOC_H
#define OPENDMI_TABLE_GROUP_ASSOC_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_GROUP_ASSOC_T
#define DMI_GROUP_ASSOC_T
typedef struct dmi_group_assoc dmi_group_assoc_t;
#endif // !DMI_GROUP_ASSOC_T

#ifndef DMI_GROUP_ASSOC_DATA_T
#define DMI_GROUP_ASSOC_DATA_T
typedef struct dmi_group_assoc_data dmi_group_assoc_data_t;
#endif // !DMI_GROUP_ASSOC_DATA_T


/**
 * @brief Group associations table (type 14).
 */
DMI_PACKED_STRUCT(dmi_group_assoc_data)
{
    /**
     * @brief DMI structure header.
     */
    dmi_header_t header;

    /**
     * @brief String number of string describing the group.
     */
    dmi_string_t group_name;

    /**
     * @brief Item (structure) type of this member.
     */
    dmi_byte_t item_type;

    /**
     * @brief Handle corresponding to this structure.
     */
    dmi_handle_t item_handle;
};

/**
 * @brief Group associations.
 */
struct dmi_group_assoc
{
    /**
     * @brief String describing the group.
     */
    const char *group_name;

    /**
     * @brief @brief Item (structure) type of this member.
     */
    dmi_type_t item_type;

    /**
     * @brief Handle corresponding to this structure.
     */
    dmi_handle_t item_handle;
};

/**
 * @brief Group associations table specification.
 */
extern const dmi_table_spec_t dmi_group_assoc_table;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_group_assoc_t *dmi_group_assoc_decode(const dmi_table_t *table);

/**
 * @internal
 */
void dmi_group_assoc_free(dmi_group_assoc_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_GROUP_ASSOC_H
