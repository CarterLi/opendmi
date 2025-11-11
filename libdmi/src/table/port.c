//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/port.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_port_type_names[] =
{
    {
        .id   = DMI_PORT_TYPE_NONE,
        .code = "none",
        .name = "None"
    },
    {
        .id   = DMI_PORT_TYPE_PARALLEL_XT_AT,
        .code = "parallel-xt-at",
        .name = "Parallel XT/AT compatible"
    },
    {
        .id   = DMI_PORT_TYPE_PARALLEL_PS2,
        .code = "parallel-ps2",
        .name = "Parallel PS/2"
    },
    {
        .id   = DMI_PORT_TYPE_PARALLEL_ECP,
        .code = "parallel-ecp",
        .name = "Parallel ECP"
    },
    {
        .id   = DMI_PORT_TYPE_PARALLEL_EPP,
        .code = "parallel-epp",
        .name = "Parallel EPP"
    },
    {
        .id   = DMI_PORT_TYPE_PARALLEL_ECP_EPP,
        .code = "parallel-ecp-epp",
        .name = "Parallel ECP/EPP"
    },
    {
        .id   = DMI_PORT_TYPE_SERIAL_XT_AT,
        .code = "serial-xt-at",
        .name = "Serial XT/AT compatible"
    },
    {
        .id   = DMI_PORT_TYPE_SERIAL_16450,
        .code = "serial-16450",
        .name = "Serial 16450 compatible"
    },
    {
        .id   = DMI_PORT_TYPE_SERIAL_16550,
        .code = "serial-16550",
        .name = "Serial 16550 compatible"
    },
    {
        .id   = DMI_PORT_TYPE_SERIAL_16550A,
        .code = "serial-16550a",
        .name = "Serial 16550A compatible"
    },
    {
        .id   = DMI_PORT_TYPE_SCSI,
        .code = "scsi",
        .name = "SCSI"
    },
    {
        .id   = DMI_PORT_TYPE_MIDI,
        .code = "midi",
        .name = "MIDI"
    },
    {
        .id   = DMI_PORT_TYPE_JOYSTICK,
        .code = "joystick",
        .name = "Joystick"
    },
    {
        .id   = DMI_PORT_TYPE_KEYBOARD,
        .code = "keyboard",
        .name = "Keyboard"
    },
    {
        .id   = DMI_PORT_TYPE_MOUSE,
        .code = "mouse",
        .name = "Mouse"
    },
    {
        .id   = DMI_PORT_TYPE_SCSI_SSA,
        .code = "ssa-scsi",
        .name = "SSA SCSI"
    },
    {
        .id   = DMI_PORT_TYPE_USB,
        .code = "usb",
        .name = "USB"
    },
    {
        .id   = DMI_PORT_TYPE_FIREWIRE,
        .code = "firewire",
        .name = "FireWire (IEEE P1394)"
    },
    {
        .id   = DMI_PORT_TYPE_PCMCIA_I,
        .code = "pcmcia-i",
        .name = "PCMCIA type I"
    },
    {
        .id   = DMI_PORT_TYPE_PCMCIA_II,
        .code = "pcmcia-ii",
        .name = "PCMCIA type II"
    },
    {
        .id   = DMI_PORT_TYPE_PCMCIA_III,
        .code = "pcmcia-iii",
        .name = "PCMCIA type III"
    },
    {
        .id   = DMI_PORT_TYPE_CARDBUS,
        .code = "cardbus",
        .name = "CardBus"
    },
    {
        .id   = DMI_PORT_TYPE_ACCESS_BUS,
        .code = "access-bus",
        .name = "ACCESS.bus"
    },
    {
        .id   = DMI_PORT_TYPE_SCSI_2,
        .code = "scsi-2",
        .name = "SCSI-2"
    },
    {
        .id   = DMI_PORT_TYPE_SCSI_WIDE,
        .code = "wide-scsi",
        .name = "Wide SCSI"
    },
    {
        .id   = DMI_PORT_TYPE_PC_98,
        .code = "pc-98",
        .name = "PC-98"
    },
    {
        .id   = DMI_PORT_TYPE_PC_98_HIRESO,
        .code = "pc-98-hireso",
        .name = "PC-98-Hireso"
    },
    {
        .id   = DMI_PORT_TYPE_PC_H98,
        .code = "pc-h98",
        .name = "PC-H98"
    },
    {
        .id   = DMI_PORT_TYPE_VIDEO,
        .code = "video",
        .name = "Video"
    },
    {
        .id   = DMI_PORT_TYPE_AUDIO,
        .code = "audio",
        .name = "Audio"
    },
    {
        .id   = DMI_PORT_TYPE_MODEM,
        .code = "modem",
        .name = "Modem"
    },
    {
        .id   = DMI_PORT_TYPE_NETWORK,
        .code = "network",
        .name = "Network"
    },
    {
        .id   = DMI_PORT_TYPE_SATA,
        .code = "sata",
        .name = "SATA"
    },
    {
        .id   = DMI_PORT_TYPE_SAS,
        .code = "sas",
        .name = "SAS"
    },
    {
        .id   = DMI_PORT_TYPE_MFDP,
        .code = "mfdp",
        .name = "MFDP (Multi-Function Display Port)"
    },
    {
        .id   = DMI_PORT_TYPE_THUNDERBOLT,
        .code = "thunderbolt",
        .name = "Thunderbolt"
    },
    {
        .id   = DMI_PORT_TYPE_8251,
        .code = "8251",
        .name = "8251 compatible"
    },
    {
        .id   = DMI_PORT_TYPE_8251_FIFO,
        .code = "8251-fifo",
        .name = "8251 FIFO compatible"
    },
    {
        .id   = DMI_PORT_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_port_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_port_table =
{
    .tag        = "port",
    .name       = "Port connector information",
    .type       = DMI_TYPE_PORT_CONNECTOR,
    .min_length = 0x09,
    .attributes = dmi_port_attrs
};

const char *dmi_port_type_name(enum dmi_port_type value)
{
    return dmi_name_lookup(dmi_port_type_names, value);
}
