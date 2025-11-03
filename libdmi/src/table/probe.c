//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/probe.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_probe_location_names[] =
{
    {
        .id   = DMI_PROBE_LOCATION_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_PROBE_LOCATION_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_PROBE_LOCATION_PROCESSOR,
        .code = "processor",
        .name = "Processor"
    },
    {
        .id   = DMI_PROBE_LOCATION_DISK,
        .code = "disk",
        .name = "Disk"
    },
    {
        .id   = DMI_PROBE_LOCATION_PERIPHERAL_BAY,
        .code = "peripheral-bay",
        .name = "Peripheral bay"
    },
    {
        .id   = DMI_PROBE_LOCATION_SYSTEM_MGMT_MODULE,
        .code = "system-mgmt-module",
        .name = "System management module"
    },
    {
        .id   = DMI_PROBE_LOCATION_MOTHERBOARD,
        .code = "motherboard",
        .name = "Motherboard"
    },
    {
        .id   = DMI_PROBE_LOCATION_MEMORY_MODULE,
        .code = "memory-module",
        .name = "Memory module"
    },
    {
        .id   = DMI_PROBE_LOCATION_PROCESSOR_MODULE,
        .code = "processor-module",
        .name = "Processor module"
    },
    {
        .id   = DMI_PROBE_LOCATION_POWER_UNIT,
        .code = "power-unit",
        .name = "Power unit"
    },
    {
        .id   = DMI_PROBE_LOCATION_ADDIN_CARD,
        .code = "addin-card",
        .name = "Add-in card"
    },
    {
        .id   = DMI_PROBE_LOCATION_FRONT_PANEL_BOARD,
        .code = "front-panel-board",
        .name = "Front panel board"
    },
    {
        .id   = DMI_PROBE_LOCATION_BACK_PANEL_BOARD,
        .code = "back-panel-board",
        .name = "Back panel board"
    },
    {
        .id   = DMI_PROBE_LOCATION_POWER_SYSTEM_BOARD,
        .code = "power-system-board",
        .name = "Power system board"
    },
    {
        .id   = DMI_PROBE_LOCATION_DRIVE_BACK_PLANE,
        .code = "drive-back-plane",
        .name = "Drive back plane"
    },
    DMI_NAME_NULL
};

const dmi_attribute_spec_t dmi_voltage_probe_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_voltage_probe_table =
{
    .tag        = "voltage-probe",
    .name       = "Voltage probe",
    .type       = DMI_TYPE_VOLTAGE_PROBE,
    .min_length = 0x16,
    .attributes = dmi_voltage_probe_attrs
};

const dmi_attribute_spec_t dmi_temperature_probe_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_temperature_probe_table =
{
    .tag        = "temperature-probe",
    .name       = "Temperature probe",
    .type       = DMI_TYPE_TEMPERATURE_PROBE,
    .min_length = 0x16,
    .attributes = dmi_temperature_probe_attrs
};

const dmi_attribute_spec_t dmi_current_probe_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_current_probe_table =
{
    .tag        = "current-probe",
    .name       = "Electrical current probe",
    .type       = DMI_TYPE_CURRENT_PROBE,
    .min_length = 0x16,
    .attributes = dmi_current_probe_attrs
};

const char *dmi_probe_location_name(dmi_probe_location_t value)
{
    return dmi_name_lookup(dmi_probe_location_names, value);
}
