//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <limits.h>

#include <opendmi/name.h>
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/table/system-reset.h>

static const dmi_name_t dmi_boot_option_names[] =
{
    {
        .id   = DMI_BOOT_OPTION_RESERVED,
        .code = "reserved",
        .name = "Reserved"
    },
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
};

static const dmi_attribute_t dmi_system_reset_attrs[] =
{
    DMI_ATTRIBUTE(dmi_system_reset_t, status, BOOL, {
        .code    = "status",
        .name    = "Reset enabled"
    }),
    DMI_ATTRIBUTE(dmi_system_reset_t, boot_on_watchdog, ENUM, {
        .code    = "boot-on-watchdog",
        .name    = "Boot option on watchdog",
        .values  = dmi_boot_option_names
    }),
    DMI_ATTRIBUTE(dmi_system_reset_t, boot_on_limit, ENUM, {
        .code    = "boot-on-limit",
        .name    = "Boot option on reset limit",
        .values  = dmi_boot_option_names
    }),
    DMI_ATTRIBUTE(dmi_system_reset_t, watchdog_present, BOOL, {
        .code    = "watchdog-present",
        .name    = "Watchdog present"
    }),
    DMI_ATTRIBUTE(dmi_system_reset_t, reset_count, INTEGER, {
        .code    = "reset-count",
        .name    = "Reset count",
        .unknown = &(unsigned short){ USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_system_reset_t, reset_limit, INTEGER, {
        .code    = "reset-limit",
        .name    = "Reset limit",
        .unknown = &(unsigned short){ USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_system_reset_t, timer_interval, INTEGER, {
        .code    = "timer-interval",
        .name    = "Timer interval",
        .unit    = "min",
        .unknown = &(unsigned short){ USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_system_reset_t, timeout, INTEGER, {
        .code    = "timeout",
        .name    = "Timeout",
        .unit    = "min",
        .unknown = &(unsigned short){ USHRT_MAX },
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_system_reset_table =
{
    .code       = "system-reset",
    .name       = "System reset",
    .type       = DMI_TYPE_SYSTEM_RESET,
    .min_length = 0x0D,
    .attributes = dmi_system_reset_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_system_reset_decode,
        .free   = (dmi_table_free_fn_t)dmi_system_reset_free
    }
};

const char *dmi_boot_option_name(dmi_boot_option_t value)
{
    return dmi_name_lookup(dmi_boot_option_names, value);
}

dmi_system_reset_t *dmi_system_reset_decode(const dmi_table_t *table)
{
    dmi_system_reset_t *info;
    const dmi_system_reset_data_t *data;

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_SYSTEM_RESET) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    dmi_system_reset_caps_t caps = {
        ._value = data->capabilities
    };

    info->status           = caps.status;
    info->boot_on_watchdog = caps.boot_on_watchdog;
    info->boot_on_limit    = caps.boot_on_limit;
    info->watchdog_present = caps.watchdog_present;

    info->reset_count    = dmi_value(data->reset_count);
    info->reset_limit    = dmi_value(data->reset_limit);
    info->timer_interval = dmi_value(data->timer_inverval);
    info->timeout        = dmi_value(data->timeout);

    return info;
}

void dmi_system_reset_free(dmi_system_reset_t *info)
{
    free(info);
}
