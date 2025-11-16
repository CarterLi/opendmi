//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <limits.h>

#include <opendmi/name.h>
#include <opendmi/utils.h>
#include <opendmi/table/probe.h>

static short dmi_probe_decode_value(dmi_word_t value);

const dmi_name_t dmi_probe_location_names[] =
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

const char *dmi_probe_location_name(dmi_probe_location_t value)
{
    return dmi_name_lookup(dmi_probe_location_names, value);
}

dmi_probe_t * dmi_probe_decode(dmi_table_t *table)
{
    dmi_probe_t *info = nullptr;
    dmi_probe_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    info->description   = dmi_table_string(table, data->description);
    info->location      = data->location;
    info->status        = data->status;
    info->maximum_value = dmi_probe_decode_value(data->maximum_value);
    info->minimum_value = dmi_probe_decode_value(data->minimum_value);
    info->resolution    = dmi_probe_decode_value(data->resolution);
    info->tolerance     = dmi_probe_decode_value(data->tolerance);
    info->accuracy      = dmi_probe_decode_value(data->accuracy);
    info->oem_defined   = dmi_decode_dword(data->oem_defined);

    if (table->body_length > 0x14)
        info->nominal_value = dmi_probe_decode_value(data->nominal_value);
    else
        info->nominal_value = SHRT_MIN;

    return info;
}

static short dmi_probe_decode_value(dmi_word_t value)
{
    value = dmi_decode_word(value);

    if (value == DMI_PROBE_VALUE_UNKNOWN)
        return SHRT_MIN;

    return (int16_t)value;
}

void dmi_probe_free(dmi_probe_t *info)
{
    free(info);
}
