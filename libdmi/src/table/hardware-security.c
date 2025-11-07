//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/table/hardware-security.h>
#include <opendmi/name.h>

static bool dmi_hardware_security_decode(dmi_table_t *table);
static void dmi_hardware_security_free(dmi_table_t *table);

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

const dmi_attribute_spec_t dmi_hardware_security_attrs[] =
{
    {
        .code   = "front-panel-reset",
        .name   = "Front panel reset status",
        .offset = offsetof(dmi_hardware_security_t, front_panel_reset),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_hardware_security_status_names
    },
    {
        .code   = "admin-password",
        .name   = "Administrator password status",
        .offset = offsetof(dmi_hardware_security_t, admin_password),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_hardware_security_status_names
    },
    {
        .code   = "keyboard-password",
        .name   = "Keyboard password status",
        .offset = offsetof(dmi_hardware_security_t, keyboard_password),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_hardware_security_status_names
    },
    {
        .code   = "poweron-password",
        .name   = "Power-on password status",
        .offset = offsetof(dmi_hardware_security_t, poweron_password),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_hardware_security_status_names
    },
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_hardware_security_table =
{
    .tag         = "hardware-security",
    .name        = "Hardware security",
    .type        = DMI_TYPE_HARDWARE_SECURITY,
    .min_version = DMI_VERSION(2, 2, 0),
    .min_length  = 0x05,
    .decode      = dmi_hardware_security_decode,
    .free        = dmi_hardware_security_free,
    .attributes  = dmi_hardware_security_attrs
};

const char *dmi_hardware_security_status_name(dmi_hardware_security_status_t value)
{
    return dmi_name_lookup(dmi_hardware_security_status_names, value);
}

static bool dmi_hardware_security_decode(dmi_table_t *table)
{
    dmi_hardware_security_t *info = nullptr;
    dmi_hardware_security_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return false;

    info->front_panel_reset = data->settings.front_panel_reset;
    info->admin_password    = data->settings.admin_password;
    info->keyboard_password = data->settings.keyboard_password;
    info->poweron_password  = data->settings.poweron_password;

    table->info = info;

    return true;
}

static void dmi_hardware_security_free(dmi_table_t *table)
{
    free(table->info);
}
