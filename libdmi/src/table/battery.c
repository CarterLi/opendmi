//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/battery.h>
#include <opendmi/utils.h>

const char *dmi_battery_chemistry_names[__DMI_BATTERY_CHEMISTRY_COUNT] =
{
    [DMI_BATTERY_CHEMISTRY_OTHER]     = "Other",
    [DMI_BATTERY_CHEMISTRY_UNKNOWN]   = "Unknown",
    [DMI_BATTERY_CHEMISTRY_LEAD_ACID] = "Lead acid",
    [DMI_BATTERY_CHEMISTRY_NI_CD]     = "Nickel cadmium",
    [DMI_BATTERY_CHEMISTRY_NI_MH]     = "Nickel metal hyrdide",
    [DMI_BATTERY_CHEMISTRY_LI_ION]    = "Lithium-ion",
    [DMI_BATTERY_CHEMISTRY_ZINC_AIR]  = "Zinc air",
    [DMI_BATTERY_CHEMISTRY_LI_PO]     = "Lithium polymer"
};

const dmi_attribute_spec_t dmi_battery_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_battery_table =
{
    .tag        = "portable-battery",
    .name       = "Portable battery",
    .type       = DMI_TYPE_PORTABLE_BATTERY,
    .min_length = 0x05,
    .attributes = dmi_battery_attrs
};

const char *dmi_battery_chemistry_name(dmi_battery_chemistry_t value)
{
    return dmi_name(dmi_battery_chemistry_names, value, __DMI_BATTERY_CHEMISTRY_COUNT);
}
