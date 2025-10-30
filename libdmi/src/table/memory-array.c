//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-array.h>
#include <opendmi/utils.h>

static const char *dmi_memory_array_location_names[__DMI_MEMORY_ARRAY_LOCATION_COUNT] =
{
    [DMI_MEMORY_ARRAY_LOCATION_OTHER]           = "Other",
    [DMI_MEMORY_ARRAY_LOCATION_UNKNOWN]         = "Unknown",
    [DMI_MEMORY_ARRAY_LOCATION_MOTHERBOARD]     = "System board or motherboard",
    [DMI_MEMORY_ARRAY_LOCATION_ISA]             = "ISA add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_EISA]            = "EISA add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_PCI]             = "PCI add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_MCA]             = "MCA add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_PCMCIA]          = "PCMCIA add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_PROPRIETARY]     = "Proprietary add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_NUBUS]           = "NuBus",
    [DMI_MEMORY_ARRAY_LOCATION_PC_98_C20]       = "PC-98/C20 add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_PC_98_C24]       = "PC-98/C24 add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_PC_98_E]         = "PC-98/E add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_PC_98_LOCAL_BUS] = "PC-98/Local bus add-on card",
    [DMI_MEMORY_ARRAY_LOCATION_CXL]             = "CXL add-on card"
};

static const char *dmi_memory_array_usage_names[__DMI_MEMORY_ARRAY_USAGE_COUNT] =
{
    [DMI_MEMORY_ARRAY_USAGE_OTHER]   = "Other",
    [DMI_MEMORY_ARRAY_USAGE_UNKNOWN] = "Unknown",
    [DMI_MEMORY_ARRAY_USAGE_SYSTEM]  = "System memory",
    [DMI_MEMORY_ARRAY_USAGE_VIDEO]   = "Video memory",
    [DMI_MEMORY_ARRAY_USAGE_FLASH]   = "Flash memory",
    [DMI_MEMORY_ARRAY_USAGE_NVRAM]   = "Non-volatile RAM",
    [DMI_MEMORY_ARRAY_USAGE_CACHE]   = "Cache memory"
};

const dmi_attribute_spec_t dmi_memory_array_attrs[] =
{
    {
        .tag  = "location",
        .name = "Location",
        .type = DMI_ATTRIBUTE_TYPE_ENUM
    },
    {
        .tag  = "use",
        .name = "Use",
        .type = DMI_ATTRIBUTE_TYPE_ENUM
    },
    {
        .tag  = "error-correction",
        .name = "Memory error correction",
        .type = DMI_ATTRIBUTE_TYPE_ENUM
    },
    {
        .tag = "maximum-capacity",
        .name = "Maximum capacity",
        .type = DMI_ATTRIBUTE_TYPE_SIZE
    },
    {
        .tag  = "error-information",
        .name = "Memory error information handle",
        .type = DMI_ATTRIBUTE_TYPE_HANDLE
    },
    {
        .tag  = "device-count",
        .name = "Number of memory devices",
        .type = DMI_ATTRIBUTE_TYPE_INT
    },
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_memory_array_table =
{
    .tag         = "memory-array",
    .name        = "Physical memory array",
    .type        = DMI_TYPE_MEMORY_ARRAY,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x0F,
    .attributes  = dmi_memory_array_attrs
};

const dmi_attribute_spec_t dmi_memory_array_addr_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_memory_array_addr_table =
{
    .tag         = "memory-array-address",
    .name        = "Memory array mapped address",
    .type        = DMI_TYPE_MEMORY_ARRAY_ADDR,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x0F,
    .attributes  = dmi_memory_array_addr_attrs
};

const char *dmi_memory_array_location_name(enum dmi_memory_array_location value)
{
    return dmi_name(dmi_memory_array_location_names, value, __DMI_MEMORY_ARRAY_LOCATION_COUNT);
}

const char *dmi_memory_array_usage_name(enum dmi_memory_array_usage value)
{
    return dmi_name(dmi_memory_array_usage_names, value, __DMI_MEMORY_ARRAY_USAGE_COUNT);
}
