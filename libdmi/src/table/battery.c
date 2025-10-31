//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/battery.h>
#include <opendmi/name.h>

const dmi_name_t dmi_battery_chemistry_names[] =
{
    {
        .id   = DMI_BATTERY_CHEMISTRY_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_BATTERY_CHEMISTRY_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_BATTERY_CHEMISTRY_LEAD_ACID,
        .code = "lead-acid",
        .name = "Lead acid"
    },
    {
        .id   = DMI_BATTERY_CHEMISTRY_NI_CD,
        .code = "ni-cd",
        .name = "Nickel cadmium"
    },
    {
        .id   = DMI_BATTERY_CHEMISTRY_NI_MH,
        .code = "ni-mh",
        .name = "Nickel metal hyrdide"
    },
    {
        .id   = DMI_BATTERY_CHEMISTRY_LI_ION,
        .code = "li-ion",
        .name = "Lithium-ion"
    },
    {
        .id   = DMI_BATTERY_CHEMISTRY_ZN_AIR,
        .code = "zn-air",
        .name = "Zinc air"
    },
    {
        .id   = DMI_BATTERY_CHEMISTRY_LI_PO,
        .code = "li-po",
        .name = "Lithium polymer"
    },
    DMI_NAME_NULL
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
    return dmi_name_lookup(dmi_battery_chemistry_names, value);
}
