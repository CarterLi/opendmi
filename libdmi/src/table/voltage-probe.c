//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/voltage-probe.h>

const dmi_attribute_spec_t dmi_voltage_probe_attrs[] =
{
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, description, STRING),
        .code   = "description",
        .name   = "Description"
    },
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, location, ENUM),
        .code   = "location",
        .name   = "Location",
        .values = dmi_probe_location_names
    },
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, status, ENUM),
        .code   = "status",
        .name   = "Status",
        .values = dmi_status_names
    },
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, max_value, INT),
        .code   = "max-value",
        .name   = "Maximum value",
        .unit   = "mV"
    },
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, min_value, INT),
        .code   = "min-value",
        .name   = "Minimum value",
        .unit   = "mV"
    },
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, resolution, INT),
        .code   = "resolution",
        .name   = "Resolution"
    },
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, tolerance, INT),
        .code   = "tolerance",
        .name   = "Tolerance",
        .unit   = "mA"
    },
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, accuracy, INT),
        .code   = "accuracy",
        .name   = "Accuracy"
    },
    /*
    {
        .code = "oem-defined",
        .name = "OEM-defined"
    },
    */
    {
        DMI_ATTRIBUTE(dmi_voltage_probe_t, nom_value, INT),
        .code   = "nom-value",
        .name   = "Nominal value",
        .unit   = "mV"
    },
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_voltage_probe_table =
{
    .tag        = "voltage-probe",
    .name       = "Voltage probe",
    .type       = DMI_TYPE_VOLTAGE_PROBE,
    .min_length = 0x16,
    .attributes = dmi_voltage_probe_attrs,
    .handlers   = {
        .decoder     = (dmi_table_decoder_t)dmi_probe_decode,
        .deallocator = (dmi_table_deallocator_t)dmi_probe_destroy
    }
};
