//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/hardware-security.h>

const dmi_attribute_spec_t dmi_hardware_security_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
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
