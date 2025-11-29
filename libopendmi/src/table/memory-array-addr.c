//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/table/memory-array-addr.h>

const dmi_attribute_t dmi_memory_array_addr_attrs[] =
{
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, start_addr, ADDRESS, {
        .code   = "start-addr",
        .name   = "Starting address"
    }),
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, end_addr, ADDRESS, {
        .code  = "end-addr",
        .name  = "Ending address"
    }),
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, range_size, SIZE, {
        .code   = "range-size",
        .name   = "Range size"
    }),
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, array_handle, HANDLE, {
        .code   = "array-handle",
        .name   = "Memory array handle"
    }),
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, partition_width, INTEGER, {
        .code   = "partition-width",
        .name   = "Partition width"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_array_addr_table =
{
    .code        = "memory-array-address",
    .name        = "Memory array mapped address",
    .type        = DMI_TYPE_MEMORY_ARRAY_ADDR,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x0F,
    .attributes  = dmi_memory_array_addr_attrs,
    .handlers    = {
        .validate = (dmi_table_validate_fn_t)dmi_memory_array_addr_validate,
        .decode   = (dmi_table_decode_fn_t)dmi_memory_array_addr_decode,
        .free     = (dmi_table_free_fn_t)dmi_memory_array_addr_free
    }
};

bool dmi_memory_array_addr_validate(dmi_table_t *table)
{
    dmi_memory_array_addr_data_t *data = dmi_cast(data, table->data);

    if (data->start_addr == 0xFFFFFFFFU) {
        if (data->end_addr != 0xFFFFFFFFU)
            return false;

        if (table->total_length < 0x1F)
            return false;
        if (data->end_addr_ex <= data->start_addr_ex)
            return false;
    } else {
        if (data->end_addr == 0xFFFFFFFFU)
            return false;
        if (data->end_addr <= data->start_addr)
            return false;            

        if (table->total_length >= 0x1F) {
            if (data->start_addr_ex != 0)
                return false;
            if (data->end_addr_ex != 0)
                return false;
        }
    }

    return true;
}

dmi_memory_array_addr_t *dmi_memory_array_addr_decode(dmi_table_t *table)
{
    dmi_memory_array_addr_t *info;
    const dmi_memory_array_addr_data_t *data;
    
    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_MEMORY_ARRAY_ADDR) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    if ((table->body_length >= 0x1F) and (data->start_addr == 0xFFFFFFFFU)) {
        info->start_addr = dmi_value(data->start_addr_ex);
        info->end_addr   = dmi_value(data->end_addr_ex);
    } else {
        info->start_addr = dmi_value(data->start_addr) << 10;
        info->end_addr   = dmi_value(data->end_addr) << 10;
    }

    if (info->end_addr > info->start_addr)
        info->range_size = info->end_addr - info->start_addr;
    else
        info->range_size = info->start_addr - info->end_addr;

    info->array_handle    = dmi_value(data->array_handle);
    info->partition_width = dmi_value(data->partition_width);

    return info;
}

void dmi_memory_array_addr_free(dmi_memory_array_addr_t *info)
{
    free(info);
}
