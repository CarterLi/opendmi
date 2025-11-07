//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-module.h>

const dmi_attribute_spec_t dmi_memory_module_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_module_table =
{
    .tag        = "memory-module",
    .name       = "Memory module information",
    .type       = DMI_TYPE_MEMORY_MODULE,
    .min_length = 0x08,
    .attributes = dmi_memory_module_attrs
};
