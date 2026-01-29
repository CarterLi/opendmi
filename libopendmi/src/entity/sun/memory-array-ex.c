//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/sun.h>
#include <opendmi/entity/sun/memory-array-ex.h>

const dmi_entity_spec_t dmi_sun_memory_array_ex_spec =
{
    .type = DMI_TYPE(SUN_MEMORY_ARRAY_EX),
    .code = "sun-memory-array-ex",
    .name = "Sun memory array extended information"
};
