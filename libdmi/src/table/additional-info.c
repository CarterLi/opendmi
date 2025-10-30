//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/additional-info.h>

const dmi_attribute_spec_t dmi_additional_info_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_additional_info_table =
{
    .tag         = "additional-info",
    .name        = "Additional information",
    .type        = DMI_TYPE_ADDITIONAL_INFO,
    .min_version = DMI_VERSION(2, 6, 0),
    .min_length  = 0x05,
    .attributes  = dmi_additional_info_attrs
};
