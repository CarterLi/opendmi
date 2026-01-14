//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/entity/additional-info.h>

const dmi_entity_spec_t dmi_additional_info_spec =
{
    .code            = "additional-info",
    .name            = "Additional information",
    .type            = DMI_TYPE(ADDITIONAL_INFO),
    .minimum_version = DMI_VERSION(2, 6, 0),
    .minimum_length  = 0x05,
    .attributes      = (dmi_attribute_t[]) {
        DMI_ATTRIBUTE_NULL
    }
};
