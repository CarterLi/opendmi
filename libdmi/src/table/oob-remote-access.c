//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/oob-remote-access.h>

const dmi_attribute_t dmi_oob_remote_access_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_oob_remote_access_table =
{
    .tag         = "oob-remote-access",
    .name        = "Out-of-band remote access",
    .type        = DMI_TYPE_OOB_REMOTE_ACCESS,
    .min_version = DMI_VERSION(2, 2, 0),
    .min_length  = 0x06,
    .attributes  = dmi_oob_remote_access_attrs
};
