//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/mgmt-device-component.h>

const dmi_attribute_t dmi_mgmt_device_component_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_mgmt_device_component_table =
{
    .tag         = "mgmt-device-component",
    .name        = "Management device component",
    .type        = DMI_TYPE_MGMT_DEVICE_COMPONENT,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x0B,
    .attributes  = dmi_mgmt_device_component_attrs
};
