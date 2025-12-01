//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_CACHE_H
#define OPENDMI_TABLE_CACHE_H

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <opendmi/table.h>
#include <opendmi/table/common.h>

/**
 * @brief Cache types.
 */
typedef enum dmi_cache_type
{
    DMI_CACHE_TYPE_OTHER       = 0x01, ///< Other
    DMI_CACHE_TYPE_UNKNOWN     = 0x02, ///< Unknown
    DMI_CACHE_TYPE_INSTRUCTION = 0x03, ///< Instruction cache
    DMI_CACHE_TYPE_DATA        = 0x04, ///< Data cache
    DMI_CACHE_TYPE_UNIFIED     = 0x05, ///< Unified cache
    __DMI_CACHE_TYPE_COUNT
} dmi_cache_type_t;

/**
 * @brief Cache operational modes.
 */
typedef enum dmi_cache_mode
{
    DMI_CACHE_MODE_WRITE_THROUGH = 0x00, ///< Write through
    DMI_CACHE_MODE_WRITE_BACK    = 0x01, ///< Write back
    DMI_CACHE_MODE_VARIABLE      = 0x02, ///< Varies with memory address
    DMI_CACHE_MODE_UNKNOWN       = 0x03, ///< Unknown
    __DMI_CACHE_MODE_COUNT
} dmi_cache_mode_t;

/**
 * @brief Cache associativity types.
 */
typedef enum dmi_cache_assoc
{
    DMI_CACHE_ASSOC_OTHER   = 0x01, ///< Other
    DMI_CACHE_ASSOC_UNKNOWN = 0x02, ///< Unknown
    DMI_CACHE_ASSOC_DIRECT  = 0x03, ///< Direct mapped
    DMI_CACHE_ASSOC_2WAY    = 0x04, ///< 2-way set-associative
    DMI_CACHE_ASSOC_4WAY    = 0x05, ///< 4-way set-associative
    DMI_CACHE_ASSOC_FULL    = 0x06, ///< Fully associative
    DMI_CACHE_ASSOC_8WAY    = 0x07, ///< 8-way set-associative
    DMI_CACHE_ASSOC_16WAY   = 0x08, ///< 16-way set-associative
    DMI_CACHE_ASSOC_12WAY   = 0x09, ///< 12-way set-associative
    DMI_CACHE_ASSOC_24WAY   = 0x0A, ///< 24-way set-associative
    DMI_CACHE_ASSOC_32WAY   = 0x0B, ///< 32-way set-associative
    DMI_CACHE_ASSOC_48WAY   = 0x0C, ///< 48-way set-associative
    DMI_CACHE_ASSOC_64WAY   = 0x0D, ///< 64-way set-associative
    DMI_CACHE_ASSOC_20WAY   = 0x0E, ///< 20-way set-associative
    __DMI_CACHE_ASSOC_COUNT
} dmi_cache_assoc_t;

/**
 * @brief Cache location, relative to the CPU module.
 */
typedef enum dmi_cache_location
{
    DMI_CACHE_LOCATION_INTERNAL = 0x00, ///< Internal
    DMI_CACHE_LOCATION_EXTERNAL = 0x01, ///< External
    DMI_CACHE_LOCATION_RESERVED = 0x02, ///< Reserved
    DMI_CACHE_LOCATION_UNKNOWN  = 0x03, ///< Unknown
    __DMI_CACHE_LOCATION_COUNT
} dmi_cache_location_t;

/**
 * @brief Cache configuration.
 */
DMI_PACKED_UNION(dmi_cache_config)
{
    /**
     * @brief Raw value.
     */
    dmi_word_t _value;

    DMI_PACKED_STRUCT()
    {
        /**
         * @brief Cache Level – 1 through 8. For example, an L1 cache would use
         * value 0x0 and an L3 cache would use 0x2.
         */
        dmi_word_t level : 3;

        /**
         * @brief Socketed cache flag (e.g., cache on a stick).
         */
        bool socketed : 1;

        /**
         * @brief Reserved.
         */
        dmi_word_t reserved : 1;

        /**
         * @brief Location, relative to the CPU module.
         */
        dmi_word_t location : 2;

        /**
         * @brief Enable flag (at boot time).
         */
        bool enabled : 1;

        /**
         * @brief Operational mode.
         */
        dmi_word_t mode : 2;
    };
};

#ifndef DMI_CACHE_CONFIG_T
#define DMI_CACHE_CONFIG_T
typedef union dmi_cache_config dmi_cache_config_t;
#endif // !DMI_CACHE_CONFIG_T

/**
 * @brief Cache SRAM type.
 */
DMI_PACKED_UNION(dmi_cache_sram_type)
{
    /**
     * @brief Encoded type value.
     */
    dmi_word_t _value;

    DMI_PACKED_STRUCT()
    {
        bool other          : 1; ///< Other
        bool unknown        : 1; ///< Unknown
        bool non_burst      : 1; ///< Non-burst
        bool burst          : 1; ///< Burst
        bool pipeline_burst : 1; ///< Pipeline burst
        bool synchonous     : 1; ///< Synchronous
        bool asynchronous   : 1; ///< Asynchronous
    };
};

#ifndef DMI_CACHE_SRAM_TYPE_T
#define DMI_CACHE_SRAM_TYPE_T
typedef union dmi_cache_sram_type dmi_cache_sram_type_t;
#endif // !DMI_CACHE_SRAM_TYPE_T

/**
 * @brief Cache information table (type 7).
 * 
 * The information in this structure defines the attributes of CPU cache
 * device in the system. One structure is specified for each such device,
 * whether the device is internal to or external to the CPU module. Cache
 * modules can be associated with a processor structure in one or two ways
 * depending on the SMBIOS version.
 */
DMI_PACKED_STRUCT(dmi_cache_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief String number for reference designation, e.g. "CACHE1", 0.
     * @since SMBIOS 2.0
     */
    dmi_string_t socket_designator;

    /**
     * @brief Cache configuration.
     * @since SMBIOS 2.0
     */
    dmi_word_t config;

    /**
     * @brief Maximum cache size that can be installed.
     * @since SMBIOS 2.0
     */
    dmi_word_t maximum_size;

    /**
     * @brief Installed cache size, set to 0 if no cache is installed.
     * @since SMBIOS 2.0
     */
    dmi_word_t installed_size;

    /**
     * @brief Supported SRAM type.
     * @since SMBIOS 2.0
     */
    dmi_word_t supported_sram;

    /**
     * @brief Current SRAM type.
     * @since SMBIOS 2.0
     */
    dmi_word_t current_sram;

    /**
     * @brief Cache module speed, in nanoseconds. The value is 0 if the speed
     * is unknown.
     *
     * @since SMBIOS 2.1
     */
    dmi_byte_t speed;

    /**
     * @brief Error-correction scheme supported by this cache component.
     * @since SMBIOS 2.1
     */
    dmi_byte_t ecc_type;

    /**
     * @brief Logical type of cache.
     * @since SMBIOS 2.1
     */
    dmi_byte_t type;

    /**
     * @brief Associativity of the cache.
     * @since SMBIOS 2.1
     */
    dmi_byte_t associativity;

    /**
     * @brief Maximum cache size that can be installed (for caches larger than
     * 2047 MiB).
     * @since SMBIOS 3.1
     */
    dmi_dword_t maximum_size_ex;

    /**
     * @brief Installed cache size (for caches larget than 2047 MiB).
     * @since SMBIOS 3.1
     */
    dmi_dword_t installed_size_ex;
};

#ifndef DMI_CACHE_DATA_T
#define DMI_CACHE_DATA_T
typedef struct dmi_cache_data dmi_cache_data_t;
#endif // !DMI_CACHE_DATA_T

/**
 * @brief Decoded cache information.
 */
struct dmi_cache
{
    /**
     * @brief Socket designator.
     */
    const char *socket_designator;

    /**
     * @brief Cache level, 1 to 8.
     */
    unsigned short level;

    /**
     * @brief Socketed cache flag (e.g., cache on a stick).
     */
    bool socketed;

    /**
     * @brief Location, relative to the CPU module.
     */
    dmi_cache_location_t location;

    /**
     * @brief Enable flag (at boot time).
     */
    bool enabled;

    /**
     * @brief Operational mode.
     */
    dmi_cache_mode_t mode;

    /**
     * @brief Maximum cache size that can be installed, in bytes.
     */
    dmi_size_t maximum_size;

    /**
     * @brief Installed cache size, in bytes.
     */
    dmi_size_t installed_size;

    /**
     * @brief Supported SRAM type.
     */
    dmi_cache_sram_type_t supported_sram;

    /**
     * @brief Current SRAM type.
     */
    dmi_cache_sram_type_t current_sram;

    /**
     * @brief Cache module speed, in nanoseconds. The value is 0 if the speed
     * is unknown.
     */
    unsigned int speed;

    /**
     * @brief Error-correction scheme supported by this cache component.
     */
    dmi_ecc_type_t ecc_type;

    /**
     * @brief Logical type of cache.
     */
    dmi_cache_type_t type;

    /**
     * @brief Associativity of the cache.
     */
    dmi_cache_assoc_t associativity;
};

#ifndef DMI_CACHE_T
#define DMI_CACHE_T
typedef struct dmi_cache dmi_cache_t;
#endif // !DMI_CACHE_T

/**
 * @brief Cache information table specification.
 */
extern const struct dmi_table_spec dmi_cache_table;

__BEGIN_DECLS

const char *dmi_cache_type_name(dmi_cache_type_t value);
const char *dmi_cache_mode_name(dmi_cache_mode_t value);
const char *dmi_cache_assoc_name(dmi_cache_assoc_t value);
const char *dmi_cache_location_name(dmi_cache_location_t value);

dmi_size_t dmi_cache_size(uint16_t value);
dmi_size_t dmi_cache_size_ex(uint32_t value);

/**
 * @internal
 */
dmi_cache_t *dmi_cache_decode(const dmi_table_t *table);

/**
 * @internal
 */
void dmi_cache_free(dmi_cache_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_CACHE_H
