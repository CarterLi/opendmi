//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_FIRMWARE_LANGUAGE_H
#define OPENDMI_TABLE_FIRMWARE_LANGUAGE_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_FIRMWARE_LANGUAGE_T
#define DMI_FIRMWARE_LANGUAGE_T
typedef struct dmi_firmware_language dmi_firmware_language_t;
#endif // !DMI_FIRMWARE_LANGUAGE_T

#ifndef DMI_FIRMWARE_LANGUAGE_DATA_T
#define DMI_FIRMWARE_LANGUAGE_DATA_T
typedef struct dmi_firmware_language_data dmi_firmware_language_data_t;
#endif // !DMI_FIRMWARE_LANGUAGE_DATA_T

#ifndef DMI_FIRMWARE_LANGUAGE_FLAGS_T
#define DMI_FIRMWARE_LANGUAGE_FLAGS_T
typedef union dmi_firmware_language_flags dmi_firmware_language_flags_t;
#endif // !DMI_FIRMWARE_LANGUAGE_FLAGS_T

/**
 * @brief Firmware language flags
 */
DMI_PACKED_UNION(dmi_firmware_language_flags)
{
    /**
     * @brief Raw value.
     */
    dmi_byte_t _value;

    DMI_PACKED_STRUCT()
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
 * @brief Firmware language information table (type 13).
 */
DMI_PACKED_STRUCT(dmi_firmware_language_data)
{
    /**
     * @brief DMI table header.
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
 * @brief Firmware language information table specification.
 */
extern const dmi_table_spec_t dmi_firmware_language_table;

__BEGIN_DECLS

dmi_firmware_language_t *dmi_firmware_language_decode(const dmi_table_t *table);
void dmi_firmware_language_free(dmi_firmware_language_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_FIRMWARE_LANGUAGE_H
