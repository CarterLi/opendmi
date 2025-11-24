//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_EXTENSION_INTEL_H
#define OPENDMI_EXTENSION_INTEL_H

#pragma once

#include <opendmi/extension.h>

/**
 * @brief Intel structure type identifiers.
 */
enum dmi_intel_type
{
    DMI_TYPE_INTEL_RSD_NIC                 = 190, ///< Intel: RSD NIC information
    DMI_TYPE_INTEL_RSD_PCIE                = 192, ///< Intel: RSD PCIe information
    DMI_TYPE_INTEL_RSD_PROCESSOR_CPUID     = 193, ///< Intel: RSD Processor CPUID information
    DMI_TYPE_INTEL_RSD_STORAGE_DEVICE      = 194, ///< Intel: RSD Storage device information
    DMI_TYPE_INTRL_RSD_TPM                 = 195, ///< Intel: RSD TPM information
    DMI_TYPE_INTEL_RSD_TXT                 = 196, ///< Intel: RSD Trusted Execution Technology (TXT) information
    DMI_TYPE_INTEL_RSD_MEMORY_DEVICE_EX    = 197, ///< Intel: RSD Memory device extended information
    DMI_TYPE_INTEL_RSD_FPGA                = 198, ///< Intel: RSD Field-Programmable Gate Array (FPGA) information
    DMI_TYPE_INTEL_RSD_CABLED_PCIE         = 199, ///< Intel: RSD Cabled PCIe port information
    DMI_TYPE_INTEL_RSD_PHYS_DEVICE_MAPPING = 200  ///< Intel: RSD SMBIOS physical device mapping
};

/**
 * @brief Intel DMI extension.
 */
extern const dmi_extension_t dmi_intel_ext;

#endif // !OPENDMI_EXTENSION_INTEL_H
