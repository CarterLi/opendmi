//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-device-addr.h>

const dmi_attribute_spec_t dmi_memory_device_addr_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_memory_device_addr_table =
{
    .tag         = "memory-device-address",
    .name        = "Memory device mapped address",
    .type        = DMI_TYPE_MEMORY_DEVICE_ADDR,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x13,
    .attributes  = dmi_memory_device_addr_attrs
};
