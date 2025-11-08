//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/temperature-probe.h>

const dmi_attribute_spec_t dmi_temperature_probe_attrs[] =
{
    {
        .code   = "description",
        .name   = "Description",
        .offset = offsetof(dmi_temperature_probe_t, description),
        .type   = DMI_ATTRIBUTE_TYPE_STRING
    },
    {
        .code   = "location",
        .name   = "Location",
        .offset = offsetof(dmi_temperature_probe_t, location),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_probe_location_names
    },
    {
        .code   = "status",
        .name   = "Status",
        .offset = offsetof(dmi_temperature_probe_t, status),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_status_names
    },
    {
        .code   = "max-value",
        .name   = "Maximum value",
        .offset = offsetof(dmi_temperature_probe_t, max_value),
        .type   = DMI_ATTRIBUTE_TYPE_INT,
        .unit   = "C"
    },
    {
        .code   = "min-value",
        .name   = "Minimum value",
        .offset = offsetof(dmi_temperature_probe_t, min_value),
        .type   = DMI_ATTRIBUTE_TYPE_INT,
        .unit   = "C"
    },
    {
        .code   = "resolution",
        .name   = "Resolution",
        .offset = offsetof(dmi_temperature_probe_t, resolution),
        .type   = DMI_ATTRIBUTE_TYPE_INT
    },
    {
        .code   = "tolerance",
        .name   = "Tolerance",
        .offset = offsetof(dmi_temperature_probe_t, tolerance),
        .type   = DMI_ATTRIBUTE_TYPE_INT,
        .unit   = "C"
    },
    {
        .code   = "accuracy",
        .name   = "Accuracy",
        .offset = offsetof(dmi_temperature_probe_t, accuracy),
        .type   = DMI_ATTRIBUTE_TYPE_INT
    },
    /*
    {
        .code = "oem-defined",
        .name = "OEM-defined"
    },
    */
    {
        .code   = "nom-value",
        .name   = "Nominal value",
        .offset = offsetof(dmi_temperature_probe_t, nom_value),
        .type   = DMI_ATTRIBUTE_TYPE_INT,
        .unit   = "C"
    },
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_temperature_probe_table =
{
    .tag        = "temperature-probe",
    .name       = "Temperature probe",
    .type       = DMI_TYPE_TEMPERATURE_PROBE,
    .min_length = 0x16,
    .decode     = dmi_probe_decode,
    .free       = dmi_probe_free,
    .attributes = dmi_temperature_probe_attrs
};
