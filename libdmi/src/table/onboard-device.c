//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/onboard-device.h>

const dmi_attribute_spec_t dmi_onboard_device_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_onboard_device_table =
{
    .tag        = "onboard-device",
    .name       = "Onboard devices information",
    .type       = DMI_TYPE_ONBOARD_DEVICE,
    .min_length = 0x06,
    .attributes = dmi_onboard_device_attrs
};


const dmi_attribute_spec_t dmi_onboard_device_ex_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_onboard_device_ex_table =
{
    .tag         = "onboard-device-ex",
    .name        = "Onboard devices extended information",
    .type        = DMI_TYPE_ONBOARD_DEVICE_EX,
    .min_version = DMI_VERSION(2, 6, 0),
    .min_length  = 0x0B,
    .attributes  = dmi_onboard_device_ex_attrs
};
