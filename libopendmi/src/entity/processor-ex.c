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
    .description     = (const char *[]){
        "The information in this structure defines the processor additional "
        "information in case SMBIOS type 4 is not sufficient to describe "
        "processor characteristics.",
        //
        "The SMBIOS type 44 structure has a reference handle field to link "
        "back to the related SMBIOS type 4 structure. There may be multiple "
        "SMBIOS type 44 structures linked to the same SMBIOS type 4 "
        "structure. For example, when cores are not identical in a processor, "
        "SMBIOS type 44 structures describe different core-specific "
        "information.",
        //
        "SMBIOS type 44 defines the standard header for the "
        "processor-specific block (see 7.45.1), while the contents of "
        "processor-specific data are maintained by processor architecture "
        "workgroups or vendors in separate documents.",
        //
        nullptr
    },
    .type            = DMI_TYPE(PROCESSOR_EX),
    .minimum_version = DMI_VERSION(2, 0, 0),
    .minimum_length  = 0x06,
    .attributes      = (const dmi_attribute_t[]){
        DMI_ATTRIBUTE_NULL
    }
};
