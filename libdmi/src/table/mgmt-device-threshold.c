//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/mgmt-device-threshold.h>

const dmi_attribute_t dmi_mgmt_device_threshold_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_mgmt_device_threshold_table =
{
    .tag         = "mgmt-device-threshold",
    .name        = "Management device threshold data",
    .type        = DMI_TYPE_MGMT_DEVICE_THRESHOLD,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x10,
    .attributes  = dmi_mgmt_device_threshold_attrs
};
