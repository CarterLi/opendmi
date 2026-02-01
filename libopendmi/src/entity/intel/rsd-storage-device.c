//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>
#include <opendmi/entity/intel/rsd-storage-device.h>

const dmi_entity_spec_t dmi_intel_rsd_storage_device_spec =
{
    .type = DMI_TYPE(INTEL_RSD_STORAGE_DEVICE),
    .code = "intel-rsd-storage-device",
    .name = "Intel RSD storage device information"
};
