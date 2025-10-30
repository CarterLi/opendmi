//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/cooler.h>
#include <opendmi/utils.h>

const char *dmi_cooler_type_names[__DMI_COOLER_TYPE_COUNT] =
{
    [DMI_COOLER_TYPE_OTHER]                    = "Other",
    [DMI_COOLER_TYPE_UNKNOWN]                  = "Unknown",
    [DMI_COOLER_TYPE_FAN]                      = "Fan",
    [DMI_COOLER_TYPE_CENTRIFUGAL_BLOWER]       = "Centrifugal blower",
    [DMI_COOLER_TYPE_CHIP_FAN]                 = "Chip fan",
    [DMI_COOLER_TYPE_CABINET_FAN]              = "Cabinet fan",
    [DMI_COOLER_TYPE_POWER_SUPPLY_FAN]         = "Power supply fan",
    [DMI_COOLER_TYPE_HEAT_PIPE]                = "Heat pipe",
    [DMI_COOLER_TYPE_INTEGRATED_REFRIGERATION] = "Integrated refrigeration",
    [DMI_COOLER_TYPE_ACTIVE_COOLING]           = "Active cooling",
    [DMI_COOLER_TYPE_PASSIVE_COOLING]          = "Passive cooling"
};

const char *dmi_cooler_status_names[__DMI_COOLER_STATUS_COUNT] =
{
    [DMI_COOLER_STATUS_OTHER]           = "Other",
    [DMI_COOLER_STATUS_UNKNOWN]         = "Unknown",
    [DMI_COOLER_STATUS_OK]              = "OK",
    [DMI_COOLER_STATUS_NON_CRITICAL]    = "Non-critical",
    [DMI_COOLER_STATUS_CRITICAL]        = "Critical",
    [DMI_COOLER_STATUS_NON_RECOVERABLE] = "Non-recoverable"
};

const dmi_attribute_spec_t dmi_cooler_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_cooler_table =
{
    .tag        = "cooling-device",
    .name       = "Cooling device",
    .type       = DMI_TYPE_COOLING_DEVICE,
    .min_length = 0x0E,
    .attributes = dmi_cooler_attrs
};

const char *dmi_cooler_type_name(dmi_cooler_type_t value)
{
    return dmi_name(dmi_cooler_type_names, value, __DMI_COOLER_TYPE_COUNT);
}

const char *dmi_cooler_status_name(dmi_cooler_status_t value)
{
    return dmi_name(dmi_cooler_status_names, value, __DMI_COOLER_STATUS_COUNT);
}
