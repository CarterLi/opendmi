//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/name.h>
#include <opendmi/utils.h>
#include <opendmi/table/memory-array.h>

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

const dmi_attribute_t dmi_memory_array_attrs[] =
{
    DMI_ATTRIBUTE(dmi_memory_array_t, location, ENUM, {
        .code   = "location",
        .name   = "Location",
        .values = dmi_memory_array_location_names
    }),
    DMI_ATTRIBUTE(dmi_memory_array_t, usage, ENUM, {
        .code   = "use",
        .name   = "Use",
        .values = dmi_memory_array_usage_names
    }),
    DMI_ATTRIBUTE(dmi_memory_array_t, ecc_type, ENUM, {
        .code   = "error-correction",
        .name   = "Memory error correction",
        .values = dmi_ecc_type_names
    }),
    DMI_ATTRIBUTE(dmi_memory_array_t, maximum_capacity, SIZE, {
        .code = "maximum-capacity",
        .name = "Maximum capacity"
    }),
    DMI_ATTRIBUTE(dmi_memory_array_t, error_handle, HANDLE, {
        .code = "error-handle",
        .name = "Memory error information handle"
    }),
    DMI_ATTRIBUTE(dmi_memory_array_t, device_count, INTEGER, {
        .code = "device-count",
        .name = "Number of memory devices"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_array_table =
{
    .tag         = "memory-array",
    .name        = "Physical memory array",
    .type        = DMI_TYPE_MEMORY_ARRAY,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x0F,
    .attributes  = dmi_memory_array_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_memory_array_decode,
        .free   = (dmi_table_free_fn_t)dmi_memory_array_free
    }
};

const char *dmi_memory_array_location_name(enum dmi_memory_array_location value)
{
    return dmi_name_lookup(dmi_memory_array_location_names, value);
}

const char *dmi_memory_array_usage_name(enum dmi_memory_array_usage value)
{
    return dmi_name_lookup(dmi_memory_array_usage_names, value);
}

dmi_memory_array_t *dmi_memory_array_decode(const dmi_table_t *table)
{
    dmi_memory_array_t *info = nullptr;
    dmi_memory_array_data_t *data = dmi_cast(data, table->data);
    dmi_dword_t maximum_capacity;

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    info->location = data->location;
    info->usage    = data->usage;
    info->ecc_type = data->ecc_type;

    maximum_capacity = dmi_value(data->maximum_capacity);
    if ((table->body_length >= 0x0F) && (maximum_capacity & 0x80000000))
        info->maximum_capacity = dmi_value(data->maximum_capacity_ex);
    else
        info->maximum_capacity  = (dmi_size_t)(maximum_capacity & 0x7FFFFFFFU) << 10;

    info->error_handle = dmi_value(data->error_handle);
    info->device_count = dmi_value(data->device_count);

    return info;
}

void dmi_memory_array_free(dmi_memory_array_t *info)
{
    free(info);
}
