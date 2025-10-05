//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_CACHE_H
#define OPENDMI_CACHE_H

#pragma once

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include <opendmi/table.h>

enum dmi_cache_type
{
    DMI_CACHE_TYPE_OTHER       = 0x01,
    DMI_CACHE_TYPE_UNKNOWN     = 0x02,
    DMI_CACHE_TYPE_INSTRUCTION = 0x03,
    DMI_CACHE_TYPE_DATA        = 0x04,
    DMI_CACHE_TYPE_UNIFIED     = 0x05
};

enum dmi_cache_mode
{
    DMI_CACHE_MODE_WRITE_THROUGH = 0x00,
    DMI_CACHE_MODE_WRITE_BACK    = 0x01,
    DMI_CACHE_MODE_VARIABLE      = 0x02,
    DMI_CACHE_MODE_UNKNOWN       = 0x03
};

/**
 * @brief Cache error correction types.
 */
enum dmi_cache_ecc_type
{
    DMI_CACHE_ECC_OTHER      = 0x01, /**< Other */
    DMI_CACHE_ECC_UNKNOWN    = 0x02, /**< Unknown */
    DMI_CACHE_ECC_NONE       = 0x03, /**< None */
    DMI_CACHE_ECC_PARITY     = 0x04, /**< Parity */
    DMI_CACHE_ECC_SINGLE_BIT = 0x05, /**< Single-bit ECC */
    DMI_CACHE_ECC_MULTI_BIT  = 0x06  /**< Multi-bit ECC */
};

enum dmi_cache_assoc
{
    DMI_CACHE_ASSOC_OTHER   = 0x01,
    DMI_CACHE_ASSOC_UNKNOWN = 0x02,
    DMI_CACHE_ASSOC_DIRECT  = 0x03,
    DMI_CACHE_ASSOC_2WAY    = 0x04,
    DMI_CACHE_ASSOC_4WAY    = 0x05,
    DMI_CACHE_ASSOC_FULL    = 0x06,
    DMI_CACHE_ASSOC_8WAY    = 0x07,
    DMI_CACHE_ASSOC_16WAY   = 0x08,
    DMI_CACHE_ASSOC_12WAY   = 0x09,
    DMI_CACHE_ASSOC_24WAY   = 0x0A,
    DMI_CACHE_ASSOC_32WAY   = 0x0B,
    DMI_CACHE_ASSOC_48WAY   = 0x0C,
    DMI_CACHE_ASSOC_64WAY   = 0x0D,
    DMI_CACHE_ASSOC_20WAY   = 0x0E
};

/**
 * @brief Cache location, relative to the CPU module.
 */
enum dmi_cache_location
{
    DMI_CACHE_LOCATION_INTERNAL = 0x00, /**< Internal */
    DMI_CACHE_LOCATION_EXTERNAL = 0x01, /**< External */
    DMI_CACHE_LOCATION_RESERVED = 0x02, /**< Reserved */
    DMI_CACHE_LOCATION_UNKNOWN  = 0x03  /**< Unknown */
};

struct dmi_cache_config
{
    uint8_t level : 3;
    bool socketed : 1;
    uint8_t reserved : 1;
    enum dmi_cache_location location : 2;
    bool enabled : 1;
    enum dmi_cache_mode mode : 2;
} __attribute__((packed));

struct dmi_cache_table
{
    struct dmi_table_header header;
} __attribute__((packed));

__BEGIN_DECLS

const char *dmi_cache_type_name(enum dmi_cache_type value);
const char *dmi_cache_mode_name(enum dmi_cache_mode value);
const char *dmi_cache_ecc_type_name(enum dmi_cache_ecc_type value);
const char *dmi_cache_assoc_name(enum dmi_cache_assoc value);
const char *dmi_cache_location_name(enum dmi_cache_location value);

size_t dmi_cache_size(uint16_t value);

__END_DECLS

#endif // !OPENDMI_CACHE_H
