//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>
#include <opendmi/entity/intel/rsd-txt.h>

const dmi_entity_spec_t dmi_intel_rsd_txt_spec =
{
    .type = DMI_TYPE(INTEL_RSD_TXT),
    .code = "intel-rsd-txt",
    .name = "Intel RSD Trusted Execution Technology (TXT) information"
};
