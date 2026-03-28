//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/entity/bis-entry-point.h>

const dmi_entity_spec_t dmi_bis_entry_point_spec =
{
    .code            = "bis-entry-point",
    .name            = "Boot Integrity Services (BIS) entry point",
    .description     = (const char *[]){
        "Structure type 31 is reserved for use by the Boot Integrity Services "
        "(BIS). See the Boot Integrity Services API Specification for details.",
        //
        nullptr
    },
    .type            = DMI_TYPE(BIS_ENTRY_POINT),
    .minimum_version = DMI_VERSION(2, 3, 0),
    .minimum_length  = 0x14,
    .attributes      = (const dmi_attribute_t[]){
        DMI_ATTRIBUTE_NULL
    }
};
