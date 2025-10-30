//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/group-assoc.h>

const dmi_attribute_spec_t dmi_group_assoc_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_group_assoc_table =
{
    .tag        = "group-associations",
    .name       = "Group associations",
    .type       = DMI_TYPE_GROUP_ASSOC,
    .min_length = 0x08,
    .attributes = dmi_group_assoc_attrs
};
