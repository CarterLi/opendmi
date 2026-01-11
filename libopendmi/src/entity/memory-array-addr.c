//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/memory-array-addr.h>

static bool dmi_memory_array_addr_validate(const dmi_entity_t *entity);
static bool dmi_memory_array_addr_decode(dmi_entity_t *entity);
static bool dmi_memory_array_addr_link(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_memory_array_addr_spec =
{
    .code            = "memory-array-address",
    .name            = "Memory array mapped address",
    .type            = DMI_TYPE_MEMORY_ARRAY_ADDR,
    .minimum_version = DMI_VERSION(2, 1, 0),
    .minimum_length  = 0x0F,
    .decoded_length  = sizeof(dmi_memory_array_addr_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_memory_array_addr_t, start_addr, ADDRESS, {
            .code   = "start-addr",
            .name   = "Starting address",
            .flags  = DMI_ATTRIBUTE_FLAG_HEX
        }),
        DMI_ATTRIBUTE(dmi_memory_array_addr_t, end_addr, ADDRESS, {
            .code  = "end-addr",
            .name  = "Ending address",
            .flags = DMI_ATTRIBUTE_FLAG_HEX
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
    },
    .handlers = {
        .validate = dmi_memory_array_addr_validate,
        .decode   = dmi_memory_array_addr_decode,
        .link     = dmi_memory_array_addr_link
    }
};

static bool dmi_memory_array_addr_validate(const dmi_entity_t *entity)
{
    const dmi_memory_array_addr_data_t *data;
    
    data = dmi_entity_data(entity, DMI_TYPE_MEMORY_ARRAY_ADDR);
    if (data == nullptr)
        return false;

    if (data->start_addr == 0xFFFFFFFFU) {
        if (data->end_addr != 0xFFFFFFFFU)
            return false;

        if (entity->body_length <= 0x0Fu)
            return false;
        if (data->end_addr_ex <= data->start_addr_ex)
            return false;
    } else {
        if (data->end_addr == 0xFFFFFFFFU)
            return false;
        if (data->end_addr <= data->start_addr)
            return false;

        if (entity->body_length > 0x0Fu) {
            if (data->start_addr_ex != 0)
                return false;
            if (data->end_addr_ex != 0)
                return false;
        }
    }

    return true;
}

static bool dmi_memory_array_addr_decode(dmi_entity_t *entity)
{
    dmi_memory_array_addr_t *info;
    const dmi_memory_array_addr_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_MEMORY_ARRAY_ADDR);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_MEMORY_ARRAY_ADDR);
    if (info == nullptr)
        return false;

    entity->level = dmi_version(2, 1, 0);

    info->start_addr      = dmi_decode(data->start_addr) << 10;
    info->end_addr        = dmi_decode(data->end_addr) << 10;
    info->array_handle    = dmi_decode(data->array_handle);
    info->partition_width = dmi_decode(data->partition_width);

    if (entity->body_length > 0x0Fu) {
        entity->level = dmi_version(2, 7, 0);

        if (data->start_addr == 0xFFFFFFFFu) {
            info->start_addr = dmi_decode(data->start_addr_ex);
            info->end_addr   = dmi_decode(data->end_addr_ex);
        }
    }

    if (info->end_addr > info->start_addr)
        info->range_size = info->end_addr - info->start_addr;
    else
        info->range_size = info->start_addr - info->end_addr;

    return true;
}

static bool dmi_memory_array_addr_link(dmi_entity_t *entity)
{
    dmi_memory_array_addr_t *info;
    dmi_registry_t *registry;

    info = dmi_entity_info(entity, DMI_TYPE_MEMORY_ARRAY_ADDR);
    if (info == nullptr)
        return false;

    registry = entity->context->registry;

    info->array = dmi_registry_get(registry, info->array_handle, DMI_TYPE_MEMORY_ARRAY, false);

    return true;
}
