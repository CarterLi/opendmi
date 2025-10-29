//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/probe.h>
#include <opendmi/utils.h>

const char *dmi_probe_location_names[__DMI_PROBE_LOCATION_COUNT] =
{
    [DMI_PROBE_LOCATION_OTHER]              = "Other",
    [DMI_PROBE_LOCATION_UNKNOWN]            = "Unknown",
    [DMI_PROBE_LOCATION_PROCESSOR]          = "Processor",
    [DMI_PROBE_LOCATION_DISK]               = "Disk",
    [DMI_PROBE_LOCATION_PERIPHERAL_BAY]     = "Peripheral bay",
    [DMI_PROBE_LOCATION_SYSTEM_MGMT_MODULE] = "System management module",
    [DMI_PROBE_LOCATION_MOTHERBOARD]        = "Motherboard",
    [DMI_PROBE_LOCATION_MEMORY_MODULE]      = "Memory module",
    [DMI_PROBE_LOCATION_PROCESSOR_MODULE]   = "Processor module",
    [DMI_PROBE_LOCATION_POWER_UNIT]         = "Power unit",
    [DMI_PROBE_LOCATION_ADDIN_CARD]         = "Add-in card",
    [DMI_PROBE_LOCATION_FRONT_PANEL_BOARD]  = "Front panel board",
    [DMI_PROBE_LOCATION_BACK_PANEL_BOARD]   = "Back panel board",
    [DMI_PROBE_LOCATION_POWER_SYSTEM_BOARD] = "Power system board",
    [DMI_PROBE_LOCATION_DRIVE_BACK_PLANE]   = "Drive back plane"
};

const char *dmi_probe_status_names[__DMI_PROBE_STATUS_COUNT] =
{
    [DMI_PROBE_STATUS_OTHER]           = "Other",
    [DMI_PROBE_STATUS_UNKNOWN]         = "Unknown",
    [DMI_PROBE_STATUS_OK]              = "OK",
    [DMI_PROBE_STATUS_NON_CRITICAL]    = "Non-critical",
    [DMI_PROBE_STATUS_CRITICAL]        = "Critical",
    [DMI_PROBE_STATUS_NON_RECOVERABLE] = "Non-recoverable"
};

const struct dmi_attribute_spec dmi_voltage_probe_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_voltage_probe_table_spec =
{
    .tag        = "voltage-probe",
    .name       = "Voltage probe",
    .type       = DMI_TYPE_VOLTAGE_PROBE,
    .min_length = 0x16,
    .attributes = dmi_voltage_probe_attrs
};

const struct dmi_attribute_spec dmi_temperature_probe_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_temperature_probe_table_spec =
{
    .tag        = "temperature-probe",
    .name       = "Temperature probe",
    .type       = DMI_TYPE_TEMPERATURE_PROBE,
    .min_length = 0x16,
    .attributes = dmi_temperature_probe_attrs
};

const struct dmi_attribute_spec dmi_current_probe_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_current_probe_table_spec =
{
    .tag        = "current-probe",
    .name       = "Electrical current probe",
    .type       = DMI_TYPE_CURRENT_PROBE,
    .min_length = 0x16,
    .attributes = dmi_current_probe_attrs
};

const char *dmi_probe_location_name(dmi_probe_location_t value)
{
    return dmi_name(dmi_probe_location_names, value, __DMI_PROBE_LOCATION_COUNT);
}

const char *dmi_probe_status_name(dmi_probe_status_t value)
{
    return dmi_name(dmi_probe_status_names, value, __DMI_PROBE_STATUS_COUNT);
}
