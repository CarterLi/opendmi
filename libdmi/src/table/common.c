//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/common.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_ecc_type_names[] =
{
    {
        .id   = DMI_ECC_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_ECC_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown" 
    },
    {
        .id   = DMI_ECC_TYPE_NONE,
        .code = "none",
        .name = "None" 
    },
    {
        .id   = DMI_ECC_TYPE_PARITY,
        .code = "parity",
        .name = "Parity" 
    },
    {
        .id   = DMI_ECC_TYPE_SINGLE_BIT,
        .code = "single-bit",
        .name = "Single-bit ECC" 
    },
    {
        .id   = DMI_ECC_TYPE_MULTI_BIT,
        .code = "multi-bit",
        .name = "Multi-bit ECC" 
    },
    {
        .id   = DMI_ECC_TYPE_CRC,
        .code = "crc",
        .name = "CRC"
    },
    DMI_NAME_NULL
};

const char *dmi_ecc_type_name(enum dmi_ecc_type value)
{
    return dmi_name_lookup(dmi_ecc_type_names, value);
}
