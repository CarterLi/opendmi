//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/dell.h>
#include <opendmi/entity/dell/parallel-port.h>

const dmi_entity_spec_t dmi_dell_parallel_port_spec =
{
    .type = DMI_TYPE(DELL_PARALLEL_PORT),
    .code = "dell-parallel-port",
    .name = "Dell: Parallel port"
};
