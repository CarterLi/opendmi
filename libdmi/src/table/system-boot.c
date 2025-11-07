//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/system-boot.h>

const dmi_attribute_spec_t dmi_system_boot_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_boot_table =
{
    .tag           = "system-boot",
    .name          = "System boot information",
    .type          = DMI_TYPE_SYSTEM_BOOT,
    .required_from = DMI_VERSION(2, 3, 0),
    .required_till = DMI_VERSION_NONE,
    .min_length    = 0x14,
    .attributes    = dmi_system_boot_attrs
};
