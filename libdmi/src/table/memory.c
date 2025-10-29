//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory.h>

const struct dmi_attribute_spec dmi_mem_controller_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const struct dmi_table_spec dmi_mem_controller_table_spec =
{
    .tag        = "memory-controller",
    .name       = "Memory controller information",
    .type       = DMI_TYPE_MEM_CONTROLLER,
    .min_length = 0x8,
    .attributes = dmi_mem_controller_attrs
};

const struct dmi_attribute_spec dmi_mem_module_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const struct dmi_table_spec dmi_mem_module_table_spec =
{
    .tag        = "memory-module",
    .name       = "Memory module information",
    .type       = DMI_TYPE_MEM_MODULE,
    .min_length = 0x8,
    .attributes = dmi_mem_module_attrs
};
