//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <limits.h>

#include <opendmi/context.h>
#include <opendmi/value.h>
#include <opendmi/utils.h>
#include <opendmi/utils/name.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/system-reset.h>

static bool dmi_system_reset_decode(dmi_entity_t *entity);

static const dmi_name_set_t dmi_boot_option_names =
{
    .code  = "boot-options",
    .names = (dmi_name_t[]){
        DMI_NAME_RESERVED(DMI_BOOT_OPTION_RESERVED),
        {
            .id   = DMI_BOOT_OPTION_OPERATING_SYSTEM,
            .code = "operating-system",
            .name = "Operating system"
        },
        {
            .id   = DMI_BOOT_OPTION_SYSTEM_UTILS,
            .code = "system-utils",
            .name = "System utilities"
        },
        {
            .id   = DMI_BOOT_OPTION_AVOID_REBOOT,
            .code = "avoid-reboot",
            .name = "Do not reboot"
        },
        DMI_NAME_NULL
    }
};

const dmi_entity_spec_t dmi_system_reset_spec =
{
    .code            = "system-reset",
    .name            = "System reset",
    .type            = DMI_TYPE(SYSTEM_RESET),
    .minimum_version = DMI_VERSION(2, 2, 0),
    .minimum_length  = 0x0D,
    .decoded_length  = sizeof(dmi_system_reset_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_system_reset_t, status, BOOL, {
            .code    = "status",
            .name    = "Reset enabled"
        }),
        DMI_ATTRIBUTE(dmi_system_reset_t, boot_on_watchdog, ENUM, {
            .code    = "boot-on-watchdog",
            .name    = "Boot option on watchdog",
            .values  = &dmi_boot_option_names
        }),
        DMI_ATTRIBUTE(dmi_system_reset_t, boot_on_limit, ENUM, {
            .code    = "boot-on-limit",
            .name    = "Boot option on reset limit",
            .values  = &dmi_boot_option_names
        }),
        DMI_ATTRIBUTE(dmi_system_reset_t, watchdog_present, BOOL, {
            .code    = "watchdog-present",
            .name    = "Watchdog present"
        }),
        DMI_ATTRIBUTE(dmi_system_reset_t, reset_count, INTEGER, {
            .code    = "reset-count",
            .name    = "Reset count",
            .unknown = dmi_value_ptr((unsigned short)USHRT_MAX)
        }),
        DMI_ATTRIBUTE(dmi_system_reset_t, reset_limit, INTEGER, {
            .code    = "reset-limit",
            .name    = "Reset limit",
            .unknown = dmi_value_ptr((unsigned short)USHRT_MAX)
        }),
        DMI_ATTRIBUTE(dmi_system_reset_t, timer_interval, INTEGER, {
            .code    = "timer-interval",
            .name    = "Timer interval",
            .unit    = DMI_UNIT_MINUTE,
            .unknown = dmi_value_ptr((unsigned short)USHRT_MAX)
        }),
        DMI_ATTRIBUTE(dmi_system_reset_t, timeout, INTEGER, {
            .code    = "timeout",
            .name    = "Timeout",
            .unit    = DMI_UNIT_MINUTE,
            .unknown = dmi_value_ptr((unsigned short)USHRT_MAX),
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers = {
        .decode = dmi_system_reset_decode
    }
};

const char *dmi_boot_option_name(dmi_boot_option_t value)
{
    return dmi_name_lookup(&dmi_boot_option_names, value);
}

static bool dmi_system_reset_decode(dmi_entity_t *entity)
{
    dmi_system_reset_t *info;
    const dmi_system_reset_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_SYSTEM_RESET);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_SYSTEM_RESET);
    if (info == nullptr)
        return false;

    dmi_system_reset_caps_t caps = {
        .__value = dmi_decode(data->capabilities)
    };

    info->status           = caps.status;
    info->boot_on_watchdog = caps.boot_on_watchdog;
    info->boot_on_limit    = caps.boot_on_limit;
    info->watchdog_present = caps.watchdog_present;

    info->reset_count    = dmi_decode(data->reset_count);
    info->reset_limit    = dmi_decode(data->reset_limit);
    info->timer_interval = dmi_decode(data->timer_inverval);
    info->timeout        = dmi_decode(data->timeout);

    return true;
}
