//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/utils.h>
#include <opendmi/table/memory-array-addr.h>

const dmi_attribute_t dmi_memory_array_addr_attrs[] =
{
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, starting_addr, ADDRESS, {
        .code   = "starting-address",
        .name   = "Starting address",
        .format = DMI_ATTRIBUTE_FORMAT_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, ending_addr, ADDRESS, {
        .code   = "ending-address",
        .name   = "Ending address",
        .format = DMI_ATTRIBUTE_FORMAT_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, range_size, SIZE, {
        .code   = "range-size",
        .name   = "Range size"
    }),
    DMI_ATTRIBUTE(dmi_memory_array_addr_t, memory_array_handle, HANDLE, {
        .code   = "memory-array-handle",
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
    .tag         = "memory-array-address",
    .name        = "Memory array mapped address",
    .type        = DMI_TYPE_MEMORY_ARRAY_ADDR,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x0F,
    .attributes  = dmi_memory_array_addr_attrs,
    .handlers    = {
        .validator   = (dmi_table_validator_t)dmi_memory_array_addr_validate,
        .decoder     = (dmi_table_decoder_t)dmi_memory_array_addr_decode,
        .deallocator = (dmi_table_deallocator_t)dmi_memory_array_addr_destroy
    }
};

bool dmi_memory_array_addr_validate(dmi_table_t *table)
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

dmi_memory_array_addr_t *dmi_memory_array_addr_decode(dmi_table_t *table)
{
    dmi_memory_array_addr_t *info = nullptr;
    dmi_memory_array_addr_data_t *data = dmi_cast(data, table->data);
    
    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    if ((table->body_length >= 0x1F) && (data->starting_addr == 0xFFFFFFFFU)) {
        info->starting_addr = dmi_decode_qword(data->starting_addr_ex);
        info->ending_addr   = dmi_decode_qword(data->ending_addr_ex);
    } else {
        info->starting_addr = dmi_decode_dword(data->starting_addr) << 10;
        info->ending_addr   = dmi_decode_dword(data->ending_addr) << 10;
    }

    if (info->ending_addr > info->starting_addr)
        info->range_size = info->ending_addr - info->starting_addr;
    else
        info->range_size = info->starting_addr - info->ending_addr;

    info->memory_array_handle = dmi_decode_word(data->memory_array_handle);
    info->partition_width     = data->partition_width;

    return info;
}

void dmi_memory_array_addr_destroy(dmi_memory_array_addr_t *info)
{
    free(info);
}
