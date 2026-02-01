//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>
#include <opendmi/entity/intel/rsd-fpga.h>

const dmi_entity_spec_t dmi_intel_rsd_fpga_spec =
{
    .type = DMI_TYPE(INTEL_RSD_FPGA),
    .code = "intel-rsd-fpga",
    .name = "Intel RSD FPGA information"
};
