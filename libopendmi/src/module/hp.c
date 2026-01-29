//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/module/hp.h>

const dmi_module_t dmi_hp_module =
{
    .code     = "hp",
    .name     = "HP",
    .entities = (const dmi_entity_spec_t *[]){
        nullptr
    }
};
