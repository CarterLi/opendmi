//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

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

dmi_mgmt_device_component_t *dmi_mgmt_device_component_decode(const dmi_table_t *table)
{
    dmi_mgmt_device_component_t *info;
    dmi_mgmt_device_component_data_t *data;

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_MGMT_DEVICE_COMPONENT) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    info->description      = dmi_table_string(table, data->description);
    info->device_handle    = dmi_value(data->device_handle);
    info->component_handle = dmi_value(data->component_handle);
    info->threshold_handle = dmi_value(data->threshold_handle);

    return info;
}

bool dmi_mgmt_device_component_link(dmi_table_t *table)
{
    dmi_mgmt_device_component_t *info;
    dmi_registry_t *registry;

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if (table->type != DMI_TYPE_MGMT_DEVICE_COMPONENT) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return false;
    }

    info     = dmi_cast(info, table->info);
    registry = table->context->registry;

    info->device = dmi_registry_get(registry, info->device_handle);
    if (!info->device)
        return false;

    info->component = dmi_registry_get(registry, info->component_handle);
    if (!info->component)
        return false;

    if (info->threshold_handle != DMI_HANDLE_INVALID) {
        info->threshold = dmi_registry_get(registry, info->threshold_handle);
        if (!info->threshold)
            return false;
    }

    return true;
}

void dmi_mgmt_device_component_free(dmi_mgmt_device_component_t *info)
{
    free(info);
}
