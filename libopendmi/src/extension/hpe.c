//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/hpe.h>

const dmi_extension_t dmi_hpe_ext =
{
    .code     = "hpe",
    .name     = "HPE",
    .entities = (const dmi_entity_spec_t *[]){
        nullptr
    }
};
