//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/baseboard.h>
#include <opendmi/utils.h>

static const char *dmi_baseboard_type_names[__DMI_BASEBOARD_COUNT] =
{
    [DMI_BASEBOARD_UNKNOWN]                  = "Unknown",
    [DMI_BASEBOARD_OTHER]                    = "Other",
    [DMI_BASEBOARD_SERVER_BLADE]             = "Server blade",
    [DMI_BASEBOARD_CONNECTIVITY_SWITCH]      = "Connectivity switch",
    [DMI_BASEBOARD_SYSTEM_MANAGEMENT_MODULE] = "System management module",
    [DMI_BASEBOARD_PROCESSOR_MODULE]         = "Processor module",
    [DMI_BASEBOARD_IO_MODULE]                = "IO module",
    [DMI_BASEBOARD_MEMORY_MODULE]            = "Memory module",
    [DMI_BASEBOARD_DAUGHTERBOARD]            = "Daughterboard",
    [DMI_BASEBOARD_MOTHERBOARD]              = "Motherboard",
    [DMI_BASEBOARD_PROCESSOR_MEMORY_MODULE]  = "Processor/memory module",
    [DMI_BASEBOARD_PROCESSOR_IO_MODULE]      = "Processor/IO module",
    [DMI_BASEBOARD_INTERCONNECT_BOARD]       = "Interconnect board"
};

const dmi_attribute_spec_t dmi_baseboard_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_baseboard_table =
{
    .tag        = "baseboard",
    .name       = "Baseboard or module information",
    .type       = DMI_TYPE_BASEBOARD,
    .min_length = 0x0F,
    .attributes = dmi_baseboard_attrs
};

const char *dmi_baseboard_type_name(enum dmi_baseboard_type value)
{
    return dmi_name(dmi_baseboard_type_names, value, __DMI_BASEBOARD_COUNT);
}
