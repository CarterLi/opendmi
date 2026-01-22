//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/sun.h>
#include <opendmi/entity/sun/memory-device-ex.h>

const dmi_entity_spec_t dmi_sun_memory_device_ex_spec =
{
    .type = DMI_TYPE(SUN_MEMORY_DEVICE_EX),
    .code = "sun-memory-device-ex",
    .name = "Sun memory device extended information"
};
