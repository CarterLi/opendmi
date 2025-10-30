//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/bis-entry-point.h>

const dmi_attribute_spec_t dmi_bis_entry_point_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_bis_entry_point_table =
{
    .tag         = "bis-entry-point",
    .name        = "Boot Integrity Services (BIS) entry point",
    .type        = DMI_TYPE_BIS_ENTRY_POINT,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x14,
    .attributes  = dmi_bis_entry_point_attrs
};
