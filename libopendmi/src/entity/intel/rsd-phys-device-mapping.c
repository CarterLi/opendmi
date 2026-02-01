//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>
#include <opendmi/entity/intel/rsd-phys-device-mapping.h>

const dmi_entity_spec_t dmi_intel_rsd_phys_device_mapping_spec =
{
    .type = DMI_TYPE(INTEL_RSD_PHYS_DEVICE_MAPPING),
    .code = "intel-rsd-phys-device-mapping",
    .name = "Intel RSD physical device mapping information"
};
