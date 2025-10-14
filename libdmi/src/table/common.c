//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/common.h>
#include <opendmi/utils.h>

static const char *dmi_ecc_type_names[__DMI_ECC_TYPE_COUNT] =
{
    [DMI_ECC_TYPE_OTHER]      = "Other",
    [DMI_ECC_TYPE_UNKNOWN]    = "Unknown",
    [DMI_ECC_TYPE_NONE]       = "None",
    [DMI_ECC_TYPE_PARITY]     = "Parity",
    [DMI_ECC_TYPE_SINGLE_BIT] = "Single-bit ECC",
    [DMI_ECC_TYPE_MULTI_BIT]  = "Multi-bit ECC",
    [DMI_ECC_TYPE_CRC]        = "CRC"
};

const char *dmi_ecc_type_name(enum dmi_ecc_type value)
{
    return dmi_name(dmi_ecc_type_names, value, __DMI_ECC_TYPE_COUNT);
}
