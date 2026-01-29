//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/hpe.h>

/**
 * @brief HPE module extension.
 */
static dmi_module_t dmi_hpe_module =
{
    .code     = "hpe",
    .name     = "HP/HPE extensions",
    .entities = (const dmi_entity_spec_t *[]){
        nullptr
    }
};

__attribute__((constructor))
static void dmi_hpe_module_register(void)
{
    dmi_module_register(&dmi_hpe_module);
}
