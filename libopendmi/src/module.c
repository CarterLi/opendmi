//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module.h>

dmi_module_t *dmi_modules = nullptr;

void dmi_module_register(dmi_module_t *module)
{
    if (dmi_modules != nullptr)
        module->next = dmi_modules;

    dmi_modules = module;
}
