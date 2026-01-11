//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/memory-error-64.h>

static bool dmi_memory_error_64_decode(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_memory_error_64_spec =
{
    .code            = "memory-error-64",
    .name            = "64-bit memory error information",
    .type            = DMI_TYPE_MEMORY_ERROR_64,
    .minimum_version = DMI_VERSION(2, 3, 0),
    .minimum_length  = 0x1F,
    .decoded_length  = sizeof(dmi_memory_error_t),
    .attributes      = dmi_memory_error_attrs,
    .handlers        = {
        .decode = dmi_memory_error_64_decode,
    }
};

static bool dmi_memory_error_64_decode(dmi_entity_t *entity)
{
    dmi_memory_error_t *info;
    const dmi_memory_error_64_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_MEMORY_ERROR_64);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_MEMORY_ERROR_64);
    if (info == nullptr)
        return false;

    info->type            = dmi_decode(data->type);
    info->granularity     = dmi_decode(data->granularity);
    info->operation       = dmi_decode(data->operation);
    info->vendor_syndrome = dmi_decode(data->vendor_syndrome);
    info->array_addr      = dmi_decode(data->array_addr);
    info->device_addr     = dmi_decode(data->device_addr);
    info->resolution      = dmi_decode(data->resolution);

    return true;
}
