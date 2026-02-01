//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>
#include <opendmi/entity/intel/rsd-memory-device-ex.h>

const dmi_entity_spec_t dmi_intel_rsd_memory_device_ex_spec =
{
    .type = DMI_TYPE(INTEL_RSD_MEMORY_DEVICE_EX),
    .code = "intel-rsd-memory-device-ex",
    .name = "Intel RSD memory device extended information"
};
