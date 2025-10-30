//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/firmware-inventory.h>

const dmi_attribute_spec_t dmi_firmware_inventory_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_firmware_inventory_table =
{
    .tag        = "firmware-inventory",
    .name       = "Firmware inventory information",
    .type       = DMI_TYPE_FIRMWARE_INVENTORY,
    .min_length = 0x18,
    .attributes = dmi_firmware_inventory_attrs
};
