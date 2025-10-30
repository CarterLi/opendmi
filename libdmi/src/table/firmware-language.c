//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/firmware-language.h>

const dmi_attribute_spec_t dmi_firmware_language_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_firmware_language_table =
{
    .tag        = "firmware-language",
    .name       = "Firmware language information",
    .type       = DMI_TYPE_FIRMWARE_LANGUAGE,
    .min_length = 0x05,
    .attributes = dmi_firmware_language_attrs
};
