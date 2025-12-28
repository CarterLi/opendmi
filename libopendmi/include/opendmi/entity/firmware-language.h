//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_FIRMWARE_LANGUAGE_H
#define OPENDMI_ENTITY_FIRMWARE_LANGUAGE_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_firmware_language       dmi_firmware_language_t;
typedef struct dmi_firmware_language_data  dmi_firmware_language_data_t;
typedef union  dmi_firmware_language_flags dmi_firmware_language_flags_t;

/**
 * @brief Firmware language flags
 */
dmi_packed_union(dmi_firmware_language_flags)
{
    /**
     * @brief Raw value.
     */
    dmi_byte_t _value;

    dmi_packed_struct()
    {
        /**
         * @brief If set to `true`, the current language strings use the
         * abbreviated format. Otherwise, the strings use the long format.
         */
        bool is_abbreviated : 1;

        /**
         * @brief Reserved for future use.
         */
        dmi_byte_t reserved: 7;
    };
};

/**
 * @brief Firmware language information structure (type 13).
 */
dmi_packed_struct(dmi_firmware_language_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Number of languages available. Each available language has a
     * description string. This field contains the number of strings that
     * follow the formatted area of the structure.
     *
     * @since SMBIOS 2.0
     */
    dmi_byte_t language_count;

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
    dmi_string_t current_language;
};

struct dmi_firmware_language
{
    /**
     * @brief Number of languages available.
     */
    size_t language_count;

    /**
     * @brief List of available languages.
     */
    const char **languages;

    /**
     * @brief If set to `true`, the language strings use the abbreviated
     * format. Otherwise, the strings use the long format.
     */
    bool is_abbreviated;

    /**
     * @brief Currently installed language.
     */
    const char *current_language;
};

/**
 * @brief Firmware language information entity specification.
 */
extern const dmi_entity_spec_t dmi_firmware_language_spec;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_firmware_language_t *dmi_firmware_language_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
void dmi_firmware_language_free(dmi_firmware_language_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_FIRMWARE_LANGUAGE_H
