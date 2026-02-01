//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>
#include <opendmi/entity/intel/rsd-cabled-pcie-port.h>

const dmi_entity_spec_t dmi_intel_rsd_cabled_pcie_port_spec =
{
    .type = DMI_TYPE(INTEL_RSD_CABLED_PCIE),
    .code = "intel-rsd-cabled-pcie-port",
    .name = "Intel RST cabled PCIe port information"
};
