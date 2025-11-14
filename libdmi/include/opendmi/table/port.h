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

typedef enum dmi_port_connector
{
    DMI_PORT_CONNECTOR_NONE             = 0x00, ///< None
    DMI_PORT_CONNECTOR_IEEE_1284_B      = 0x01, ///< Centronics
    DMI_PORT_CONNECTOR_IEEE_1284_C      = 0x02, ///< Mini-Centronics
    DMI_PORT_CONNECTOR_PROPRIETARY      = 0x03, ///< Proprietary
    DMI_PORT_CONNECTOR_DB_25_M          = 0x04, ///< DB-25 pin male
    DMI_PORT_CONNECTOR_DB_25_F          = 0x05, ///< DB-25 pin female
    DMI_PORT_CONNECTOR_DB_15_M          = 0x06, ///< DB-15 pin male
    DMI_PORT_CONNECTOR_DB_15_F          = 0x07, ///< DB-15 pin female
    DMI_PORT_CONNECTOR_DB_9_M           = 0x08, ///< DB-9 pin male
    DMI_PORT_CONNECTOR_DB_9_F           = 0x09, ///< DB-9 pin female
    DMI_PORT_CONNECTOR_RJ_11            = 0x0A, ///< RJ-11
    DMI_PORT_CONNECTOR_RJ_45            = 0x0B, ///< RJ-45
    DMI_PORT_CONNECTOR_MINI_SCSI_50PIN  = 0x0C, ///< 50-pin MiniSCSI
    DMI_PORT_CONNECTOR_MINI_DIN         = 0x0D, ///< Mini-DIN
    DMI_PORT_CONNECTOR_MICRO_DIN        = 0x0E, ///< Micro-DIN
    DMI_PORT_CONNECTOR_PS2              = 0x0F, ///< PS/2
    DMI_PORT_CONNECTOR_INFRARED         = 0x10, ///< Infrared
    DMI_PORT_CONNECTOR_HP_HIL           = 0x11, ///< HP-HIL
    DMI_PORT_CONNECTOR_ACCESS_BUS       = 0x12, ///< Access Bus (USB)
    DMI_PORT_CONNECTOR_SSA_SCSI         = 0x13, ///< SSA SCSI
    DMI_PORT_CONNECTOR_CIRCULAR_DIN_8_M = 0x14, ///< Circular DIN-8 male
    DMI_PORT_CONNECTOR_CIRCULAR_DIN_8_F = 0x15, ///< Circular DIN-8 female
    DMI_PORT_CONNECTOR_ONBOARD_IDE      = 0x16, ///< On Board IDE
    DMI_PORT_CONNECTOR_ONBOARD_FLOPPY   = 0x17, ///< On Board Floppy
    DMI_PORT_CONNECTOR_DIL_9PIN         = 0x18, ///< 9-pin Dual Inline (pin 10 cut)
    DMI_PORT_CONNECTOR_DIL_25PIN        = 0x19, ///< 25-pin Dual Inline (pin 26 cut)
    DMI_PORT_CONNECTOR_DIL_50PIN        = 0x1A, ///< 50-pin Dual Inline
    DMI_PORT_CONNECTOR_DIL_68PIN        = 0x1B, ///< 68-pin Dual Inline
    DMI_PORT_CONNECTOR_ONBOARD_SOUND    = 0x1C, ///< On Board Sound Input from CD-ROM
    DMI_PORT_CONNECTOR_IEEE_1284_C_14   = 0x1D, ///< Mini-Centronics Type-14
    DMI_PORT_CONNECTOR_IEEE_1284_C_26   = 0x1E, ///< Mini-Centronics Type-26
    DMI_PORT_CONNECTOR_MINI_JACK        = 0x1F, ///< Mini-jack (headphones)
    DMI_PORT_CONNECTOR_BNC              = 0x20, ///< BNC
    DMI_PORT_CONNECTOR_IEEE_1394        = 0x21, ///< IEEE 1394
    DMI_PORT_CONNECTOR_SAS_SATA         = 0x22, ///< SAS/SATA Plug Receptacle
    DMI_PORT_CONNECTOR_USB_C            = 0x23, ///< USB Type-C Receptacle
    DMI_PORT_CONNECTOR_PC_98            = 0xA0, ///< PC-98
    DMI_PORT_CONNECTOR_PC_98_HIRESO     = 0xA1, ///< PC-98 Hireso
    DMI_PORT_CONNECTOR_PC_H98           = 0xA2, ///< PC-H98
    DMI_PORT_CONNECTOR_PC_98_NOTE       = 0xA3, ///< PC-98 Note
    DMI_PORT_CONNECTOR_PC_98_FULL       = 0xA4, ///< PC-98 Full
    DMI_PORT_CONNECTOR_OTHER            = 0xFF, ///< Other
} dmi_port_connector_t;

/**
 * @brief Port types
 */
typedef enum dmi_port_type
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
    DMI_PORT_TYPE_SCSI_2           = 0x17, ///< SCSI-2
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
} dmi_port_type_t;

/**
 * @brief Port connector information table (type 8).
 */
DMI_PACKED_STRUCT(dmi_port_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief String number for internal reference designator, that is,
     * internal to the system enclosure. Example: "J101".
     */
    dmi_string_t internal_designator;

    /**
     * @brief Internal connector type.
     */
    dmi_byte_t internal_connector;

    /**
     * @brief String number for the external reference designation, that is,
     * external to the system enclosure. Example: "COM A".
     */
    dmi_string_t external_designator;

    /**
     * @brief External connector type.
     */
    dmi_byte_t external_connector;

    /**
     * @brief Port type.
     */
    dmi_byte_t type;
};

#ifndef DMI_PORT_DATA_T
#define DMI_PORT_DATA_T
typedef struct dmi_port_data dmi_port_data_t;
#endif // !DMI_PORT_DATA_T

/**
 * @brief Port connector information.
 */
struct dmi_port
{
    /**
     * @brief Internal reference designator, that is, internal to the system
     * enclosure. Example: "J101".
     */
    const char *internal_designator;

    /**
     * @brief Internal connector type.
     */
    dmi_port_connector_t internal_connector;

    /**
     * @brief External reference designation external to the system enclosure.
     * Example: "COM A".
     */
    const char *external_designator;

    /**
     * @brief External connector type.
     */
    dmi_port_connector_t external_connector;

    /**
     * @brief Port type.
     */
    dmi_port_type_t type;
};

#ifndef DMI_PORT_T
#define DMI_PORT_T
typedef struct dmi_port dmi_port_t;
#endif // !DMI_PORT_T

/**
 * @brief Port connector information table specification.
 */
extern const dmi_table_spec_t dmi_port_table;

__BEGIN_DECLS

const char *dmi_port_connector_name(dmi_port_connector_t value);
const char *dmi_port_type_name(dmi_port_type_t value);

dmi_port_t *dmi_port_decode(const dmi_table_t *table);
void dmi_port_destroy(dmi_port_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_PORT_H
