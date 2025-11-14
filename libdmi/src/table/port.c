//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/name.h>
#include <opendmi/table/port.h>

static const dmi_name_t dmi_port_connector_names[] =
{
    {
        .id   = DMI_PORT_CONNECTOR_NONE,
        .code = "none",
        .name = "None"
    },
    {
        .id   = DMI_PORT_CONNECTOR_IEEE_1284_B,
        .code = "ieee-1284-b",
        .name = "Centronics"
    },
    {
        .id   = DMI_PORT_CONNECTOR_IEEE_1284_C,
        .code = "ieee-1284-c",
        .name = "Mini-Centronics"
    },
    {
        .id   = DMI_PORT_CONNECTOR_PROPRIETARY,
        .code = "proprietary",
        .name = "Proprietary"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DB_25_M,
        .code = "db-25-m",
        .name = "DB-25 pin male"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DB_25_F,
        .code = "db-25-f",
        .name = "DB-25 pin female"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DB_15_M,
        .code = "db-15-m",
        .name = "DB-15 pin male"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DB_15_F,
        .code = "db-15-f",
        .name = "DB-15 pin female"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DB_9_M,
        .code = "db-9-m",
        .name = "DB-9 pin male"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DB_9_F,
        .code = "db-9-f",
        .name = "DB-9 pin female"
    },
    {
        .id   = DMI_PORT_CONNECTOR_RJ_11,
        .code = "rj-11",
        .name = "RJ-11"
    },
    {
        .id   = DMI_PORT_CONNECTOR_RJ_45,
        .code = "rj-45",
        .name = "RJ-45"
    },
    {
        .id   = DMI_PORT_CONNECTOR_MINI_SCSI_50PIN,
        .code = "mini-scsi-50pin",
        .name = "50-pin MiniSCSI"
    },
    {
        .id   = DMI_PORT_CONNECTOR_MINI_DIN,
        .code = "mini-din",
        .name = "Mini-DIN"
    },
    {
        .id = DMI_PORT_CONNECTOR_MICRO_DIN,
        .code = "micro-din",
        .name = "Micro-DIN"
    },
    {
        .id   = DMI_PORT_CONNECTOR_PS2,
        .code = "ps-2",
        .name = "PS/2"
    },
    {
        .id   = DMI_PORT_CONNECTOR_INFRARED,
        .code = "infrared",
        .name = "Infrared"
    },
    {
        .id   = DMI_PORT_CONNECTOR_HP_HIL,
        .code = "hp-hil",
        .name = "HP-HIL"
    },
    {
        .id   = DMI_PORT_CONNECTOR_ACCESS_BUS,
        .code = "access-bus",
        .name = "Access Bus (USB)"
    },
    {
        .id   = DMI_PORT_CONNECTOR_SSA_SCSI,
        .code = "ssa-scsi",
        .name = "SSA SCSI"
    },
    {
        .id   = DMI_PORT_CONNECTOR_CIRCULAR_DIN_8_M,
        .code = "circular-din-8-m",
        .name = "Circular DIN-8 male"
    },
    {
        .id   = DMI_PORT_CONNECTOR_CIRCULAR_DIN_8_F,
        .code = "circular-din-8-f",
        .name = "Circular DIN-8 female"
    },
    {
        .id   = DMI_PORT_CONNECTOR_ONBOARD_IDE,
        .code = "onboard-ide",
        .name = "On Board IDE"
    },
    {
        .id   = DMI_PORT_CONNECTOR_ONBOARD_FLOPPY,
        .code = "onboard-floppy",
        .name = "On Board Floppy"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DIL_9PIN,
        .code = "dil-9pin",
        .name = "9-pin Dual Inline (pin 10 cut)"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DIL_25PIN,
        .code = "dil-25-pin",
        .name = "25-pin Dual Inline (pin 26 cut)"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DIL_50PIN,
        .code = "dil-50pin",
        .name = "50-pin Dual Inline"
    },
    {
        .id   = DMI_PORT_CONNECTOR_DIL_68PIN,
        .code = "dil-68pin",
        .name = "68-pin Dual Inline"
    },
    {
        .id   = DMI_PORT_CONNECTOR_ONBOARD_SOUND,
        .code = "onboard-sound",
        .name = "On Board Sound Input from CD-ROM"
    },
    {
        .id   = DMI_PORT_CONNECTOR_IEEE_1284_C_14,
        .code = "ieee-1284-c-14",
        .name = "Mini-Centronics Type-14"
    },
    {
        .id   = DMI_PORT_CONNECTOR_IEEE_1284_C_26,
        .code = "ieee-1284-c-26",
        .name = "Mini-Centronics Type-26"
    },
    {
        .id   = DMI_PORT_CONNECTOR_MINI_JACK,
        .code = "mini-jack",
        .name = "Mini-jack (headphones)"
    },
    {
        .id   = DMI_PORT_CONNECTOR_BNC,
        .code = "bnc",
        .name = "BNC"
    },
    {
        .id   = DMI_PORT_CONNECTOR_IEEE_1394,
        .code = "ieee-1394",
        .name = "IEEE 1394"
    },
    {
        .id   = DMI_PORT_CONNECTOR_SAS_SATA,
        .code = "sas-sata",
        .name = "SAS/SATA Plug Receptacle"
    },
    {
        .id   = DMI_PORT_CONNECTOR_USB_C,
        .code = "usb-c",
        .name = "USB Type-C Receptacle"
    },
    {
        .id   = DMI_PORT_CONNECTOR_PC_98,
        .code = "pc-98",
        .name = "PC-98"
    },
    {
        .id   = DMI_PORT_CONNECTOR_PC_98_HIRESO,
        .code = "pc-98-hireso",
        .name = "PC-98 Hireso"
    },
    {
        .id   = DMI_PORT_CONNECTOR_PC_H98,
        .code = "pc-h98",
        .name = "PC-H98"
    },
    {
        .id   = DMI_PORT_CONNECTOR_PC_98_NOTE,
        .code = "pc-98-note",
        .name = "PC-98 Note"
    },
    {
        .id   = DMI_PORT_CONNECTOR_PC_98_FULL,
        .code = "pc-98-full",
        .name = "PC-98 Full"
    },
    {
        .id   = DMI_PORT_CONNECTOR_OTHER,
        .code = "other",
        .name = "Other"
    },
    DMI_NAME_NULL
};

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
    DMI_ATTRIBUTE(dmi_port_t, internal_designator, STRING, {
        .code   = "internal-designator",
        .name   = "Internal reference designator"
    }),
    DMI_ATTRIBUTE(dmi_port_t, internal_connector, ENUM, {
        .code   = "internal-connector",
        .name   = "Internal connector type",
        .values = dmi_port_connector_names
    }),
    DMI_ATTRIBUTE(dmi_port_t, external_designator, STRING, {
        .code   = "external-designator",
        .name   = "External reference designator"
    }),
    DMI_ATTRIBUTE(dmi_port_t, external_connector, ENUM, {
        .code   = "external-connector",
        .name   = "External connector type",
        .values = dmi_port_connector_names
    }),
    DMI_ATTRIBUTE(dmi_port_t, type, ENUM, {
        .code   = "port-type",
        .name   = "Port type",
        .values = dmi_port_type_names
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_port_table =
{
    .tag        = "port",
    .name       = "Port connector information",
    .type       = DMI_TYPE_PORT_CONNECTOR,
    .min_length = 0x09,
    .attributes = dmi_port_attrs,
    .handlers   = {
        .decoder     = (dmi_table_decoder_t)dmi_port_decode,
        .deallocator = (dmi_table_deallocator_t)dmi_port_destroy
    }
};

const char *dmi_port_connector_name(dmi_port_connector_t value)
{
    return dmi_name_lookup(dmi_port_connector_names, value);
}

const char *dmi_port_type_name(dmi_port_type_t value)
{
    return dmi_name_lookup(dmi_port_type_names, value);
}

dmi_port_t *dmi_port_decode(const dmi_table_t *table)
{
    dmi_port_t *info = nullptr;
    dmi_port_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    info->internal_designator = dmi_table_string(table, data->internal_designator);
    info->internal_connector  = data->internal_connector;
    info->external_designator = dmi_table_string(table, data->external_designator);
    info->external_connector  = data->external_connector;
    info->type                = data->type;

    return info;
}

void dmi_port_destroy(dmi_port_t *info)
{
    free(info);
}
