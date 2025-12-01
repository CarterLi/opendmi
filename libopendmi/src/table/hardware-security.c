//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>

#include <opendmi/table/hardware-security.h>

static const dmi_name_t dmi_hardware_security_status_names[] =
{
    {
        .id   = DMI_HARDWARE_SECURITY_STATUS_DISABLED,
        .code = "disabled",
        .name = "Disabled"
    },
    {
        .id   = DMI_HARDWARE_SECURITY_STATUS_ENABLED,
        .code = "enabled",
        .name = "Enabled"
    },
    {
        .id   = DMI_HARDWARE_SECURITY_STATUS_NOT_IMPLEMENTED,
        .code = "not-implemented",
        .name = "Not implemented"
    },
    {
        .id   = DMI_HARDWARE_SECURITY_STATUS_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_hardware_security_attrs[] =
{
    DMI_ATTRIBUTE(dmi_hardware_security_t, front_panel_reset, ENUM, {
        .code   = "front-panel-reset",
        .name   = "Front panel reset status",
        .values = dmi_hardware_security_status_names
    }),
    DMI_ATTRIBUTE(dmi_hardware_security_t, admin_password, ENUM, {
        .code   = "admin-password",
        .name   = "Administrator password status",
        .values = dmi_hardware_security_status_names
    }),
    DMI_ATTRIBUTE(dmi_hardware_security_t, keyboard_password, ENUM, {
        .code   = "keyboard-password",
        .name   = "Keyboard password status",
        .values = dmi_hardware_security_status_names
    }),
    DMI_ATTRIBUTE(dmi_hardware_security_t, poweron_password, ENUM, {
        .code   = "poweron-password",
        .name   = "Power-on password status",
        .values = dmi_hardware_security_status_names
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_hardware_security_table =
{
    .code        = "hardware-security",
    .name        = "Hardware security",
    .type        = DMI_TYPE_HARDWARE_SECURITY,
    .min_version = DMI_VERSION(2, 2, 0),
    .min_length  = 0x05,
    .attributes  = dmi_hardware_security_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_hardware_security_decode,
        .free   = (dmi_table_free_fn_t)dmi_hardware_security_free
    }
};

const char *dmi_hardware_security_status_name(dmi_hardware_security_status_t value)
{
    return dmi_name_lookup(dmi_hardware_security_status_names, value);
}

dmi_hardware_security_t *dmi_hardware_security_decode(dmi_table_t *table)
{
    dmi_hardware_security_t *info;
    const dmi_hardware_security_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_HARDWARE_SECURITY));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->front_panel_reset = data->settings.front_panel_reset;
    info->admin_password    = data->settings.admin_password;
    info->keyboard_password = data->settings.keyboard_password;
    info->poweron_password  = data->settings.poweron_password;

    return info;
}

void dmi_hardware_security_free(dmi_hardware_security_t *info)
{
    dmi_free(info);
}
