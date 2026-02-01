//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <assert.h>

#include <opendmi/module.h>

dmi_module_t *dmi_modules = nullptr;

void dmi_module_register(dmi_module_t *module)
{
    assert(module != nullptr);

    if (dmi_modules != nullptr)
        module->next = dmi_modules;

    dmi_modules = module;
}

const dmi_module_t *dmi_module_find(const char *code)
{
    const dmi_module_t *module;

    assert(code != nullptr);

    for (module = dmi_modules; module != nullptr; module = module->next) {
        if (strcmp(module->code, code) == 0)
            return module;
    }

    return nullptr;
}
