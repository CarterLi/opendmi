//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/ipmi-device.h>

const dmi_attribute_spec_t dmi_ipmi_device_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_ipmi_device_table =
{
    .tag         = "ipmi-device",
    .name        = "IPMI device information",
    .type        = DMI_TYPE_IPMI_DEVICE,
    .min_length  = 0x12,
    .attributes  = dmi_ipmi_device_attrs
};
