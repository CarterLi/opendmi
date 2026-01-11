//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/group-assoc.h>

static bool dmi_group_assoc_decode(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_group_assoc_spec =
{
    .code            = "group-associations",
    .name            = "Group associations",
    .type            = DMI_TYPE_GROUP_ASSOC,
    .minimum_version = DMI_VERSION(2, 0, 0),
    .minimum_length  = 0x08,
    .decoded_length  = sizeof(dmi_group_assoc_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_group_assoc_t, group_name, STRING, {
            .code = "group-name",
            .name = "Group name"
        }),
        DMI_ATTRIBUTE(dmi_group_assoc_t, item_type, INTEGER, {
            .code  = "item-type",
            .name  = "Item type",
            .flags = DMI_ATTRIBUTE_FLAG_HEX
        }),
        DMI_ATTRIBUTE(dmi_group_assoc_t, item_handle, HANDLE, {
            .code = "item-handle",
            .name = "Item handle"
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers = {
        .decode = dmi_group_assoc_decode,
    }
};

static bool dmi_group_assoc_decode(dmi_entity_t *entity)
{
    dmi_group_assoc_t *info;
    const dmi_group_assoc_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_GROUP_ASSOC);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_GROUP_ASSOC);
    if (info == nullptr)
        return false;

    info->group_name  = dmi_entity_string(entity, data->group_name);
    info->item_type   = dmi_decode(data->item_type);
    info->item_handle = dmi_decode(data->item_handle);

    return true;
}
