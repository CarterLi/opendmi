//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/entity/processor-ex.h>

const dmi_entity_spec_t dmi_processor_ex_spec =
{
    .code            = "processor-ex",
    .name            = "Processor additional information",
    .type            = DMI_TYPE(PROCESSOR_EX),
    .minimum_version = DMI_VERSION(2, 0, 0),
    .minimum_length  = 0x06,
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE_NULL
    }
};
