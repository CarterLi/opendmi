//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/table/memory-array-addr.h>

static bool dmi_memory_array_addr_decode(dmi_table_t *table);
static bool dmi_memory_array_addr_validate(dmi_table_t *table);
static void dmi_memory_array_addr_free(dmi_table_t *table);

const dmi_attribute_spec_t dmi_memory_array_addr_attrs[] =
{
    {
        .code   = "starting-address",
        .name   = "Starting address",
        .offset = offsetof(dmi_memory_array_addr_t, starting_addr),
        .type   = DMI_ATTRIBUTE_TYPE_SIZE,
        .format = DMI_ATTRIBUTE_FORMAT_HEX
    },
    {
        .code   = "ending-address",
        .name   = "Ending address",
        .offset = offsetof(dmi_memory_array_addr_t, ending_addr),
        .type   = DMI_ATTRIBUTE_TYPE_SIZE,
        .format = DMI_ATTRIBUTE_FORMAT_HEX
    },
    {
        .code   = "array-handle",
        .name   = "Memory array handle",
        .offset = offsetof(dmi_memory_array_addr_t, array_handle),
        .type   = DMI_ATTRIBUTE_TYPE_HANDLE
    },
    {
        .code   = "partition-width",
        .name   = "Partition width",
        .offset = offsetof(dmi_memory_array_addr_t, partition_width),
        .type   = DMI_ATTRIBUTE_TYPE_INT
    },
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_array_addr_table =
{
    .tag         = "memory-array-address",
    .name        = "Memory array mapped address",
    .type        = DMI_TYPE_MEMORY_ARRAY_ADDR,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x0F,
    .decode      = dmi_memory_array_addr_decode,
    .validate    = dmi_memory_array_addr_validate,
    .free        = dmi_memory_array_addr_free,
    .attributes  = dmi_memory_array_addr_attrs
};

static bool dmi_memory_array_addr_decode(dmi_table_t *table)
{
    dmi_memory_array_addr_t *info = nullptr;
    dmi_memory_array_addr_data_t *data = dmi_cast(data, table->data);
    
    info = calloc(1, sizeof(*info));
    if (!info)
        return false;

    if ((table->total_length >= 0x1F) && (data->starting_addr == 0xFFFFFFFFU)) {
        info->starting_addr = data->starting_addr_ex;
        info->ending_addr   = data->ending_addr_ex;
    } else {
        info->starting_addr = data->starting_addr << 10;
        info->ending_addr   = data->ending_addr << 10;
    }

    info->array_handle    = data->array_handle;
    info->partition_width = data->partition_width;

    table->info = info;

    return true;
}

static bool dmi_memory_array_addr_validate(dmi_table_t *table)
{
    dmi_memory_array_addr_data_t *data = dmi_cast(data, table->data);

    if (data->starting_addr == 0xFFFFFFFFU) {
        if (data->ending_addr != 0xFFFFFFFFU)
            return false;

        if (table->total_length < 0x1F)
            return false;
        if (data->ending_addr_ex <= data->starting_addr_ex)
            return false;
    } else {
        if (data->ending_addr == 0xFFFFFFFFU)
            return false;
        if (data->ending_addr <= data->starting_addr)
            return false;            

        if (table->total_length >= 0x1F) {
            if (data->starting_addr_ex != 0)
                return false;
            if (data->ending_addr_ex != 0)
                return false;
        }
    }

    return true;
}

static void dmi_memory_array_addr_free(dmi_table_t *table)
{
    free(table->info);
}
