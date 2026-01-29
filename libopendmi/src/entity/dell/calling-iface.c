//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/dell.h>
#include <opendmi/entity/dell/calling-iface.h>

const dmi_entity_spec_t dmi_dell_calling_iface_spec =
{
    .type = DMI_TYPE(DELL_CALLING_IFACE),
    .code = "dell-calling-iface",
    .name = "Dell calling interface"
};
