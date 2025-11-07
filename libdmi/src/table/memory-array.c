//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-array.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_memory_array_location_names[] =
{
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_MOTHERBOARD,
        .code = "motherboard",
        .name = "System board or motherboard"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_ISA,
        .code = "isa",
        .name = "ISA add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_EISA,
        .code = "eisa",
        .name = "EISA add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_PCI,
        .code = "pci",
        .name = "PCI add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_MCA,
        .code = "mca",
        .name = "MCA add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_PCMCIA,
        .code = "pcmcia",
        .name = "PCMCIA add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_PROPRIETARY,
        .code = "proprietary",
        .name = "Proprietary add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_NUBUS,
        .code = "nubus",
        .name = "NuBus"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_PC_98_C20,
        .code = "pc-98-c20",
        .name = "PC-98/C20 add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_PC_98_C24,
        .code = "pc-98-c24",
        .name = "PC-98/C24 add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_PC_98_E,
        .code = "pc-98-e",
        .name = "PC-98/E add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_PC_98_LOCAL_BUS,
        .code = "pc-98-local-bus",
        .name = "PC-98/Local bus add-on card"
    },
    {
        .id   = DMI_MEMORY_ARRAY_LOCATION_CXL,
        .code = "cxl",
        .name = "CXL add-on card"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_memory_array_usage_names[] =
{
    {
        .id   = DMI_MEMORY_ARRAY_USAGE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_ARRAY_USAGE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_ARRAY_USAGE_SYSTEM,
        .code = "system",
        .name = "System memory"
    },
    {
        .id   = DMI_MEMORY_ARRAY_USAGE_VIDEO,
        .code = "video",
        .name = "Video memory"
    },
    {
        .id   = DMI_MEMORY_ARRAY_USAGE_FLASH,
        .code = "flash",
        .name = "Flash memory"
    },
    {
        .id   = DMI_MEMORY_ARRAY_USAGE_NVRAM,
        .code = "nvram",
        .name = "Non-volatile RAM"
    },
    {
        .id   = DMI_MEMORY_ARRAY_USAGE_CACHE,
        .code = "cache",
        .name = "Cache memory"
    },
    DMI_NAME_NULL
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

const char *dmi_memory_array_location_name(enum dmi_memory_array_location value)
{
    return dmi_name_lookup(dmi_memory_array_location_names, value);
}

const char *dmi_memory_array_usage_name(enum dmi_memory_array_usage value)
{
    return dmi_name_lookup(dmi_memory_array_usage_names, value);
}
