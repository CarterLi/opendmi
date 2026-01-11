//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/oob-remote-access.h>

static bool dmi_oob_remote_access_decode(dmi_entity_t *entity);

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

const dmi_entity_spec_t dmi_oob_remote_access_spec =
{
    .code            = "oob-remote-access",
    .name            = "Out-of-band remote access",
    .type            = DMI_TYPE_OOB_REMOTE_ACCESS,
    .minimum_version = DMI_VERSION(2, 2, 0),
    .minimum_length  = 0x06,
    .decoded_length  = sizeof(dmi_oob_remote_access_t),
    .attributes      = (dmi_attribute_t[]){
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
    },
    .handlers = {
        .decode = dmi_oob_remote_access_decode
    }
};

static bool dmi_oob_remote_access_decode(dmi_entity_t *entity)
{
    dmi_oob_remote_access_t *info;
    const dmi_oob_remote_access_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_OOB_REMOTE_ACCESS);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_OOB_REMOTE_ACCESS);
    if (info == nullptr)
        return false;

    info->vendor              = dmi_entity_string(entity, data->vendor);
    info->connections.__value = dmi_decode(data->connections);

    return true;
}
