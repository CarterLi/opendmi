//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <memory.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/entity/system-boot.h>

static bool dmi_system_boot_decode(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_system_boot_spec =
{
    .code           = "system-boot",
    .name           = "System boot information",
    .type           = DMI_TYPE_SYSTEM_BOOT,
    .required_from  = DMI_VERSION(2, 3, 0),
    .required_till  = DMI_VERSION_NONE,
    .minimum_length = 0x0B,
    .decoded_length = sizeof(dmi_system_boot_t),
    .attributes     = (dmi_attribute_t[]){
        // TODO: add string code representation (ranges, you know).
        DMI_ATTRIBUTE(dmi_system_boot_t, status, INTEGER, {
            .code = "status",
            .name = "Boot status"
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers = {
        .decode = dmi_system_boot_decode
    }
};

static bool dmi_system_boot_decode(dmi_entity_t *entity)
{
    dmi_system_boot_t *info;
    const dmi_system_boot_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_SYSTEM_BOOT);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_SYSTEM_BOOT);
    if (info == nullptr)
        return false;

    info->status = data->status[0];
    memcpy(info->status_data, data->status, countof(info->status_data));

    return true;
}
