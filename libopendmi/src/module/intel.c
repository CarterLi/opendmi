//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/intel.h>

/**
 * @brief Intel extension module.
 */
static dmi_module_t dmi_intel_module =
{
    .code     = "intel",
    .name     = "Intel extensions",
    .entities = nullptr
};

__attribute__((constructor))
static void dmi_intel_module_register(void)
{
    dmi_module_register(&dmi_intel_module);
}
