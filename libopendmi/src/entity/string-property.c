//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/string-property.h>

static bool dmi_string_property_decode(dmi_entity_t *entity);
static bool dmi_string_property_link(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_string_property_spec =
{
    .code            = "string-property",
    .name            = "String property",
    .type            = DMI_TYPE_STRING_PROPERTY,
    .minimum_version = DMI_VERSION(3, 5, 0),
    .minimum_length  = 0x09,
    .decoded_length  = sizeof(dmi_string_property_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_string_property_t, ident, INTEGER, {
            .code = "ident",
            .name = "Identifier"
        }),
        DMI_ATTRIBUTE(dmi_string_property_t, value, STRING, {
            .code = "value",
            .name = "Identifier"
        }),
        DMI_ATTRIBUTE(dmi_string_property_t, parent_handle, HANDLE, {
            .code = "parent-handle",
            .name = "Parent handle"
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers    = {
        .decode = dmi_string_property_decode,
        .link   = dmi_string_property_link
    }
};

static bool dmi_string_property_decode(dmi_entity_t *entity)
{
    dmi_string_property_t *info;
    const dmi_string_property_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_STRING_PROPERTY);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_STRING_PROPERTY);
    if (info == nullptr)
        return false;

    info->ident         = dmi_decode(data->ident);
    info->value         = dmi_entity_string(entity, data->value);
    info->parent_handle = dmi_decode(data->parent_handle);

    return true;
}

static bool dmi_string_property_link(dmi_entity_t *entity)
{
    dmi_string_property_t *info;

    info = dmi_entity_info(entity, DMI_TYPE_STRING_PROPERTY);
    if (info == nullptr)
        return false;

    dmi_registry_t *registry = entity->context->registry;

    if (info->parent_handle != DMI_HANDLE_INVALID) {
        info->parent = dmi_registry_get(registry, info->parent_handle, DMI_TYPE_INVALID, false);
    }

    return true;
}
