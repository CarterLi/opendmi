//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/table/group-assoc.h>

const dmi_attribute_t dmi_group_assoc_attrs[] =
{
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
};

const dmi_table_spec_t dmi_group_assoc_table =
{
    .tag        = "group-associations",
    .name       = "Group associations",
    .type       = DMI_TYPE_GROUP_ASSOC,
    .min_length = 0x08,
    .attributes = dmi_group_assoc_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_group_assoc_decode,
        .free   = (dmi_table_free_fn_t)dmi_group_assoc_free
    }
};

dmi_group_assoc_t *dmi_group_assoc_decode(const dmi_table_t *table)
{
    dmi_group_assoc_t *info;
    const dmi_group_assoc_data_t *data;

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_GROUP_ASSOC) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    info->group_name  = dmi_table_string(table, data->group_name);
    info->item_type   = dmi_value(data->item_type);
    info->item_handle = dmi_value(data->item_handle);

    return info;
}

void dmi_group_assoc_free(dmi_group_assoc_t *info)
{
    free(info);
}
