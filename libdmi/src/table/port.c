//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/port.h>
#include <opendmi/utils.h>

static const char *dmi_port_type_names[] =
{
    [DMI_PORT_TYPE_NONE]             = "None",
    [DMI_PORT_TYPE_PARALLEL_XT_AT]   = "Parallel XT/AT compatible",
    [DMI_PORT_TYPE_PARALLEL_PS2]     = "Parallel PS/2",
    [DMI_PORT_TYPE_PARALLEL_ECP]     = "Parallel ECP",
    [DMI_PORT_TYPE_PARALLEL_EPP]     = "Parallel EPP",
    [DMI_PORT_TYPE_PARALLEL_ECP_EPP] = "Parallel ECP/EPP",
    [DMI_PORT_TYPE_SERIAL_XT_AT]     = "Serial XT/AT compatible",
    [DMI_PORT_TYPE_SERIAL_16450]     = "Serial 16450 compatible",
    [DMI_PORT_TYPE_SERIAL_16550]     = "Serial 16550 compatible",
    [DMI_PORT_TYPE_SERIAL_16550A]    = "Serial 16550A compatible",
    [DMI_PORT_TYPE_SCSI]             = "SCSI",
    [DMI_PORT_TYPE_MIDI]             = "MIDI",
    [DMI_PORT_TYPE_JOYSTICK]         = "Joystick",
    [DMI_PORT_TYPE_KEYBOARD]         = "Keyboard",
    [DMI_PORT_TYPE_MOUSE]            = "Mouse",
    [DMI_PORT_TYPE_SCSI_SSA]         = "SSA SCSI",
    [DMI_PORT_TYPE_USB]              = "USB",
    [DMI_PORT_TYPE_FIREWIRE]         = "FireWire (IEEE P1394)",
    [DMI_PORT_TYPE_PCMCIA_I]         = "PCMCIA type I",
    [DMI_PORT_TYPE_PCMCIA_II]        = "PCMCIA type II",
    [DMI_PORT_TYPE_PCMCIA_III]       = "PCMCIA type III",
    [DMI_PORT_TYPE_CARDBUS]          = "CardBus",
    [DMI_PORT_TYPE_ACCESS_BUS]       = "ACCESS.bus",
    [DMI_PORT_TYPE_SCSI_II]          = "SCSI-II",
    [DMI_PORT_TYPE_SCSI_WIDE]        = "Wide SCSI",
    [DMI_PORT_TYPE_PC_98]            = "PC-98",
    [DMI_PORT_TYPE_PC_98_HIRESO]     = "PC-98-Hireso",
    [DMI_PORT_TYPE_PC_H98]           = "PC-H98",
    [DMI_PORT_TYPE_VIDEO]            = "Video",
    [DMI_PORT_TYPE_AUDIO]            = "Audio",
    [DMI_PORT_TYPE_MODEM]            = "Modem",
    [DMI_PORT_TYPE_NETWORK]          = "Network",
    [DMI_PORT_TYPE_SATA]             = "SATA",
    [DMI_PORT_TYPE_SAS]              = "SAS",
    [DMI_PORT_TYPE_MFDP]             = "MFDP (Multi-Function Display Port)",
    [DMI_PORT_TYPE_THUNDERBOLT]      = "Thunderbolt",
    [DMI_PORT_TYPE_8251]             = "8251 compatible",
    [DMI_PORT_TYPE_8251_FIFO]        = "8251 FIFO compatible",
    [DMI_PORT_TYPE_OTHER]            = "Other"
};

const struct dmi_attribute_spec dmi_port_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_port_table_spec =
{
    .tag        = "port",
    .name       = "Port connector information",
    .type       = DMI_TYPE_PORT_CONNECTOR,
    .min_length = 0x09,
    .attributes = dmi_port_attrs
};

const char *dmi_port_type_name(enum dmi_port_type value)
{
    return dmi_name(dmi_port_type_names, value, __DMI_PORT_TYPE_COUNT);
}
