//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>

#include <opendmi/vendor.h>
#include <opendmi/utils/name.h>

#include <opendmi/extension/acer.h>
#include <opendmi/extension/apple.h>
#include <opendmi/extension/dell.h>
#include <opendmi/extension/hp.h>
#include <opendmi/extension/hpe.h>
#include <opendmi/extension/ibm.h>
#include <opendmi/extension/intel.h>
#include <opendmi/extension/lenovo.h>

static const dmi_name_set_t dmi_vendor_names =
{
    .code = "vendors",
    .names = (const dmi_name_t[]){
        DMI_NAME_OTHER(DMI_VENDOR_OTHER),
        {
            .id   = DMI_VENDOR_ACER,
            .code = "acer",
            .name = "Acer"
        },
        {
            .id   = DMI_VENDOR_APPLE,
            .code = "apple",
            .name = "Apple"
        },
        {
            .id   = DMI_VENDOR_DELL,
            .code = "dell",
            .name = "Dell"
        },
        {
            .id   = DMI_VENDOR_HP,
            .code = "hp",
            .name = "HP"
        },
        {
            .id   = DMI_VENDOR_HPE,
            .code = "hpe",
            .name = "HPE"
        },
        {
            .id   = DMI_VENDOR_IBM,
            .code = "ibm",
            .name = "IBM"
        },
        {
            .id   = DMI_VENDOR_INTEL,
            .code = "intel",
            .name = "Intel"
        },
        {
            .id   = DMI_VENDOR_LENOVO,
            .code = "lenovo",
            .name = "Lenovo"
        },
        DMI_NAME_NULL
    }
};

static const dmi_vendor_spec_t dmi_vendor_specs[] =
{
    {
        .id    = DMI_VENDOR_ACER,
        .code  = "acer",
        .names = (const char *[]){
            "Acer",
            nullptr
        },
        .extension = &dmi_acer_ext
    },
    {
        .id    = DMI_VENDOR_DELL,
        .code  = "dell",
        .names = (const char *[]){
            "Dell Inc.",
            "Dell Computer Corporation",
            nullptr
        },
        .extension = &dmi_dell_ext
    },
    {
        .id    = DMI_VENDOR_HP,
        .code  = "hp",
        .names = (const char *[]){
            "HP",
            "Hewlett-Packard",
            nullptr
        },
        .extension = &dmi_hp_ext
    },
    {
        .id    = DMI_VENDOR_HPE,
        .code  = "hpe",
        .names = (const char *[]){
            "HPE",
            "Hewlett-Packard Enterprise",
            nullptr
        },
        .extension = &dmi_hpe_ext
    },
    {
        .id    = DMI_VENDOR_IBM,
        .code  = "ibm",
        .names = (const char *[]){
            "IBM",
            nullptr
        },
        .extension = &dmi_ibm_ext,
    },
    {
        .id    = DMI_VENDOR_INTEL,
        .code  = "intel",
        .names = (const char *[]){
            "Intel",
            nullptr
        },
        .extension = &dmi_intel_ext,
    },
    {
        .id    = DMI_VENDOR_LENOVO,
        .code  = "lenovo",
        .names = (const char *[]){
            "LENOVO",
            nullptr
        },
        .extension = &dmi_lenovo_ext,
    },
    DMI_VENDOR_NULL
};

const char *dmi_vendor_name(dmi_vendor_t vendor)
{
    return dmi_name_lookup(&dmi_vendor_names, vendor);
}

const dmi_vendor_spec_t *dmi_vendor_detect(const char *name)
{
    const dmi_vendor_spec_t *vendor;
    const char **vendor_name;

    if (name == nullptr)
        return nullptr;

    for (vendor = dmi_vendor_specs; vendor->id != DMI_VENDOR_INVALID; vendor++) {
        for (vendor_name = vendor->names; *vendor_name != nullptr; vendor_name++) {
            if (strcasecmp(name, *vendor_name) == 0)
                return vendor;
        }
    }

    return nullptr;
}
