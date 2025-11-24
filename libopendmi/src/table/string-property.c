//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/string-property.h>

const dmi_attribute_t dmi_string_property_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_string_property_table =
{
    .tag         = "string-property",
    .name        = "String property",
    .type        = DMI_TYPE_STRING_PROPERTY,
    .min_version = DMI_VERSION(3, 5, 0),
    .min_length  = 0x09,
    .attributes  = dmi_string_property_attrs
};
