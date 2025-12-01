//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/memory-module.h>

const dmi_attribute_t dmi_memory_module_attrs[] =
{
    DMI_ATTRIBUTE(dmi_memory_module_t, socket, STRING, {
        .code = "socket",
        .name = "Socket designator"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, current_speed, INTEGER, {
        .code = "current-speed",
        .name = "Current speed",
        .unit = "ns"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, installed_size, SIZE, {
        .code = "installed-size",
        .name = "Installed size"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, enabled_size, SIZE, {
        .code = "enabled-size",
        .name = "Enabled size"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_module_table =
{
    .code       = "memory-module",
    .name       = "Memory module information",
    .type       = DMI_TYPE_MEMORY_MODULE,
    .min_length = 0x08,
    .attributes = dmi_memory_module_attrs,
    .handlers = {
        .decode = (dmi_table_decode_fn_t)dmi_memory_module_decode,
        .free   = (dmi_table_free_fn_t)dmi_memory_module_free
    }
};

dmi_memory_module_t *dmi_memory_module_decode(const dmi_table_t *table)
{
    dmi_memory_module_t *info;
    const dmi_memory_module_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_MEMORY_MODULE));
    if (!data)
        return nullptr;

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    info->socket = dmi_table_string(table, data->socket);

    // Decode bank connections
    dmi_byte_t bank_connections = dmi_value(data->bank_connections);
    info->bank_connections[0] = (bank_connections & 0x0Fu);
    info->bank_connections[1] = (bank_connections & 0xF0u) >> 4;

    // Decode speed and type
    info->current_speed = dmi_value(data->current_speed);
    info->current_type  = (dmi_memory_module_type_t){
        ._value = dmi_value(data->current_type)
    };

    // Decode installed size
    dmi_byte_t installed_size = dmi_value(data->installed_size) & 0x7Fu;
    if (installed_size != 0x7Du)
        info->has_installed_size = true;
    if (installed_size != 0x7Fu)
        info->installed_size = (dmi_size_t)(installed_size & 0x7Fu) << 20;

    // Decode enabled size
    dmi_byte_t enabled_size = dmi_value(data->enabled_size) & 0x7Fu;
    if (enabled_size != 0x7Du)
        info->has_enabled_size = true;
    if (enabled_size != 0x7Fu) {
        if (enabled_size == 0x7Eu)
            info->is_disabled = true;
        else if (enabled_size != 0x7Du)
            info->enabled_size = (dmi_size_t)(enabled_size & 0x7Fu) << 20;
    }

    // Decode bank count
    info->bank_count = dmi_value(data->enabled_size) & 0x80u ? 2 : 1;

    // Decode error status
    info->error_status = (dmi_memory_module_error_t){
        ._value = dmi_value(data->error_status)
    };

    return info;
}

void dmi_memory_module_free(dmi_memory_module_t *info)
{
    free(info);
}
