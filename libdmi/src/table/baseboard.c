//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/baseboard.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_baseboard_type_names[] =
{
    {
        .id   = DMI_BASEBOARD_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_SERVER_BLADE,
        .code = "server-blade",
        .name = "Server blade"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_CONNECTIVITY_SWITCH,
        .code = "connectivity-switch",
        .name = "Connectivity switch"
    },
    {
        .id   =  DMI_BASEBOARD_TYPE_SYSTEM_MANAGEMENT_MODULE,
        .code = "system-management-module",
        .name = "System management module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_PROCESSOR_MODULE,
        .code = "processor-module",
        .name = "Processor module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_IO_MODULE,
        .code = "io-module",
        .name = "IO module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_MEMORY_MODULE,
        .code = "memory-module",
        .name = "Memory module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_DAUGHTERBOARD,
        .code = "daughterboard",
        .name = "Daughterboard"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_MOTHERBOARD,
        .code = "motherboard",
        .name = "Motherboard"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_PROCESSOR_MEMORY_MODULE,
        .code = "processor-memory-module",
        .name = "Processor/memory module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_PROCESSOR_IO_MODULE,
        .code = "processor-io-module",
        .name = "Processor/IO module"
    },
    {
        .id   = DMI_BASEBOARD_TYPE_INTERCONNECT_BOARD,
        .code = "interconnect-board",
        .name = "Interconnect board"
    },
    DMI_NAME_NULL
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
    return dmi_name_lookup(dmi_baseboard_type_names, value);
}
