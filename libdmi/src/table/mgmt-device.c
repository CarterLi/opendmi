//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/mgmt-device.h>

const dmi_attribute_spec_t dmi_mgmt_device_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_mgmt_device_table =
{
    .tag         = "mgmt-device",
    .name        = "Management device",
    .type        = DMI_TYPE_MGMT_DEVICE,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x0B,
    .attributes  = dmi_mgmt_device_attrs
};

const dmi_attribute_spec_t dmi_mgmt_device_component_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
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

const dmi_attribute_spec_t dmi_mgmt_device_threshold_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
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
