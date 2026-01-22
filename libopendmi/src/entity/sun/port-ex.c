//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/sun.h>
#include <opendmi/entity/sun/port-ex.h>

const dmi_entity_spec_t dmi_sun_port_ex_spec =
{
    .type = DMI_TYPE(SUN_PORT_EX),
    .code = "sun-port-ex",
    .name = "Sun port extended information"
};
