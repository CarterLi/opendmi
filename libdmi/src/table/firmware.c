//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/firmware.h>
#include <opendmi/utils.h>

const struct dmi_attribute_spec dmi_firmware_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_firmware_table_spec =
{
    .tag        = "firmware",
    .name       = "Platform firmware information",
    .type       = DMI_TYPE_FIRMWARE,
    .min_length = 0x12,
    .attributes = dmi_firmware_attrs
};

const struct dmi_attribute_spec dmi_firmware_language_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_firmware_language_table_spec =
{
    .tag        = "firmware-language",
    .name       = "Firmware language information",
    .type       = DMI_TYPE_FIRMWARE_LANGUAGE,
    .min_length = 0x05,
    .attributes = dmi_firmware_language_attrs
};

const struct dmi_attribute_spec dmi_firmware_inventory_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_firmware_inventory_table_spec =
{
    .tag        = "firmware-inventory",
    .name       = "Firmware inventory information",
    .type       = DMI_TYPE_FIRMWARE_INVENTORY,
    .min_length = 0x18,
    .attributes = dmi_firmware_inventory_attrs
};
