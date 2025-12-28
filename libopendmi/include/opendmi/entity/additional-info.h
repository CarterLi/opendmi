//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_ADDITIONAL_INFO_H
#define OPENDMI_ENTITY_ADDITIONAL_INFO_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_additional_info_data dmi_additional_info_data_t;
typedef struct dmi_additional_info      dmi_additional_info_t;

/**
 * @brief Additional information entry.
 */
dmi_packed_struct(dmi_additional_info_entry_data)
{
    /**
     * @brief Length of this additional information entry instance; a minimum
     * of 6.
     */
    dmi_byte_t length;

    /**
     * @brief Handle, or instance number, associated with the structure for
     * which additional information is provided.
     */
    dmi_word_t ref_handle;

    /**
     * @brief Offset of the field within the structure referenced by the
     * referenced handle for which additional information is provided.
     */
    dmi_byte_t ref_offset;

    /**
     * @brief Number of the optional string to be associated with the field
     * referenced by the referenced offset.
     */
    dmi_string_t string;

    /**
     * @brief Enumerated value or updated field content that has not yet been
     * approved for publication in this specification and therefore could not
     * be used in the field referenced by referenced offset.
     *
     * @note
     * This field is the same type and size as the field being referenced by
     * this additional information entry.
     */
    dmi_data_t value[];
};

/**
 * @brief Additional information structure (type 40).
 */
dmi_packed_struct(dmi_additional_info_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Number of additional information entries that follow.
     */
    dmi_byte_t entry_count;
};

/**
 * @brief Additional information entity specification.
 */
extern const dmi_entity_spec_t dmi_additional_info_spec;

#endif // !OPENDMI_ENTITY_ADDITIONAL_INFO_H
