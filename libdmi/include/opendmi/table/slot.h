//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_SLOT_H
#define OPENDMI_TABLE_SLOT_H

#include <opendmi/table.h>

/**
 * @brief Slot type identifiers.
 */
enum dmi_slot_type
{
    DMI_SLOT_TYPE_OTHER                 = 0x01, ///< Other
    DMI_SLOT_TYPE_UNKNOWN               = 0x02, ///< Unknown
    DMI_SLOT_TYPE_ISA                   = 0x03, ///< ISA
    DMI_SLOT_TYPE_MCA                   = 0x04, ///< MCA
    DMI_SLOT_TYPE_EISA                  = 0x05, ///< EISA
    DMI_SLOT_TYPE_PCI                   = 0x06, ///< PCI
    DMI_SLOT_TYPE_PCMCIA                = 0x07, ///< PC card (PCMCIA)
    DMI_SLOT_TYPE_VESA                  = 0x08, ///< VL-VESA
    DMI_SLOT_TYPE_PROPRIETARY           = 0x09, ///< Proprietary
    DMI_SLOT_TYPE_PROCESSOR_CARD        = 0x0A, ///< Processor card slot
    DMI_SLOT_TYPE_MEMORY_CARD           = 0x0B, ///< Memory card slot
    DMI_SLOT_TYPE_IO_RISER_CARD         = 0x0C, ///< I/O riser card slot
    DMI_SLOT_TYPE_NUBUS                 = 0x0D, ///< NuBus
    DMI_SLOT_TYPE_PCI_66                = 0x0E, ///< PCI 66 Mhz
    DMI_SLOT_TYPE_AGP                   = 0x0F, ///< AGP
    DMI_SLOT_TYPE_AGP_2X                = 0x10, ///< AGP 2x
    DMI_SLOT_TYPE_AGP_4X                = 0x11, ///< AGP 4x
    DMI_SLOT_TYPE_PCI_X                 = 0x12, ///< PCI-X
    DMI_SLOT_TYPE_AGP_8X                = 0x13, ///< AGP 8x
    DMI_SLOT_TYPE_M2_S1_DP              = 0x14, ///< M.2 Socket 1-DP (Mechanical key A)
    DMI_SLOT_TYPE_M2_S1_SD              = 0x15, ///< M.2 Socket 1-SD (Mechanical key E)
    DMI_SLOT_TYPE_M2_S2                 = 0x16, ///< M.2 Socket 2 (Mechanical key B)
    DMI_SLOT_TYPE_M2_S3                 = 0x17, ///< M.2 Socket 3 (Mechanical key M)
    DMI_SLOT_TYPE_MXM_I                 = 0x18, ///< MXM Type I
    DMI_SLOT_TYPE_MXM_II                = 0x19, ///< MXM Type II
    DMI_SLOT_TYPE_MXM_III_STD           = 0x1A, ///< MXM Type III (Standard connector)
    DMI_SLOT_TYPE_MXM_III_HE            = 0x1B, ///< MXM Type III (HE connector)
    DMI_SLOT_TYPE_MXM_IV                = 0x1C, ///< MXM Type IV
    DMI_SLOT_TYPE_MXM_30_A              = 0x1D, ///< MXM 3.0 Type A
    DMI_SLOT_TYPE_MXM_30_B              = 0x1E, ///< MXM 3.0 Type B
    DMI_SLOT_TYPE_PCI_E_G2_SFF8639      = 0x1F, ///< PCI Express Gen 2 SFF-8639 (U.2)
    DMI_SLOT_TYPE_PCI_E_G3_SFF8639      = 0x20, ///< PCI Express Gen 3 SFF-8639 (U.2)
    DMI_SLOT_TYPE_PCI_E_MINI_52PIN_BSKO = 0x21, ///< PCI Express Mini 52-pin (CEM spec. 2.0) with bottom-side keep-outs
    DMI_SLOT_TYPE_PCI_E_MINI_52PIN      = 0x22, ///< PCI Express Mini 52-pin (CEM spec. 2.0) without bottom-side keep-outs
    DMI_SLOT_TYPE_PCI_E_MINI_76PIN      = 0x23, ///< PCI Express Mini 76-pin (CEM spec. 2.0)
    DMI_SLOT_TYPE_PCI_E_G4_SFF8639      = 0x24, ///< PCI Express Gen 4 SFF-8639 (U.2)
    DMI_SLOT_TYPE_PCI_E_G5_SFF8639      = 0x25, ///< PCI Express Gen 5 SFF-8639 (U.2)
    DMI_SLOT_TYPE_OCP_NIC_30_SFF        = 0x26, ///< OCP NIC 3.0 Small Form Factor (SFF)
    DMI_SLOT_TYPE_OCP_NIC_30_LFF        = 0x27, ///< OCP NIC 3.0 Large Form Factor (LFF)
    DMI_SLOT_TYPP_OCP_NIC_LEGACY        = 0x28, ///< OCP NIC prior to 3.0
    // Unassigned: 0x29 .. 0x2F
    DMI_SLOT_TYPE_CXL_FLEXBUS_10        = 0x30, ///< CXL FlexBus 1.0
    DMI_SLOT_TYPE_PC_98_C20             = 0xA0, ///< PC-98/C20
    DMI_SLOT_TYPE_PC_98_C24             = 0xA1, ///< PC-98/C24
    DMI_SLOT_TYPE_PC_98_E               = 0xA2, ///< PC-98/E
    DMI_SLOT_TYPE_PC_98_LOCAL_BUS       = 0xA3, ///< PC-98/Local bus
    DMI_SLOT_TYPE_PC_98_CARD            = 0xA4, ///< PC-98/Card
    DMI_SLOT_TYPE_PCI_E                 = 0xA5, ///< PCI Express
    DMI_SLOT_TYPE_PCI_E_X1              = 0xA6, ///< PCI Express x1
    DMI_SLOT_TYPE_PCI_E_X2              = 0xA7, ///< PCI Express x2
    DMI_SLOT_TYPE_PCI_E_X4              = 0xA8, ///< PCI Express x4
    DMI_SLOT_TYPE_PCI_E_X8              = 0xA9, ///< PCI Express x8
    DMI_SLOT_TYPE_PCI_E_X16             = 0xAA, ///< PCI Express x16
    DMI_SLOT_TYPE_PCI_E_G2              = 0xAB, ///< PCI Express Gen 2
    DMI_SLOT_TYPE_PCI_E_G2_X1           = 0xAC, ///< PCI Express Gen 2 x1
    DMI_SLOT_TYPE_PCI_E_G2_X2           = 0xAD, ///< PCI Express Gen 2 x2
    DMI_SLOT_TYPE_PCI_E_G2_X4           = 0xAE, ///< PCI Express Gen 2 x4
    DMI_SLOT_TYPE_PCI_E_G2_X8           = 0xAF, ///< PCI Express Gen 2 x8
    DMI_SLOT_TYPE_PCI_E_G2_X16          = 0xB0, ///< PCI Express Gen 2 x16
    DMI_SLOT_TYPE_PCI_E_G3              = 0xB1, ///< PCI Express Gen 3
    DMI_SLOT_TYPE_PCI_E_G3_X1           = 0xB2, ///< PCI Express Gen 3 x1
    DMI_SLOT_TYPE_PCI_E_G3_X2           = 0xB3, ///< PCI Express Gen 3 x2
    DMI_SLOT_TYPE_PCI_E_G3_X4           = 0xB4, ///< PCI Express Gen 3 x4
    DMI_SLOT_TYPE_PCI_E_G3_X8           = 0xB5, ///< PCI Express Gen 3 x8
    DMI_SLOT_TYPE_PCI_E_G3_X16          = 0xB6, ///< PCI Express Gen 3 x16
    // Unassigned: 0xB7
    DMI_SLOT_TYPE_PCI_E_G4              = 0xB8, ///< PCI Express Gen 4
    DMI_SLOT_TYPE_PCI_E_G4_X1           = 0xB9, ///< PCI Express Gen 4 x1
    DMI_SLOT_TYPE_PCI_E_G4_X2           = 0xBA, ///< PCI Express Gen 4 x2
    DMI_SLOT_TYPE_PCI_E_G4_X4           = 0xBB, ///< PCI Express Gen 4 x4
    DMI_SLOT_TYPE_PCI_E_G4_X8           = 0xBC, ///< PCI Express Gen 4 x8
    DMI_SLOT_TYPE_PCI_E_G4_X16          = 0xBD, ///< PCI Express Gen 4 x16
    DMI_SLOT_TYPE_PCI_E_G5              = 0xBE, ///< PCI Express Gen 5
    DMI_SLOT_TYPE_PCI_E_G5_X1           = 0xBF, ///< PCI Express Gen 5 x1
    DMI_SLOT_TYPE_PCI_E_G5_X2           = 0xC0, ///< PCI Express Gen 5 x2
    DMI_SLOT_TYPE_PCI_E_G5_X4           = 0xC1, ///< PCI Express Gen 5 x4
    DMI_SLOT_TYPE_PCI_E_G5_X8           = 0xC2, ///< PCI Express Gen 5 x8
    DMI_SLOT_TYPE_PCI_E_G5_X16          = 0xC3, ///< PCI Express Gen 5 x16
    DMI_SLOT_TYPE_PCI_E_G6              = 0xC4, ///< PCI Express Gen 6 and beyond
    DMI_SLOT_TYPE_EDSFF_E1              = 0xC5, ///< Enterprise and datacenter 1U E1 form factor slot (EDSFF E1.S, E1.L)
    DMI_SLOT_TYPE_EDSFF_E3              = 0xC6, ///< Enterprise and datacenter 3" E3 form factor slot (EDSFF E3.S, E3.L)
};

/**
 * @brief Slot data bus width values.
 */
enum dmi_slot_width
{
    DMI_SLOT_WIDTH_OTHER   = 0x01, ///< Other
    DMI_SLOT_WIDTH_UNKNOWN = 0x02, ///< Unknown
    DMI_SLOT_WIDTH_8_BIT   = 0x03, ///< 8 bit
    DMI_SLOT_WIDTH_16_BIT  = 0x04, ///< 16 bit
    DMI_SLOT_WIDTH_32_BIT  = 0x05, ///< 32 bit
    DMI_SLOT_WIDTH_64_BIT  = 0x06, ///< 64 bit
    DMI_SLOT_WIDTH_128_BIT = 0x07, ///< 128 bit
    DMI_SLOT_WIDTH_1X      = 0x08, ///< 1x or x1
    DMI_SLOT_WIDTH_2X      = 0x09, ///< 2x or x2
    DMI_SLOT_WIDTH_4X      = 0x0A, ///< 4x or x4
    DMI_SLOT_WIDTH_8X      = 0x0B, ///< 8x or x8
    DMI_SLOT_WIDTH_12X     = 0x0C, ///< 12x or x12
    DMI_SLOT_WIDTH_16X     = 0x0D, ///< 16x or x16
    DMI_SLOT_WIDTH_32X     = 0x0E, ///< 32x or x32
};

/**
 * @brief Slot usage values.
 */
enum dmi_slot_usage
{
    DMI_SLOT_USAGE_OTHER       = 0x01, ///< Other
    DMI_SLOT_USAGE_UNKNOWN     = 0x02, ///< Unknown
    DMI_SLOT_USAGE_AVAILABLE   = 0x03, ///< Available
    DMI_SLOT_USAGE_IN_USE      = 0x04, ///< In use
    DMI_SLOT_USAGE_UNAVAILABLE = 0x05, ///< Unavailable
};

DMI_PACKED_STRUCT(dmi_slot_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief String number for reference designation. Example: "PCI-1".
     * @since SMBIOS 2.0
     */
    dmi_string_t designator;

    /**
     * @brief Slot type.
     * @since SMBIOS 2.0
     */
    enum dmi_slot_type type : 8;

    /**
     * @brief Data bus width.
     * @since SMBIOS 2.0
     */
    enum dmi_slot_width width : 8;

    /**
     * @brief Current usage.
     * @since SMBIOS 2.0
     */
    enum dmi_slot_usage usage : 8;

    /**
     * @brief Slot length.
     * @since SMBIOS 2.0
     */
    dmi_byte_t length : 8;

    /**
     * @brief Slot identifier.
     * @since SMBIOS 2.0
     */
    dmi_word_t id;

    /**
     * @since SMBIOS 2.0
     */
    dmi_byte_t features;

    /**
     * @since SMBIOS 2.1
     */
    dmi_byte_t features_ex;

    /**
     * @since SMBIOS 2.6
     */
    dmi_word_t segment_group;

    /**
     * @since SMBIOS 2.6
     */
    dmi_byte_t bus_number;

    struct
    {
        /**
         * @since SMBIOS 2.6
         */
        dmi_byte_t function_number : 3;

        /**
         * @since SMBIOS 2.6
         */
        dmi_byte_t device_number : 5;
    };
    
    dmi_byte_t data_bus_width;

    dmi_byte_t peer_group_count;

    dmi_byte_t peer_groups[];
};

struct dmi_slot_data_ex
{
    dmi_byte_t information;
    dmi_byte_t physical_width;
    dmi_byte_t pitch;
    dmi_byte_t height;
};

struct dmi_slot_info
{
    const char *designator;
};

/**
 * @brief System slots table specification.
 */
extern const dmi_table_spec_t dmi_slot_table;

__BEGIN_DECLS

const char *dmi_slot_type_name(enum dmi_slot_type value);
const char *dmi_slot_width_name(enum dmi_slot_width value);
const char *dmi_slot_usage_name(enum dmi_slot_usage value);

__END_DECLS

#endif // !OPENDMI_TABLE_SLOT_H
