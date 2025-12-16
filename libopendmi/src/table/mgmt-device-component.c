//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/mgmt-device-component.h>

const dmi_attribute_t dmi_mgmt_device_component_attrs[] =
{
    DMI_ATTRIBUTE(dmi_mgmt_device_component_t, description, STRING, {
        .code = "description",
        .name = "Description"
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_component_t, device_handle, HANDLE, {
        .code = "device-handle",
        .name = "Device handle"
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_component_t, component_handle, HANDLE, {
        .code = "component-handle",
        .name = "Component handle"
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_component_t, threshold_handle, HANDLE, {
        .code = "threshold-handle",
        .name = "Threshold handle"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_mgmt_device_component_table =
{
    .code        = "mgmt-device-component",
    .name        = "Management device component",
    .type        = DMI_TYPE_MGMT_DEVICE_COMPONENT,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x0B,
    .attributes  = dmi_mgmt_device_component_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_mgmt_device_component_decode,
        .free   = (dmi_table_free_fn_t)dmi_mgmt_device_component_free
    }
};

dmi_mgmt_device_component_t *dmi_mgmt_device_component_decode(const dmi_table_t *table, dmi_version_t *plevel)
{
    dmi_mgmt_device_component_t *info;
    const dmi_mgmt_device_component_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_MGMT_DEVICE_COMPONENT));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->description      = dmi_table_string(table, data->description);
    info->device_handle    = dmi_value(data->device_handle);
    info->component_handle = dmi_value(data->component_handle);
    info->threshold_handle = dmi_value(data->threshold_handle);

    if (plevel)
        *plevel = dmi_version(2, 3, 0);

    return info;
}

bool dmi_mgmt_device_component_link(dmi_table_t *table)
{
    static dmi_type_t dmi_component_types[] = {
        DMI_TYPE_COOLING_DEVICE,
        DMI_TYPE_TEMPERATURE_PROBE,
        DMI_TYPE_VOLTAGE_PROBE,
        DMI_TYPE_CURRENT_PROBE,
        DMI_TYPE_INVALID
    };

    dmi_mgmt_device_component_t *info;
    dmi_registry_t *registry;

    info = dmi_cast(info, dmi_table_info(table, DMI_TYPE_MGMT_DEVICE_COMPONENT));
    if (!info)
        return false;

    registry = table->context->registry;

    info->device = dmi_registry_get(registry, info->device_handle, DMI_TYPE_MGMT_DEVICE);
    if (!info->device)
        return false;

    info->component = dmi_registry_get_any(registry, info->component_handle, dmi_component_types);
    if (!info->component)
        return false;

    if (info->threshold_handle != DMI_HANDLE_INVALID) {
        info->threshold = dmi_registry_get(registry, info->threshold_handle, DMI_TYPE_MGMT_DEVICE_THRESHOLD);
    }

    return true;
}

void dmi_mgmt_device_component_free(dmi_mgmt_device_component_t *info)
{
    dmi_free(info);
}
