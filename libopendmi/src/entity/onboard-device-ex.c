//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/onboard-device-ex.h>

static bool dmi_onboard_device_ex_decode(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_onboard_device_ex_spec =
{
    .code            = "onboard-device-ex",
    .name            = "Onboard devices extended information",
    .type            = DMI_TYPE(ONBOARD_DEVICE_EX),
    .minimum_version = DMI_VERSION(2, 6, 0),
    .minimum_length  = 0x0B,
    .decoded_length  = sizeof(dmi_onboard_device_ex_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_onboard_device_ex_t, designator, STRING, {
            .code    = "designator",
            .name    = "Designator"
        }),
        DMI_ATTRIBUTE(dmi_onboard_device_ex_t, type, ENUM, {
            .code    = "type",
            .name    = "Type",
            .unspec  = dmi_value_ptr(DMI_ONBOARD_DEVICE_TYPE_UNSPEC),
            .unknown = dmi_value_ptr(DMI_ONBOARD_DEVICE_TYPE_UNKNOWN),
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
    },
    .handlers = {
        .decode = dmi_onboard_device_ex_decode
    }
};

static bool dmi_onboard_device_ex_decode(dmi_entity_t *entity)
{
    dmi_onboard_device_ex_t *info;
    const dmi_onboard_device_ex_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_ONBOARD_DEVICE_EX);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_ONBOARD_DEVICE_EX);
    if (info == nullptr)
        return false;

    info->designator = dmi_entity_string(entity, data->designator);

    dmi_onboard_device_instance_details_t details = {
        .__value = dmi_decode(data->details)
    };

    info->type       = details.type;
    info->is_enabled = details.is_enabled;
    info->instance   = dmi_decode(data->instance);

    dmi_pci_addr_decode(&info->address, &data->address);

    return true;
}
