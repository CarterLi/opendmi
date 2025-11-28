//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <limits.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/table/memory-device-addr.h>

const dmi_attribute_t dmi_memory_device_addr_attrs[] =
{
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, start_addr, ADDRESS, {
        .code = "start-addr",
        .name = "Starting address"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, end_addr, ADDRESS, {
        .code = "end-addr",
        .name = "Ending address"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, range_size, SIZE, {
        .code = "range-size",
        .name = "Range size"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, device_handle, HANDLE, {
        .code = "device-handle",
        .name = "Device handle"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, array_addr_handle, HANDLE, {
        .code = "array-addr-handle",
        .name = "Array mapped address handle"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, partition_pos, INTEGER, {
        .code = "partition-pos",
        .name = "Partition row position",
        .unknown = &(unsigned short) { USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, interleave_pos, INTEGER, {
        .code = "interleave-pos",
        .name = "Interleave position",
        .unknown = &(unsigned short) { USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_addr_t, interleave_depth, INTEGER, {
        .code    = "interleave-depth",
        .name    = "Interleave data depth",
        .unknown = &(unsigned short) { USHRT_MAX }
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_device_addr_table =
{
    .tag         = "memory-device-address",
    .name        = "Memory device mapped address",
    .type        = DMI_TYPE_MEMORY_DEVICE_ADDR,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x13,
    .attributes  = dmi_memory_device_addr_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_memory_device_addr_decode,
        .free   = (dmi_table_free_fn_t)dmi_memory_device_addr_free
    }
};

dmi_memory_device_addr_t *dmi_memory_device_addr_decode(const dmi_table_t *table)
{
    dmi_memory_device_addr_t *info;
    const dmi_memory_device_addr_data_t *data;

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_MEMORY_DEVICE_ADDR) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    if ((table->body_length >= 0x13) and (data->start_addr == 0xFFFFFFFFU)) {
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

    info->device_handle     = dmi_value(data->device_handle);
    info->array_addr_handle = dmi_value(data->array_addr_handle);

    info->partition_pos    = data->partition_pos != 0xFFU ?
                             data->partition_pos : USHRT_MAX;
    info->interleave_pos   = data->interleave_pos != 0xFFU ?
                             data->interleave_pos : USHRT_MAX;
    info->interleave_depth = data->interleave_depth != 0xFFU ?
                             data->interleave_depth : USHRT_MAX;

return info;
}

void dmi_memory_device_addr_free(dmi_memory_device_addr_t *info)
{
    free(info);
}
