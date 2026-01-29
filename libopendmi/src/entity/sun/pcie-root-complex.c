//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/sun.h>
#include <opendmi/entity/sun/pcie-root-complex.h>

const dmi_entity_spec_t dmi_sun_pcie_root_complex_spec =
{
    .type = DMI_TYPE(SUN_PCIE_ROOT_COMPLEX),
    .code = "sun-pcie-root-complex",
    .name = "Sun PCI-express root complex information"
};
