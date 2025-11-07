//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/cooling-device.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_cooling_device_type_names[] =
{
    {
        .id   = DMI_COOLING_DEVICE_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_FAN,
        .code = "fan",
        .name = "Fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_CENTRIFUGAL_BLOWER,
        .code = "centrifugal-blower",
        .name = "Centrifugal blower"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_CHIP_FAN,
        .code = "chip-fan",
        .name = "Chip fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_CABINET_FAN,
        .code = "cabinet-fan",
        .name = "Cabinet fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_POWER_SUPPLY_FAN,
        .code = "power-supply-fan",
        .name = "Power supply fan"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_HEAT_PIPE,
        .code = "heat-pipe",
        .name = "Heat pipe"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_INTEGRATED_REFRIGERATION,
        .code = "integrated-refrigeration",
        .name = "Integrated refrigeration"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_ACTIVE_COOLING,
        .code = "active-cooling",
        .name = "Active cooling"
    },
    {
        .id   = DMI_COOLING_DEVICE_TYPE_PASSIVE_COOLING,
        .code = "passive-cooling",
        .name = "Passive cooling"
    },
    DMI_NAME_NULL
};

const dmi_attribute_spec_t dmi_cooling_device_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_cooling_device_table =
{
    .tag        = "cooling-device",
    .name       = "Cooling device",
    .type       = DMI_TYPE_COOLING_DEVICE,
    .min_length = 0x0E,
    .attributes = dmi_cooling_device_attrs
};

const char *dmi_cooling_device_type_name(dmi_cooling_device_type_t value)
{
    return dmi_name_lookup(dmi_cooling_device_type_names, value);
}
