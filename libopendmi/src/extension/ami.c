//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/ami.h>
#include <opendmi/entity/ami/type-221.h>

const dmi_extension_t dmi_ami_ext =
{
    .code     = "ami",
    .name     = "AMI",
    .entities = (const dmi_entity_spec_t *[]){
        &dmi_ami_type_221_spec,
        nullptr
    }
};
