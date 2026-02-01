//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>
#include <opendmi/entity/intel/rsd-processor-cpuid.h>

const dmi_entity_spec_t dmi_intel_rsd_processor_cpuid_spec =
{
    .type = DMI_TYPE(INTEL_RSD_NETWORK_CARD),
    .code = "intel-rsd-processor-cpuid",
    .name = "Intel RSD processor CPUID information"
};
