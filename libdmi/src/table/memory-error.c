//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-error.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_memory_error_type_names[] =
{
    {
        .id   = DMI_MEMORY_ERROR_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_OK,
        .code = "ok",
        .name = "OK"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_BAD_READ,
        .code = "bad-read",
        .name = "Bad read"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_PARITY,
        .code = "parity",
        .name = "Parity error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_SINGLE_BIT,
        .code = "single-bit",
        .name = "Single-bit error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_DOUBLE_BIT,
        .code = "double-bit",
        .name = "Double-bit error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_MULTI_BIT,
        .code = "multi-bit",
        .name = "Multi-bit error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_NIBBLE,
        .code = "nibble",
        .name = "Nibble error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_CHECKSUM,
        .code = "checksum",
        .name = "Checksum error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_CRC,
        .code = "crc",
        .name = "CRC error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_CORRECTED_SINGLE_BIT,
        .code = "corrected-single-bit",
        .name = "Corrected single-bit error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_CORRECTED,
        .code = "corrected",
        .name = "Corrected error"
    },
    {
        .id   = DMI_MEMORY_ERROR_TYPE_UNCORRECTABLE,
        .code = "uncorrectable",
        .name = "Uncorrectable error"
    },
    DMI_NAME_NULL
};  

static const dmi_name_t dmi_memory_error_granularity_names[] =
{
    {
        .id   = DMI_MEMORY_ERROR_GRANULARITY_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_ERROR_GRANULARITY_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_ERROR_GRANULARITY_DEVICE,
        .code = "device",
        .name = "Device level"
    },
    {
        .id   = DMI_MEMORY_ERROR_GRANULARITY_PARTITION,
        .code = "partition",
        .name = "Memory partition level"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_memory_error_operation_names[] =
{
    {
        .id   = DMI_MEMORY_ERROR_OPERATION_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_ERROR_OPERATION_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_ERROR_OPERATION_READ,
        .code = "read",
        .name = "Read"
    },
    {
        .id   = DMI_MEMORY_ERROR_OPERATION_WRITE,
        .code = "write",
        .name = "Write"
    },
    {
        .id   = DMI_MEMORY_ERROR_OPERATION_PARTIAL_WRITE,
        .code = "partial-write",
        .name = "Partial write"
    },
    DMI_NAME_NULL
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
    return dmi_name_lookup(dmi_memory_error_type_names, value);
}

const char *dmi_memory_error_granularity_name(enum dmi_memory_error_granularity value)
{
    return dmi_name_lookup(dmi_memory_error_granularity_names, value);
}

const char *dmi_memory_error_operation_name(enum dmi_memory_error_operation value)
{
    return dmi_name_lookup(dmi_memory_error_operation_names, value);
}
