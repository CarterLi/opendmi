//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/string-property.h>

static const dmi_attribute_t dmi_string_property_attrs[] =
{
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
};

const dmi_table_spec_t dmi_string_property_table =
{
    .code        = "string-property",
    .name        = "String property",
    .type        = DMI_TYPE_STRING_PROPERTY,
    .min_version = DMI_VERSION(3, 5, 0),
    .min_length  = 0x09,
    .attributes  = dmi_string_property_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_string_property_decode,
        .link   = (dmi_table_link_fn_t)dmi_string_property_link,
        .free   = (dmi_table_free_fn_t)dmi_string_property_free,
    }
};

dmi_string_property_t *dmi_string_property_decode(const dmi_table_t *table, dmi_version_t *plevel)
{
    dmi_string_property_t *info;
    const dmi_string_property_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_STRING_PROPERTY));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->ident         = dmi_value(data->ident);
    info->value         = dmi_table_string(table, data->value);
    info->parent_handle = dmi_value(data->parent_handle);

    if (plevel)
        *plevel = dmi_version(3, 5, 0);

    return info;
}

bool dmi_string_property_link(dmi_table_t *table)
{
    dmi_string_property_t *info;
    dmi_registry_t *registry;

    info = dmi_cast(info, dmi_table_info(table, DMI_TYPE_STRING_PROPERTY));
    if (!info)
        return false;

    registry = table->context->registry;

    if (info->parent_handle != DMI_HANDLE_INVALID) {
        info->parent = dmi_registry_get(registry, info->parent_handle);
        if (!info->parent)
            return false;
    }

    return true;
}

void dmi_string_property_free(dmi_string_property_t *info)
{
    dmi_free(info);
}
