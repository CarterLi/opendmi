//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/system.h>
#include <opendmi/utils.h>

const struct dmi_attribute_spec dmi_system_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_table_spec =
{
    .tag        = "system",
    .name       = "System information",
    .type       = DMI_TYPE_SYSTEM,
    .min_length = 0x8,
    .attributes = dmi_system_attrs
};

const struct dmi_attribute_spec dmi_system_reset_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_reset_table_spec =
{
    .tag        = "system-reset",
    .name       = "System reset",
    .type       = DMI_TYPE_SYSTEM_RESET,
    .min_length = 0x0D,
    .attributes = dmi_system_reset_attrs
};

const struct dmi_attribute_spec dmi_system_boot_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_boot_table_spec =
{
    .tag        = "system-boot",
    .name       = "System boot information",
    .type       = DMI_TYPE_SYSTEM_BOOT,
    .min_length = 0x14,
    .attributes = dmi_system_boot_attrs
};
