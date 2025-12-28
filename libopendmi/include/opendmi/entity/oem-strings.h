//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_OEM_STRINGS_H
#define OPENDMI_ENTITY_OEM_STRINGS_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_oem_strings_data dmi_oem_strings_data_t;

/**
 * @brief OEM strings structure (type 11).
 */
DMI_PACKED_STRUCT(dmi_oem_strings_data)
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

typedef struct dmi_oem_strings dmi_oem_strings_t;

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
 * @brief OEM strings entity specification.
 */
extern const dmi_entity_spec_t dmi_oem_strings_spec;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_oem_strings_t *dmi_oem_strings_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
void dmi_oem_strings_free(dmi_oem_strings_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_OEM_STRINGS_H
