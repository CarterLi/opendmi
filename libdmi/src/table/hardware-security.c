//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/hardware-security.h>
#include <opendmi/name.h>

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
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_hardware_security_table =
{
    .tag         = "hardware-security",
    .name        = "Hardware security",
    .type        = DMI_TYPE_HARDWARE_SECURITY,
    .min_version = DMI_VERSION(2, 2, 0),
    .min_length  = 0x05,
    .attributes  = dmi_hardware_security_attrs
};

const char *dmi_hardware_security_status_name(enum dmi_hardware_security_status value)
{
    return dmi_name_lookup(dmi_hardware_security_status_names, value);
}
