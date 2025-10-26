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

const char *dmi_probe_location_name(dmi_probe_location_t value)
{
    return dmi_name(dmi_probe_location_names, value, __DMI_PROBE_LOCATION_COUNT);
}

const char *dmi_probe_status_name(dmi_probe_status_t value)
{
    return dmi_name(dmi_probe_status_names, value, __DMI_PROBE_STATUS_COUNT);
}
