//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/firmware.h>
#include <opendmi/utils.h>

const dmi_attribute_spec_t dmi_firmware_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_firmware_table =
{
    .tag           = "firmware",
    .name          = "Platform firmware information",
    .type          = DMI_TYPE_FIRMWARE,
    .required_from = DMI_VERSION(2, 3, 0),
    .required_till = DMI_VERSION_NONE,
    .unique        = true,
    .min_length    = 0x12,
    .attributes    = dmi_firmware_attrs
};
