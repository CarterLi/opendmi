//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/mgmt-controller.h>

const dmi_attribute_spec_t dmi_mgmt_controller_host_if_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_mgmt_controller_host_if_table =
{
    .tag         = "mgmt-controller-host-if",
    .name        = "Management controller host interface",
    .type        = DMI_TYPE_MGMT_CONTROLLER_HOST_IF,
    .min_length  = 0x06,
    .attributes  = dmi_mgmt_controller_host_if_attrs
};
