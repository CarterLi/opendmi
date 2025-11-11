//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/system-reset.h>

const dmi_attribute_t dmi_system_reset_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_system_reset_table =
{
    .tag        = "system-reset",
    .name       = "System reset",
    .type       = DMI_TYPE_SYSTEM_RESET,
    .min_length = 0x0D,
    .attributes = dmi_system_reset_attrs
};
