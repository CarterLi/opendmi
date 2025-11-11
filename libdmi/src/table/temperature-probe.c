//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdio.h>

#include <opendmi/table/temperature-probe.h>

const char *dmi_temperature_value_format(const void *value_ptr);
const char *dmi_temperature_resolution_format(const void *value_ptr);
const char *dmi_temperature_accuracy_format(const void *value_ptr);

const dmi_attribute_spec_t dmi_temperature_probe_attrs[] =
{
    DMI_ATTRIBUTE(dmi_temperature_probe_t, description, STRING, {
        .code   = "description",
        .name   = "Description"
    }),
    DMI_ATTRIBUTE(dmi_temperature_probe_t, location, ENUM, {
        .code   = "location",
        .name   = "Location",
        .values = dmi_probe_location_names
    }),
    DMI_ATTRIBUTE(dmi_temperature_probe_t, status, ENUM, {
        .code   = "status",
        .name   = "Status",
        .values = dmi_status_names
    }),
    DMI_ATTRIBUTE(dmi_temperature_probe_t, max_value, INT, {
        .code      = "max-value",
        .name      = "Maximum value",
        .unit      = "°C",
        .to_string = dmi_temperature_value_format
    }),
    DMI_ATTRIBUTE(dmi_temperature_probe_t, min_value, INT, {
        .code      = "min-value",
        .name      = "Minimum value",
        .unit      = "°C",
        .to_string = dmi_temperature_value_format
    }),
    DMI_ATTRIBUTE(dmi_temperature_probe_t, resolution, INT, {
        .code      = "resolution",
        .name      = "Resolution",
        .unit      = "°C",
        .to_string = dmi_temperature_resolution_format
    }),
    DMI_ATTRIBUTE(dmi_temperature_probe_t, tolerance, INT, {
        .code      = "tolerance",
        .name      = "Tolerance",
        .unit      = "°C",
        .to_string = dmi_temperature_value_format
    }),
    DMI_ATTRIBUTE(dmi_temperature_probe_t, accuracy, INT, {
        .code      = "accuracy",
        .name      = "Accuracy",
        .to_string = dmi_temperature_accuracy_format
    }),
    /*
    {
        .code = "oem-defined",
        .name = "OEM-defined"
    },
    */
    DMI_ATTRIBUTE(dmi_temperature_probe_t, nom_value, INT, {
        .code      = "nom-value",
        .name      = "Nominal value",
        .unit      = "°C",
        .to_string = dmi_temperature_value_format,
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_temperature_probe_table =
{
    .tag        = "temperature-probe",
    .name       = "Temperature probe",
    .type       = DMI_TYPE_TEMPERATURE_PROBE,
    .min_length = 0x16,
    .attributes = dmi_temperature_probe_attrs,
    .handlers   = {
        .decoder     = (dmi_table_decoder_t)dmi_probe_decode,
        .deallocator = (dmi_table_deallocator_t)dmi_probe_destroy
    }
};

const char *dmi_temperature_value_format(const void *value_ptr)
{
    static char str[16];

    int value = *(const int *)value_ptr;
    snprintf(str, sizeof(str), "%d.%01d", value / 10, value % 10);

    return str;
}

const char *dmi_temperature_resolution_format(const void *value_ptr)
{
    static char str[16];

    int value = *(const int *)value_ptr;
    snprintf(str, sizeof(str), "%d.%03d", value / 1000, value % 1000);

    return str;

}

const char *dmi_temperature_accuracy_format(const void *value_ptr)
{
    static char str[16];

    int value = *(const int *)value_ptr;
    snprintf(str, sizeof(str), "%d.%02d", value / 100, value % 100);

    return str;
}
