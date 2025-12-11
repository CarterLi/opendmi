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

const dmi_name_t dmi_memory_module_type_names[] =
{
    DMI_NAME_OTHER(0),
    DMI_NAME_UNKNOWN(1),
    {
        .id   = 2,
        .code = "standard",
        .name = "Standard"
    },
    {
        .id   = 3,
        .code = "fpm",
        .name = "Fast page mode"
    },
    {
        .id   = 4,
        .code = "edo",
        .name = "EDO"
    },
    {
        .id   = 5,
        .code = "parity",
        .name = "Parity"
    },
    {
        .id   = 6,
        .code = "ecc",
        .name = "ECC"
    },
    {
        .id   = 7,
        .code = "simm",
        .name = "SIMM"
    },
    {
        .id   = 8,
        .code = "dimm",
        .name = "DIMM"
    },
    {
        .id   = 9,
        .code = "burst-edo",
        .name = "Burst EDO"
    },
    {
        .id   = 10,
        .code = "sdram",
        .name = "SDRAM"
    },
    DMI_NAME_NULL
};

const dmi_name_t dmi_memory_module_error_names[] =
{
    {
        .id   = 0,
        .code = "uncorrectable",
        .name = "Uncorrectable"
    },
    {
        .id   = 1,
        .code = "correctable",
        .name = "Correctable"
    },
    {
        .id   = 2,
        .code = "event-log",
        .name = "Event log"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_memory_module_attrs[] =
{
    DMI_ATTRIBUTE(dmi_memory_module_t, socket, STRING, {
        .code   = "socket",
        .name   = "Socket designator"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, bank_connections, INTEGER, {
        .code   = "bank-connections",
        .name   = "Bank connections",
        .flags  = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, current_speed, INTEGER, {
        .code   = "current-speed",
        .name   = "Current speed",
        .unit   = "ns"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, current_type, SET, {
        .code   = "current-type",
        .name   = "Current type",
        .values = dmi_memory_module_type_names
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, installed_size, SIZE, {
        .code   = "installed-size",
        .name   = "Installed size"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, enabled_size, SIZE, {
        .code   = "enabled-size",
        .name   = "Enabled size"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, is_disabled, BOOL, {
        .code   = "disabled",
        .name   = "Disabled"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, bank_count, INTEGER, {
        .code   = "bank-count",
        .name   = "Bank count"
    }),
    DMI_ATTRIBUTE(dmi_memory_module_t, error_status, SET, {
        .code   = "error-status",
        .name   = "Error status",
        .values = dmi_memory_module_error_names
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

dmi_memory_module_t *dmi_memory_module_decode(const dmi_table_t *table, dmi_version_t *plevel)
{
    dmi_memory_module_t *info;
    const dmi_memory_module_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_MEMORY_MODULE));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

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

    if (plevel)
        *plevel = dmi_version(2, 0, 0);

    return info;
}

void dmi_memory_module_free(dmi_memory_module_t *info)
{
    dmi_free(info);
}
