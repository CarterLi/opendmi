//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/intel.h>

const dmi_extension_t dmi_intel_ext =
{
    .code     = "intel",
    .name     = "Intel DMI extension",
    .entities = nullptr
};
