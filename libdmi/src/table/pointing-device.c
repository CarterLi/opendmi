//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/pointing-device.h>

const dmi_attribute_spec_t dmi_pointing_device_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_pointing_device_table =
{
    .tag        = "pointing-device",
    .name       = "Built-in pointing device",
    .type       = DMI_TYPE_POINTING_DEVICE,
    .min_length = 0x07,
    .attributes = dmi_pointing_device_attrs
};
