//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/sun.h>
#include <opendmi/entity/sun/processor-ex.h>

const dmi_entity_spec_t dmi_sun_processor_ex_spec =
{
    .type = DMI_TYPE(SUN_PROCESSOR_EX),
    .code = "sun-processor-ex",
    .name = "Sun processor extended information"
};
