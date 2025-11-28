//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/memory-error-64.h>

const dmi_table_spec_t dmi_memory_error_64_table =
{
    .tag         = "memory-error-64",
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

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_MEMORY_ERROR_64) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    info->type            = dmi_value(data->type);
    info->granularity     = dmi_value(data->granularity);
    info->operation       = dmi_value(data->operation);
    info->vendor_syndrome = dmi_value(data->vendor_syndrome);
    info->array_addr      = dmi_value(data->array_addr);
    info->device_addr     = dmi_value(data->device_addr);
    info->resolution      = dmi_value(data->resolution);

    return info;
}
