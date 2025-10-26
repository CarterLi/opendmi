//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_PORT_H
#define OPENDMI_TABLE_PORT_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Port types
 */
enum dmi_port_type
{
    DMI_PORT_TYPE_NONE             = 0x00, ///< None
    DMI_PORT_TYPE_PARALLEL_XT_AT   = 0x01, ///< Parallel XT/AT compatible
    DMI_PORT_TYPE_PARALLEL_PS2     = 0x02, ///< Parallel PS/2
    DMI_PORT_TYPE_PARALLEL_ECP     = 0x03, ///< Parallel ECP
    DMI_PORT_TYPE_PARALLEL_EPP     = 0x04, ///< Parallel EPP
    DMI_PORT_TYPE_PARALLEL_ECP_EPP = 0x05, ///< Parallel ECP/EPP
    DMI_PORT_TYPE_SERIAL_XT_AT     = 0x06, ///< Serial XT/AT compatible
    DMI_PORT_TYPE_SERIAL_16450     = 0x07, ///< Serial 16450 compatible
    DMI_PORT_TYPE_SERIAL_16550     = 0x08, ///< Serial 16550 compatible
    DMI_PORT_TYPE_SERIAL_16550A    = 0x09, ///< Serial 16550A compatible
    DMI_PORT_TYPE_SCSI             = 0x0A, ///< SCSI
    DMI_PORT_TYPE_MIDI             = 0x0B, ///< MIDI
    DMI_PORT_TYPE_JOYSTICK         = 0x0C, ///< Joystick
    DMI_PORT_TYPE_KEYBOARD         = 0x0D, ///< Keyboard
    DMI_PORT_TYPE_MOUSE            = 0x0E, ///< Mouse
    DMI_PORT_TYPE_SCSI_SSA         = 0x0F, ///< SSA SCSI
    DMI_PORT_TYPE_USB              = 0x10, ///< USB
    DMI_PORT_TYPE_FIREWIRE         = 0x11, ///< FireWire (IEEE P1394)
    DMI_PORT_TYPE_PCMCIA_I         = 0x12, ///< PCMCIA type I
    DMI_PORT_TYPE_PCMCIA_II        = 0x13, ///< PCMCIA type II
    DMI_PORT_TYPE_PCMCIA_III       = 0x14, ///< PCMCIA type III
    DMI_PORT_TYPE_CARDBUS          = 0x15, ///< CardBus
    DMI_PORT_TYPE_ACCESS_BUS       = 0x16, ///< ACCESS.bus
    DMI_PORT_TYPE_SCSI_II          = 0x17, ///< SCSI-II
    DMI_PORT_TYPE_SCSI_WIDE        = 0x18, ///< Wide SCSI
    DMI_PORT_TYPE_PC_98            = 0x19, ///< PC-98
    DMI_PORT_TYPE_PC_98_HIRESO     = 0x1A, ///< PC-98-Hireso
    DMI_PORT_TYPE_PC_H98           = 0x1B, ///< PC-H98
    DMI_PORT_TYPE_VIDEO            = 0x1C, ///< Video
    DMI_PORT_TYPE_AUDIO            = 0x1D, ///< Audio
    DMI_PORT_TYPE_MODEM            = 0x1E, ///< Modem
    DMI_PORT_TYPE_NETWORK          = 0x1F, ///< Network
    DMI_PORT_TYPE_SATA             = 0x20, ///< SATA
    DMI_PORT_TYPE_SAS              = 0x21, ///< SAS
    DMI_PORT_TYPE_MFDP             = 0x22, ///< MFDP (Multi-Function Display Port)
    DMI_PORT_TYPE_THUNDERBOLT      = 0x23, ///< Thunderbolt
    DMI_PORT_TYPE_8251             = 0xA0, ///< 8251 compatible
    DMI_PORT_TYPE_8251_FIFO        = 0xA1, ///< 8251 FIFO compatible
    DMI_PORT_TYPE_OTHER            = 0xFF, ///< Other
    __DMI_PORT_TYPE_COUNT
};

__BEGIN_DECLS

const char *dmi_port_type_name(enum dmi_port_type value);

__END_DECLS

#endif // !OPENDMI_TABLE_PORT_H
