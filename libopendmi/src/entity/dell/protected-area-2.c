//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/dell.h>
#include <opendmi/entity/dell/protected-area-2.h>

const dmi_entity_spec_t dmi_dell_protected_area_2_spec =
{
    .type = DMI_TYPE(DELL_PROTECTED_AREA_2),
    .code = "dell-protected-area-2",
    .name = "Dell: Protected area type 2"
};
