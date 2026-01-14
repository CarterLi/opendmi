//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/dell.h>
#include <opendmi/entity/dell/serial-port.h>

const dmi_entity_spec_t dmi_dell_serial_port_spec =
{
    .type = DMI_TYPE_DELL_SERIAL_PORT,
    .code = "dell-serial-port",
    .name = "Dell: Serial port"
};
