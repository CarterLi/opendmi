//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/system-config.h>

const dmi_attribute_spec_t dmi_system_config_options_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_system_config_options_table =
{
    .tag        = "system-config-options",
    .name       = "System configuration options",
    .type       = DMI_TYPE_SYSTEM_CONFIG_OPTIONS,
    .min_length = 0x05,
    .attributes = dmi_system_config_options_attrs
};
