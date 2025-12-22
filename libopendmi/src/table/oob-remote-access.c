//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>

#include <opendmi/table/oob-remote-access.h>

static const dmi_name_set_t dmi_oob_connection_names =
{
    .code  = "oob-connections",
    .names = {
        {
            .id   = 0,
            .code = "is-inbound-enabled",
            .name = "Inbound connections enabled"
        },
        {
            .id   = 1,
            .code = "is-outbound-enabled",
            .name = "Outbound connections enabled"
        },
        DMI_NAME_NULL
    }
};

static const dmi_attribute_t dmi_oob_remote_access_attrs[] =
{
    DMI_ATTRIBUTE(dmi_oob_remote_access_t, vendor, STRING, {
        .code = "vendor",
        .name = "Vendor"
    }),
    DMI_ATTRIBUTE(dmi_oob_remote_access_t, connections, SET, {
        .code   = "connections",
        .name   = "Connections",
        .values = &dmi_oob_connection_names
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_oob_remote_access_table =
{
    .code        = "oob-remote-access",
    .name        = "Out-of-band remote access",
    .type        = DMI_TYPE_OOB_REMOTE_ACCESS,
    .min_version = DMI_VERSION(2, 2, 0),
    .min_length  = 0x06,
    .attributes  = dmi_oob_remote_access_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_oob_remote_access_decode,
        .free   = (dmi_table_free_fn_t)dmi_oob_remote_access_free
    }
};

dmi_oob_remote_access_t *dmi_oob_remote_access_decode(
        const dmi_table_t *table,
        dmi_version_t     *plevel)
{
    dmi_oob_remote_access_t *info;
    const dmi_oob_remote_access_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_OOB_REMOTE_ACCESS));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    dmi_oob_connections_t connections = {
        ._value = dmi_value(data->connections)
    };

    info->vendor      = dmi_table_string(table, data->vendor);
    info->connections = connections;

    if (plevel)
        *plevel = dmi_version(2, 2, 0);

    return info;
}

void dmi_oob_remote_access_free(dmi_oob_remote_access_t *info)
{
    dmi_free(info);
}
