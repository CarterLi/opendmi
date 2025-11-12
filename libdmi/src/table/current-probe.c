//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/current-probe.h>

const dmi_attribute_t dmi_current_probe_attrs[] =
{
    DMI_ATTRIBUTE(dmi_current_probe_t, description, STRING, {
        .code    = "description",
        .name    = "Description"
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, location, ENUM, {
        .code    = "location",
        .name    = "Location",
        .values  = dmi_probe_location_names
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, status, ENUM, {  
        .code    = "status",
        .name    = "Status",
        .values  = dmi_status_names
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, max_value, DECIMAL, {
        .code    = "max-value",
        .name    = "Maximum value",
        .scale   = 1,
        .unit    = "mA",
        .unknown = &(short){ DMI_PROBE_VALUE_UNKNOWN },
        .flags   = DMI_ATTRIBUTE_FLAG_SIGNED
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, min_value, DECIMAL, {
        .code    = "min-value",
        .name    = "Minimum value",
        .scale   = 1,
        .unit    = "mA",
        .unknown = &(short){ DMI_PROBE_VALUE_UNKNOWN },
        .flags   = DMI_ATTRIBUTE_FLAG_SIGNED
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, resolution, DECIMAL, {
        .code    = "resolution",
        .name    = "Resolution",
        .scale   = 3,
        .unit    = "mA",
        .unknown = &(short){ DMI_PROBE_VALUE_UNKNOWN },
        .flags   = DMI_ATTRIBUTE_FLAG_SIGNED
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, tolerance, DECIMAL, {
        .code    = "tolerance",
        .name    = "Tolerance",
        .scale   = 1,
        .unit    = "mA",
        .unknown = &(short){ DMI_PROBE_VALUE_UNKNOWN },
        .flags   = DMI_ATTRIBUTE_FLAG_SIGNED
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, accuracy, DECIMAL, {
        .code    = "accuracy",
        .name    = "Accuracy",
        .scale   = 2,
        .unit    = "mA",
        .unknown = &(short){ DMI_PROBE_VALUE_UNKNOWN },
        .flags   = DMI_ATTRIBUTE_FLAG_SIGNED
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, oem_defined, INTEGER, {
        .code    = "oem-defined",
        .name    = "OEM-defined",
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_current_probe_t, nom_value, DECIMAL, {
        .code    = "nom-value",
        .name    = "Nominal value",
        .scale   = 1,
        .unit    = "mA",
        .unknown = &(short){ DMI_PROBE_VALUE_UNKNOWN },
        .flags   = DMI_ATTRIBUTE_FLAG_SIGNED
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_current_probe_table =
{
    .tag        = "current-probe",
    .name       = "Electrical current probe",
    .type       = DMI_TYPE_CURRENT_PROBE,
    .min_length = 0x16,
    .attributes = dmi_current_probe_attrs,
    .handlers   = {
        .decoder     = (dmi_table_decoder_t)dmi_probe_decode,
        .deallocator = (dmi_table_deallocator_t)dmi_probe_destroy
    }
};
