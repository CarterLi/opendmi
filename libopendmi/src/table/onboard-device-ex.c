//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <limits.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/onboard-device-ex.h>

const dmi_attribute_t dmi_onboard_device_ex_attrs[] =
{
    DMI_ATTRIBUTE(dmi_onboard_device_ex_t, designator, STRING, {
        .code    = "designator",
        .name    = "Designator"
    }),
    DMI_ATTRIBUTE(dmi_onboard_device_ex_t, type, ENUM, {
        .code    = "type",
        .name    = "Type",
        .unspec  = DMI_VALUE_PTR(DMI_ONBOARD_DEVICE_TYPE_UNSPEC),
        .unknown = DMI_VALUE_PTR(DMI_ONBOARD_DEVICE_TYPE_UNKNOWN),
        .values  = &dmi_onboard_device_type_names
    }),
    DMI_ATTRIBUTE(dmi_onboard_device_ex_t, is_enabled, BOOL, {
        .code    = "is-enabled",
        .name    = "Enabled"
    }),
    DMI_ATTRIBUTE(dmi_onboard_device_ex_t, instance, INTEGER, {
        .code    = "instance",
        .name    = "Instance"
    }),
    DMI_ATTRIBUTE(dmi_onboard_device_ex_t, address, STRUCT, {
        .code    = "address",
        .name    = "Address",
        .attrs   = dmi_pci_addr_attrs
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_onboard_device_ex_table =
{
    .code        = "onboard-device-ex",
    .name        = "Onboard devices extended information",
    .type        = DMI_TYPE_ONBOARD_DEVICE_EX,
    .min_version = DMI_VERSION(2, 6, 0),
    .min_length  = 0x0B,
    .attributes  = dmi_onboard_device_ex_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_onboard_device_ex_decode,
        .free   = (dmi_table_free_fn_t)dmi_onboard_device_ex_free
    }
};

dmi_onboard_device_ex_t *dmi_onboard_device_ex_decode(const dmi_table_t *table, dmi_version_t *plevel)
{
    dmi_onboard_device_ex_t *info;
    const dmi_onboard_device_ex_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_ONBOARD_DEVICE_EX));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->designator = dmi_table_string(table, data->designator);

    dmi_onboard_device_instance_details_t details = {
        ._value = dmi_value(data->details)
    };

    info->type       = details.type;
    info->is_enabled = details.is_enabled;
    info->instance   = dmi_value(data->instance);

    dmi_pci_addr_decode(&info->address, &data->address);

    if (plevel)
        *plevel = dmi_version(2, 6, 0);

    return info;
}

void dmi_onboard_device_ex_free(dmi_onboard_device_ex_t *info)
{
    dmi_free(info);
}
