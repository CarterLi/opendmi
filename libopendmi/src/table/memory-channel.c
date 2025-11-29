//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-channel.h>

const dmi_attribute_t dmi_memory_channel_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_channel_table =
{
    .code        = "memory-channel",
    .name        = "Memory channel",
    .type        = DMI_TYPE_MEMORY_CHANNEL,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x0A,
    .attributes  = dmi_memory_channel_attrs
};
