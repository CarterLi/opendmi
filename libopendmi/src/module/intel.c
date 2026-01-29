//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>

const dmi_module_t dmi_intel_module =
{
    .code     = "intel",
    .name     = "Intel DMI extension",
    .entities = nullptr
};
