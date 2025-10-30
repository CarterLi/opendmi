//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/system-power.h>

const dmi_attribute_spec_t dmi_system_power_controls_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_power_controls_table =
{
    .tag         = "system-power-controls",
    .name        = "System power controls",
    .type        = DMI_TYPE_SYSTEM_POWER_CONTROLS,
    .min_version = DMI_VERSION(2, 2, 0),
    .min_length  = 0x09,
    .attributes  = dmi_system_power_controls_attrs
};

const dmi_attribute_spec_t dmi_system_power_supply_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_power_supply_table =
{
    .tag         = "system-power-supply",
    .name        = "System power supply",
    .type        = DMI_TYPE_SYSTEM_POWER_SUPPLY,
    .min_version = DMI_VERSION(2, 3, 1),
    .min_length  = 0x16,
    .attributes  = dmi_system_power_supply_attrs
};
