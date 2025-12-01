//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/memory-error-64.h>

const dmi_table_spec_t dmi_memory_error_64_table =
{
    .code        = "memory-error-64",
    .name        = "64-bit memory error information",
    .type        = DMI_TYPE_MEMORY_ERROR_64,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x1F,
    .attributes  = dmi_memory_error_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_memory_error_64_decode,
        .free   = (dmi_table_free_fn_t)dmi_memory_error_free
    }
};

dmi_memory_error_t *dmi_memory_error_64_decode(const dmi_table_t *table)
{
    dmi_memory_error_t *info;
    const dmi_memory_error_64_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_MEMORY_ERROR_64));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->type            = dmi_value(data->type);
    info->granularity     = dmi_value(data->granularity);
    info->operation       = dmi_value(data->operation);
    info->vendor_syndrome = dmi_value(data->vendor_syndrome);
    info->array_addr      = dmi_value(data->array_addr);
    info->device_addr     = dmi_value(data->device_addr);
    info->resolution      = dmi_value(data->resolution);

    return info;
}
