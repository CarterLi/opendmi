//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/entity/bis-entry-point.h>

const dmi_attribute_t dmi_bis_entry_point_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_entity_spec_t dmi_bis_entry_point_spec =
{
    .code        = "bis-entry-point",
    .name        = "Boot Integrity Services (BIS) entry point",
    .type        = DMI_TYPE_BIS_ENTRY_POINT,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x14,
    .attributes  = dmi_bis_entry_point_attrs
};
