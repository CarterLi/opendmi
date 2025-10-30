//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-error.h>
#include <opendmi/utils.h>

static const char *dmi_memory_error_type_names[__DMI_MEMORY_ERROR_TYPE_COUNT] =
{
    [DMI_MEMORY_ERROR_TYPE_OTHER]                = "Other",
    [DMI_MEMORY_ERROR_TYPE_UNKNOWN]              = "Unknown",
    [DMI_MEMORY_ERROR_TYPE_OK]                   = "OK",
    [DMI_MEMORY_ERROR_TYPE_BAD_READ]             = "Bad read",
    [DMI_MEMORY_ERROR_TYPE_PARITY]               = "Parity error",
    [DMI_MEMORY_ERROR_TYPE_SINGLE_BIT]           = "Single-bit error",
    [DMI_MEMORY_ERROR_TYPE_DOUBLE_BIT]           = "Double-bit error",
    [DMI_MEMORY_ERROR_TYPE_MULTI_BIT]            = "Multi-bit error",
    [DMI_MEMORY_ERROR_TYPE_NIBBLE]               = "Nibble error",
    [DMI_MEMORY_ERROR_TYPE_CHECKSUM]             = "Checksum error",
    [DMI_MEMORY_ERROR_TYPE_CRC]                  = "CRC error",
    [DMI_MEMORY_ERROR_TYPE_CORRECTED_SINGLE_BIT] = "Corrected single-bit error",
    [DMI_MEMORY_ERROR_TYPE_CORRECTED]            = "Corrected error",
    [DMI_MEMORY_ERROR_TYPE_UNCORRECTABLE]        = "Uncorrectable error"
};

static const char *dmi_memory_error_granularity_names[__DMI_MEMORY_ERROR_GRANULARITY_COUNT] =
{
    [DMI_MEMORY_ERROR_GRANULARITY_OTHER]     = "Other",
    [DMI_MEMORY_ERROR_GRANULARITY_UNKNOWN]   = "Unknown",
    [DMI_MEMORY_ERROR_GRANULARITY_DEVICE]    = "Device level",
    [DMI_MEMORY_ERROR_GRANULARITY_PARTITION] = "Memory partition level"
};

static const char *dmi_memory_error_operation_names[__DMI_MEMORY_ERROR_OPERATION_COUNT] =
{
    [DMI_MEMORY_ERROR_OPERATION_OTHER]         = "Other",
    [DMI_MEMORY_ERROR_OPERATION_UNKNOWN]       = "Unknown",
    [DMI_MEMORY_ERROR_OPERATION_READ]          = "Read",
    [DMI_MEMORY_ERROR_OPERATION_WRITE]         = "Write",
    [DMI_MEMORY_ERROR_OPERATION_PARTIAL_WRITE] = "Partial write"
};

const dmi_attribute_spec_t dmi_memory_error_32_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_memory_error_32_table =
{
    .tag         = "memory-error-32",
    .name        = "32-bit memory error information",
    .type        = DMI_TYPE_MEMORY_ERROR_32,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x17,
    .attributes  = dmi_memory_error_32_attrs
};

const dmi_attribute_spec_t dmi_memory_error_64_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_memory_error_64_table =
{
    .tag         = "memory-error-64",
    .name        = "64-bit memory error information",
    .type        = DMI_TYPE_MEMORY_ERROR_64,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x1F,
    .attributes  = dmi_memory_error_64_attrs
};

const char *dmi_memory_error_type_name(enum dmi_memory_error_type value)
{
    return dmi_name(dmi_memory_error_type_names, value, __DMI_MEMORY_ERROR_TYPE_COUNT);
}

const char *dmi_memory_error_granularity_name(enum dmi_memory_error_granularity value)
{
    return dmi_name(dmi_memory_error_granularity_names, value, __DMI_MEMORY_ERROR_GRANULARITY_COUNT);
}

const char *dmi_memory_error_operation_name(enum dmi_memory_error_operation value)
{
    return dmi_name(dmi_memory_error_operation_names, value, __DMI_MEMORY_ERROR_OPERATION_COUNT);
}
