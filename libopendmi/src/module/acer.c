//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/acer.h>

/**
 * @brief Acer extension module.
 */
static dmi_module_t dmi_acer_module =
{
    .code     = "acer",
    .name     = "Acer extensions",
    .entities = nullptr
};

__attribute__((constructor))
static void dmi_acer_module_register(void)
{
    dmi_module_register(&dmi_acer_module);
}
