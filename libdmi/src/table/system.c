//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/system.h>
#include <opendmi/utils.h>

const dmi_attribute_spec_t dmi_system_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_table =
{
    .tag           = "system",
    .name          = "System information",
    .type          = DMI_TYPE_SYSTEM,
    .required_from = DMI_VERSION(2, 3, 0),
    .required_till = DMI_VERSION_NONE,
    .unique        = true,
    .min_length    = 0x8,
    .attributes    = dmi_system_attrs
};
