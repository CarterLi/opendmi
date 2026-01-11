//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_STRING_PROPERTY_H
#define OPENDMI_ENTITY_STRING_PROPERTY_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_string_property      dmi_string_property_t;
typedef struct dmi_string_property_data dmi_string_property_data_t;

/**
 * @brief String property structure (type 46).
 *
 * This structure defines a string property for another structure. This allows
 * adding string properties that are common to several structures without
 * having to modify the definitions of these structures. Multiple type 46
 * structures can add string properties to the same parent structure.
 *
 * @since SMBIOS 3.5
 */
dmi_packed_struct(dmi_string_property_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Property identifier.
     */
    dmi_word_t ident;

    /**
     * @brief Property value.
     */
    dmi_string_t value;

    /**
     * @brief Handle corresponding to the structure this string property
     * applies to.
     */
    dmi_handle_t parent_handle;
};

struct dmi_string_property
{
    /**
     * @brief Property identifier.
     */
    uint16_t ident;

    /**
     * @brief Property value.
     */
    const char *value;

    /**
     * @brief Handle corresponding to the entity this string property
     * applies to.
     */
    dmi_handle_t parent_handle;

    /**
     * @brief The entity this string property applies to.
     */
    dmi_entity_t *parent;
};

/**
 * @brief String property entity specification.
 */
extern const dmi_entity_spec_t dmi_string_property_spec;

#endif // !OPENDMI_ENTITY_STRING_PROPERTY_H
