//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <limits.h>

#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>

#include <opendmi/table/cooling-device.h>

static const dmi_name_t dmi_cooling_device_type_names[] =
{
    DMI_NAME_UNSPEC(DMI_COOLING_DEVICE_TYPE_UNSPEC),
    DMI_NAME_OTHER(DMI_COOLING_DEVICE_TYPE_OTHER),
    DMI_NAME_UNKNOWN(DMI_COOLING_DEVICE_TYPE_UNKNOWN),
    {
        .id   = DMI_COOLING_DEVICE_TYPE_FAN,
        .code = "fan",
        .name = "Fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_CENTRIFUGAL_BLOWER,
        .code = "centrifugal-blower",
        .name = "Centrifugal blower"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_CHIP_FAN,
        .code = "chip-fan",
        .name = "Chip fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_CABINET_FAN,
        .code = "cabinet-fan",
        .name = "Cabinet fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_POWER_SUPPLY_FAN,
        .code = "power-supply-fan",
        .name = "Power supply fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_HEAT_PIPE,
        .code = "heat-pipe",
        .name = "Heat pipe"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_INTEGRATED_REFRIGERATION,
        .code = "integrated-refrigeration",
        .name = "Integrated refrigeration"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_ACTIVE_COOLING,
        .code = "active-cooling",
        .name = "Active cooling"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_PASSIVE_COOLING,
        .code = "passive-cooling",
        .name = "Passive cooling"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_cooling_device_attrs[] =
{
    DMI_ATTRIBUTE(dmi_cooling_device_t, probe_handle, HANDLE, {
        .code    = "probe-handle",
        .name    = "Temperature probe handle"
    }),
    DMI_ATTRIBUTE(dmi_cooling_device_t, type, ENUM, {
        .code    = "type",
        .name    = "Type",
        .unspec  = DMI_VALUE_PTR(DMI_COOLING_DEVICE_TYPE_UNSPEC),
        .unknown = DMI_VALUE_PTR(DMI_COOLING_DEVICE_TYPE_UNKNOWN),
        .values  = dmi_cooling_device_type_names
    }),
    DMI_ATTRIBUTE(dmi_cooling_device_t, status, ENUM, {
        .code    = "status",
        .name    = "Status",
        .unspec  = DMI_VALUE_PTR(DMI_STATUS_UNSPEC),
        .unknown = DMI_VALUE_PTR(DMI_STATUS_UNKNOWN),
        .values  = dmi_status_names
    }),
    DMI_ATTRIBUTE(dmi_cooling_device_t, group, INTEGER, {
        .code    = "group",
        .name    = "Group"
    }),
    DMI_ATTRIBUTE(dmi_cooling_device_t, oem_defined, INTEGER, {
        .code    = "oem-defined",
        .name    = "OEM-defined",
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_cooling_device_t, nominal_speed, INTEGER, {
        .code    = "nominal-speed",
        .name    = "Nominal speed",
        .unit    = "rpm",
        .unknown = DMI_VALUE_PTR((short)SHRT_MIN)
    }),
    DMI_ATTRIBUTE(dmi_cooling_device_t, description, STRING, {
        .code    = "description",
        .name    = "Description"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_cooling_device_table =
{
    .code       = "cooling-device",
    .name       = "Cooling device",
    .type       = DMI_TYPE_COOLING_DEVICE,
    .min_length = 0x0E,
    .attributes = dmi_cooling_device_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_cooling_device_decode,
        .link   = (dmi_table_link_fn_t)dmi_cooling_device_link,
        .free   = (dmi_table_free_fn_t)dmi_cooling_device_free
    }
};

const char *dmi_cooling_device_type_name(dmi_cooling_device_type_t value)
{
    return dmi_name_lookup(dmi_cooling_device_type_names, value);
}

dmi_cooling_device_t *dmi_cooling_device_decode(dmi_table_t *table)
{
    dmi_cooling_device_t *info;
    const dmi_cooling_device_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_COOLING_DEVICE));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->probe_handle = dmi_value(data->probe_handle);

    dmi_cooling_device_details_t details = {
        ._value = dmi_value(data->details)
    };

    info->type        = details.type;
    info->status      = details.status;
    info->group       = dmi_value(data->group);
    info->oem_defined = dmi_value(data->oem_defined);

    if (table->body_length > 0x0C) {
        uint16_t nominal_speed = dmi_value(data->nominal_speed);
        if (nominal_speed != 0x8000u)
            info->nominal_speed = (short)(nominal_speed & 0x7FFFu);
        else
            info->nominal_speed = SHRT_MIN;
    } else {
        info->nominal_speed = SHRT_MIN;
    }

    if (table->body_length >= 0x0F)
        info->description = dmi_table_string(table, data->description);

    return info;
}

bool dmi_cooling_device_link(dmi_table_t *table)
{
    dmi_cooling_device_t *info;
    dmi_registry_t *registry;

    info = dmi_cast(info, dmi_table_info(table, DMI_TYPE_COOLING_DEVICE));
    if (!info)
        return false;

    registry = table->context->registry;

    if (info->probe_handle != DMI_HANDLE_INVALID) {
        info->probe = dmi_registry_get(registry, info->probe_handle);
        if (!info->probe)
            return false;
    }

    return true;
}

void dmi_cooling_device_free(dmi_cooling_device_t *info)
{
    dmi_free(info);
}
