//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-controller.h>

const dmi_attribute_spec_t dmi_memory_controller_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_controller_table =
{
    .tag        = "memory-controller",
    .name       = "Memory controller information",
    .type       = DMI_TYPE_MEMORY_CONTROLLER,
    .min_length = 0x08,
    .attributes = dmi_memory_controller_attrs
};
