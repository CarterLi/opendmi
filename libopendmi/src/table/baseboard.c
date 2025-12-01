//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>

#include <opendmi/table/baseboard.h>

static const dmi_name_t dmi_baseboard_type_names[] =
{
    {
        .id   = DMI_BASEBOARD_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_SERVER_BLADE,
        .code = "server-blade",
        .name = "Server blade"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_CONNECTIVITY_SWITCH,
        .code = "connectivity-switch",
        .name = "Connectivity switch"
    },
    {
        .id   =  DMI_BASEBOARD_TYPE_SYSTEM_MANAGEMENT_MODULE,
        .code = "system-management-module",
        .name = "System management module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_PROCESSOR_MODULE,
        .code = "processor-module",
        .name = "Processor module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_IO_MODULE,
        .code = "io-module",
        .name = "IO module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_MEMORY_MODULE,
        .code = "memory-module",
        .name = "Memory module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_DAUGHTERBOARD,
        .code = "daughterboard",
        .name = "Daughterboard"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_MOTHERBOARD,
        .code = "motherboard",
        .name = "Motherboard"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_PROCESSOR_MEMORY_MODULE,
        .code = "processor-memory-module",
        .name = "Processor/memory module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_PROCESSOR_IO_MODULE,
        .code = "processor-io-module",
        .name = "Processor/IO module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_INTERCONNECT_BOARD,
        .code = "interconnect-board",
        .name = "Interconnect board"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_baseboard_attrs[] =
{
    DMI_ATTRIBUTE(dmi_baseboard_t, vendor, STRING, {
        .code   = "vendor",
        .name   = "Vendor"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, product, STRING, {
        .code   = "product",
        .name   = "Product"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, version, STRING, {
        .code   = "version",
        .name   = "Version"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, serial_number, STRING, {
        .code   = "serial-number",
        .name   = "Serial number"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, asset_tag, STRING, {
        .code   = "asset-tag",
        .name   = "Asset tag"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, is_hosting_board, BOOL, {
        .code   = "is-hosting-board",
        .name   = "Hosting board"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, require_daughter_board, BOOL, {
        .code   = "require-daugther-board",
        .name   = "Require daugther board"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, is_removable, BOOL, {
        .code = "is-removable",
        .name = "Removable"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, is_replaceable, BOOL, {
        .code = "is-replaceable",
        .name = "Replaceable"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, is_hot_swappable, BOOL, {
        .code = "is-hot-swappable",
        .name = "Hot-swappable"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, location, STRING, {
        .code = "location",
        .name = "Location"
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, type, ENUM, {
        .code   = "type",
        .name   = "Type",
        .values = dmi_baseboard_type_names
    }),
    DMI_ATTRIBUTE(dmi_baseboard_t, children_count, INTEGER, {
        .code   = "children-count",
        .name   = "Children count"
    }),
    DMI_ATTRIBUTE_ARRAY(dmi_baseboard_t, children, children_count, HANDLE, {
        .code   = "children",
        .name   = "Children"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_baseboard_table =
{
    .code       = "baseboard",
    .name       = "Baseboard or module information",
    .type       = DMI_TYPE_BASEBOARD,
    .min_length = 0x0F,
    .attributes = dmi_baseboard_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_baseboard_decode,
        .free   = (dmi_table_free_fn_t)dmi_baseboard_free
    }
};

const char *dmi_baseboard_type_name(enum dmi_baseboard_type value)
{
    return dmi_name_lookup(dmi_baseboard_type_names, value);
}

dmi_baseboard_t *dmi_baseboard_decode(const dmi_table_t *table)
{
    dmi_baseboard_t *info;
    const dmi_baseboard_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_BASEBOARD));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->vendor        = dmi_table_string(table, data->vendor);
    info->product       = dmi_table_string(table, data->product);
    info->version       = dmi_table_string(table, data->version);
    info->serial_number = dmi_table_string(table, data->serial_number);
    info->asset_tag     = dmi_table_string(table, data->asset_tag);

    dmi_baseboard_features_t features = {
        ._value = dmi_value(data->features)
    };

    info->is_hosting_board       = features.is_hosting_board;
    info->require_daughter_board = features.require_daughter_board;
    info->is_removable           = features.is_removable;
    info->is_replaceable         = features.is_replaceable;
    info->is_hot_swappable       = features.is_hot_swappable;

    info->location       = dmi_table_string(table, data->location);
    info->chassis_handle = dmi_value(data->chassis_handle);
    info->type           = dmi_value(data->type);
    info->children_count = dmi_value(data->children_count);

    info->children = dmi_alloc_array(table->context, sizeof(dmi_handle_t), info->children_count);
    if (!info->children) {
        dmi_free(info);
        return nullptr;
    }

    for (size_t i = 0; i < info->children_count; i++)
        info->children[i] = dmi_value(data->children_handles[i]);

    return info;
}

void dmi_baseboard_free(dmi_baseboard_t *info)
{
    dmi_free(info->children);
    dmi_free(info);
}
