//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/oem-strings.h>

const dmi_attribute_spec_t dmi_oem_strings_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_oem_strings_table =
{
    .tag        = "oem-strings",
    .name       = "OEM strings",
    .type       = DMI_TYPE_OEM_STRINGS,
    .min_length = 0x05,
    .attributes = dmi_oem_strings_attrs
};
