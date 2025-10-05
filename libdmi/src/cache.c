//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/cache.h>
#include <opendmi/utils.h>

#include <stdlib.h>
#include <errno.h>

static const char *dmi_cache_type_names[__DMI_CACHE_TYPE_COUNT] =
{
    [DMI_CACHE_TYPE_OTHER]       = "Other",
    [DMI_CACHE_TYPE_UNKNOWN]     = "Unknown",
    [DMI_CACHE_TYPE_INSTRUCTION] = "Instruction",
    [DMI_CACHE_TYPE_DATA]        = "Data",
    [DMI_CACHE_TYPE_UNIFIED]     = "Unified"
};

static const char *dmi_cache_mode_names[__DMI_CACHE_MODE_COUNT] =
{
    [DMI_CACHE_MODE_WRITE_THROUGH] = "Write-through",
    [DMI_CACHE_MODE_WRITE_BACK]    = "Write-back",
    [DMI_CACHE_MODE_VARIABLE]      = "Variable",
    [DMI_CACHE_MODE_UNKNOWN]       = "Unknown"
};

static const char *dmi_cache_ecc_type_names[__DMI_CACHE_ECC_TYPE_COUNT] =
{
    [DMI_CACHE_ECC_OTHER]      = "Other",
    [DMI_CACHE_ECC_UNKNOWN]    = "Unknown",
    [DMI_CACHE_ECC_NONE]       = "None",
    [DMI_CACHE_ECC_PARITY]     = "Parity",
    [DMI_CACHE_ECC_SINGLE_BIT] = "Single-bit ECC",
    [DMI_CACHE_ECC_MULTI_BIT]  = "Multi-bit ECC"
};

static const char *dmi_cache_assoc_names[__DMI_CACHE_ASSOC_COUNT] =
{
    [DMI_CACHE_ASSOC_OTHER]   = "Other",
    [DMI_CACHE_ASSOC_UNKNOWN] = "Unknown",
    [DMI_CACHE_ASSOC_DIRECT]  = "Direct mapped",
    [DMI_CACHE_ASSOC_2WAY]    = "2-way set-associative",
    [DMI_CACHE_ASSOC_4WAY]    = "4-way set-associative",
    [DMI_CACHE_ASSOC_FULL]    = "Fully associative",
    [DMI_CACHE_ASSOC_8WAY]    = "8-way set-associative",
    [DMI_CACHE_ASSOC_16WAY]   = "16-way set-associative",
    [DMI_CACHE_ASSOC_12WAY]   = "12-way set-associative",
    [DMI_CACHE_ASSOC_24WAY]   = "24-way set-associative",
    [DMI_CACHE_ASSOC_32WAY]   = "32-way set-associative",
    [DMI_CACHE_ASSOC_48WAY]   = "48-way set-associative",
    [DMI_CACHE_ASSOC_64WAY]   = "64-way set-associative",
    [DMI_CACHE_ASSOC_20WAY]   = "20-way set-associative"
};

static const char *dmi_cache_location_names[__DMI_CACHE_LOCATION_COUNT] =
{
    [DMI_CACHE_LOCATION_INTERNAL] = "Internal",
    [DMI_CACHE_LOCATION_EXTERNAL] = "External",
    [DMI_CACHE_LOCATION_RESERVED] = "Reserved",
    [DMI_CACHE_LOCATION_UNKNOWN]  = "Unknown"
};

const char *dmi_cache_type_name(enum dmi_cache_type value)
{
    return dmi_name(dmi_cache_type_names, value, __DMI_CACHE_TYPE_COUNT);
}

const char *dmi_cache_mode_name(enum dmi_cache_mode value)
{
    return dmi_name(dmi_cache_mode_names, value, __DMI_CACHE_MODE_COUNT);
}

const char *dmi_cache_ecc_type_name(enum dmi_cache_ecc_type value)
{
    return dmi_name(dmi_cache_ecc_type_names, value, __DMI_CACHE_ECC_TYPE_COUNT);
}

const char *dmi_cache_assoc_name(enum dmi_cache_assoc value)
{
    return dmi_name(dmi_cache_assoc_names, value, __DMI_CACHE_ASSOC_COUNT);
}

const char *dmi_cache_location_name(enum dmi_cache_location value)
{
    return dmi_name(dmi_cache_location_names, value, __DMI_CACHE_LOCATION_COUNT);
}

struct dmi_cache_info *dmi_cache_info_create(struct dmi_cache_table *table)
{
    struct dmi_cache_info *info;

    if (!table) {
        errno = EINVAL;
        return nullptr;
    }

    info = malloc(sizeof(struct dmi_cache_info));
    if (!info) {
        errno = ENOMEM;
        return nullptr;
    }

    return info;
}

void dmi_cache_info_destroy(struct dmi_cache_info *info)
{
    if (!info)
        return;

    free(info);
}

size_t dmi_cache_size(dmi_cache_size_t value)
{
    size_t size = value & 0x7FFFU;

    if (value & 0x8000U)
        size <<= 16; // Granularity is 64 Kb
    else
        size <<= 10; // Granularity is 1 Kb

    return size;
}

size_t dmi_cache_size_ex(dmi_cache_size_ex_t value)
{
    size_t size = value & 0x7FFFFFFFU;

    if (value & 0x80000000U)
        size <<= 16; // Granularity is 64 Kb
    else
        size <<= 10; // Granularity is 1 Kb

    return size;
}
