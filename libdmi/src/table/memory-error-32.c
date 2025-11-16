//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/utils.h>
#include <opendmi/table/memory-error-32.h>

const dmi_table_spec_t dmi_memory_error_32_table =
{
    .tag         = "memory-error-32",
    .name        = "32-bit memory error information",
    .type        = DMI_TYPE_MEMORY_ERROR_32,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x17,
    .attributes  = dmi_memory_error_attrs,
    .handlers    = {
        .decoder     = (dmi_table_decoder_t)dmi_memory_error_32_decode,
        .deallocator = (dmi_table_deallocator_t)dmi_memory_error_destroy
    }
};

dmi_memory_error_t *dmi_memory_error_32_decode(const dmi_table_t *table)
{
    dmi_memory_error_t *info = nullptr;
    dmi_memory_error_32_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    info->type            = data->type;
    info->granularity     = data->granularity;
    info->operation       = data->operation;
    info->vendor_syndrome = dmi_decode_dword(data->vendor_syndrome);
    info->array_addr      = dmi_decode_dword(data->array_addr);
    info->device_addr     = dmi_decode_dword(data->device_addr);
    info->resolution      = dmi_decode_dword(data->resolution);

    return info;
}
