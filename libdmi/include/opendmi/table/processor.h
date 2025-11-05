//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_PROCESSOR_H
#define OPENDMI_TABLE_PROCESSOR_H

#pragma once

#include <opendmi/table.h>

enum dmi_processor_type
{
    DMI_PROCESSOR_TYPE_OTHER   = 0x01, ///< Other
    DMI_PROCESSOR_TYPE_UNKNOWN = 0x02, ///< Unknown
    DMI_PROCESSOR_TYPE_CENTRAL = 0x03, ///< Central processor
    DMI_PROCESSOR_TYPE_MATH    = 0x04, ///< Math processor
    DMI_PROCESSOR_TYPE_DSP     = 0x05, ///< DSP processor
    DMI_PROCESSOR_TYPE_VIDEO   = 0x06, ///< Video processor
};

enum dmi_processor_family
{
    DMI_PROCERROR_FAMILY_OTHER                 = 0x01,
    DMI_PROCESSOR_FAMILY_UNKNOWN               = 0x02,
    DMI_PROCESSOR_FAMILY_INTEL_8086            = 0x03,
    DMI_PROCESSOR_FAMILY_INTEL_80286           = 0x04,
    DMI_PROCESSOR_FAMILY_INTEL_80386           = 0x05,
    DMI_PROCESSOR_FAMILY_INTEL_80486           = 0x06,
    DMI_PROCESSOR_FAMILY_INTEL_8087            = 0x07,
    DMI_PROCESSOR_FAMILY_INTEL_80287           = 0x08,
    DMI_PROCESSOR_FAMILY_INTEL_80387           = 0x09,
    DMI_PROCESSOR_FAMILY_INTEL_80487           = 0x0A,
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM         = 0x0B,
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_PRO     = 0x0C,
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_II      = 0x0D,
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_MMX     = 0x0E,
    DMI_PROCESSOR_FAMILY_INTEL_CELERON         = 0x0F,
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_II_XEON = 0x10,
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_III     = 0x11,
    DMI_PROCESSOR_FAMILY_APPLE_M1              = 0x12,
    DMI_PROCESSOR_FAMILY_APPLE_M2              = 0x13,
    DMI_PROCESSOR_FAMILY_INTEL_CELERON_M       = 0x14,
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_4_HT    = 0x15,
    DMI_PROCESSOR_FAMILY_INTEL                 = 0x16,
    // Unassigned: 0x17
    DMI_PROCESSOR_FAMILY_AMD_DURON             = 0x18,
    DMI_PROCESSOR_FAMILY_AMD_K5                = 0x19,
    DMI_PROCESSOR_FAMILY_AMD_K6                = 0x1A,
    DMI_PROCESSOR_FAMILY_AMD_K6_2              = 0x1B,
    DMI_PROCESSOR_FAMILY_AMD_K6_3              = 0x1C,
    DMI_PROCESSOR_FAMILY_AMD_ATHLON            = 0x1D,
    DMI_PROCESSOR_FAMILY_AMD_29000             = 0x1E,
    DMI_PROCESSOR_FAMILY_AMD_K6_2_PLUS         = 0x1F,
    DMI_PROCESSOR_FAMILY_POWERPC               = 0x20,
    DMI_PROCESSOR_FAMILY_POWERPC_601           = 0x21,
    DMI_PROCESSOR_FAMILY_POWERPC_603           = 0x22,
    DMI_PROCESSOR_FAMILY_POWERPC_603_PLUS      = 0x23,
    DMI_PROCESSOR_FAMILY_POWERPC_604           = 0x24,
    DMI_PROCESSOR_FAMILY_POWERPC_620           = 0x25,
    DMI_PROCESSOR_FAMILY_POWERPC_X704          = 0x26,
    DMI_PROCESSOR_FAMILY_POWERPC_750           = 0x27,
    DMI_PROCESSOR_FAMILY_INTEL_CORE_DUO        = 0x28,
    DMI_PROCESSOR_FAMILY_INTEL_CORE_DUO_M      = 0x29,
    DMI_PROCESSOR_FAMILY_INTEL_CORE_SOLO_M     = 0x2A,
    DMI_PROCESSOR_FAMILY_INTEL_ATOM            = 0x2B,
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M          = 0x2C,
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M3         = 0x2D,
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M5         = 0x2E,
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M7         = 0x2F,
    DMI_PROCESSOR_FAMILY_ALPHA                 = 0x30,
    DMI_PROCESSOR_FAMILY_ALPHA_21064           = 0x31,
    DMI_PROCESSOR_FAMILY_ALPHA_21066           = 0x32,
};

enum dmi_processor_upgrade
{
    DMI_PROCESSOR_UPGRADE_OTHER            = 0x01, ///< Other
    DMI_PROCESSOR_UPGRADE_UNKNOWN          = 0x02, ///< Unknown
    DMI_PROCESSOR_UPGRADE_DAUGHTER_BOARD   = 0x03, ///< Daughter board
    DMI_PROCESSOR_UPGRADE_SOCKET_ZIF       = 0x04, ///< ZIF socket
    DMI_PROCESSOR_UPGRADE_PIGGY_BACK       = 0x05, ///< Replaceable piggy-back
    DMI_PROCESSOR_UPGRADE_NONE             = 0x06, ///< None
    DMI_PROCESSOR_UPGRADE_SOCKET_LIF       = 0x07, ///< LIF socket
    DMI_PROCESSOR_UPGRADE_SLOT_1           = 0x08, ///< Slot 1
    DMI_PROCESSOR_UPGRADE_SLOT_2           = 0x09, ///< Slot 2
    DMI_PROCESSOR_UPGRADE_SOCKET_370PIN    = 0x0A, ///< 370-pin socket
    DMI_PROCESSOR_UPGRADE_SLOT_A           = 0x0B, ///< Slot A
    DMI_PROCESSOR_UPGRADE_SLOT_M           = 0x0C, ///< Slot M
    DMI_PROCESSOR_UPGRADE_SOCKET_423       = 0x0D, ///< Socket 423
    DMI_PROCESSOR_UPGRADE_SOCKET_A         = 0x0E, ///< Socket A (462)
    DMI_PROCESSOR_UPGRADE_SOCKET_478       = 0x0F, ///< Socket 478
    DMI_PROCESSOR_UPGRADE_SOCKET_754       = 0x10, ///< Socket 754
    DMI_PROCESSOR_UPGRADE_SOCKET_940       = 0x11, ///< Socket 940
    DMI_PROCESSOR_UPGRADE_SOCKET_939       = 0x12, ///< Socket 939
    DMI_PROCESSOR_UPGRADE_SOCKET_MPGA604   = 0x13, ///< Socket mPGA604
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA771    = 0x14, ///< Socket LGA771
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA775    = 0x15, ///< Socket LGA775
    DMI_PROCESSOR_UPGRADE_SOCKET_S1        = 0x16, ///< Socket S1
    DMI_PROCESSOR_UPGRADE_SOCKET_AM2       = 0x17, ///< Socket AM2
    DMI_PROCESSOR_UPGRADE_SOCKET_F         = 0x18, ///< Socket F (1207)
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1366   = 0x19, ///< Socket LGA1366
    DMI_PROCESSOR_UPGRADE_SOCKET_G34       = 0x1A, ///< Socket G34
    DMI_PROCESSOR_UPGRADE_SOCKET_AM3       = 0x1B, ///< Socket AM3
    DMI_PROCESSOR_UPGRADE_SOCKET_C32       = 0x1C, ///< Socket C32
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1156   = 0x1D, ///< Socket LGA1156
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1567   = 0x1E, ///< Socket LGA1567
    DMI_PROCESSOR_UPGRADE_SOCKET_PGA988A   = 0x1F, ///< Socket PGA988A
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1288   = 0x20, ///< Socket BGA1288
    DMI_PROCESSOR_UPGRADE_SOCKET_RPGA988B  = 0x21, ///< Socket rPGA988B
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1023   = 0x22, ///< Socket BGA1023
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1224   = 0x23, ///< Socket BGA1224
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1155   = 0x24, ///< Socket LGA1155
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1356   = 0x25, ///< Socket LGA1356
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA2011   = 0x26, ///< Socket LGA2011
    DMI_PROCESSOR_UPGRADE_SOCKET_FS1       = 0x27, ///< Socket FS1
    DMI_PROCESSOR_UPGRADE_SOCKET_FS2       = 0x28, ///< Socket FS2
    DMI_PROCESSOR_UPGRADE_SOCKET_FM1       = 0x29, ///< Socket FM1
    DMI_PROCESSOR_UPGRADE_SOCKET_FM2       = 0x2A, ///< Socket FM2
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA2011_3 = 0x2B, ///< Socket LGA2011-3
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1356_3 = 0x2C, ///< Socket LGA1356-3
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1150   = 0x2D, ///< Socket LGA1150
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1168   = 0x2E, ///< Socket BGA1168
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1234   = 0x2F, ///< Socket BGA1234
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1364   = 0x30, ///< Socket BGA1364
    DMI_PROCESSOR_UPGRADE_SOCKET_AM4       = 0x31, ///< Socket AM4
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1151   = 0x32, ///< Socket LGA1151
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1356   = 0x33, ///< Socket BGA1356
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1440   = 0x34, ///< Socket BGA1440
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1515   = 0x35, ///< Socket BGA1515
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA3647_1 = 0x36, ///< Socket LGA3647-1
    DMI_PROCESSOR_UPGRADE_SOCKET_SP3       = 0x37, ///< Socket SP3
    DMI_PROCESSOR_UPGRADE_SOCKET_SP3R2     = 0x38, ///< Socket SP3r2
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA2066   = 0x39, ///< Socket LGA2066
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1392   = 0x3A, ///< Socket BGA1392
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1510   = 0x3B, ///< Socket BGA1510
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1528   = 0x3C, ///< Socket BGA1528
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA4189   = 0x3D, ///< Socket LGA4189
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1200   = 0x3E, ///< Socket LGA1200
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA4677   = 0x3F, ///< Socket LGA4677
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1700   = 0x40, ///< Socket LGA1700
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1744   = 0x41, ///< Socket BGA1744
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1781   = 0x42, ///< Socket BGA1781
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1211   = 0x43, ///< Socket BGA1211
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA2422   = 0x44, ///< Socket BGA2422
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1211   = 0x45, ///< Socket LGA1211
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA2422   = 0x46, ///< Socket LGA2422
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA5773   = 0x47, ///< Socket LGA5773
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA5773   = 0x48, ///< Socket BGA5773
    DMI_PROCESSOR_UPGRADE_SOCKET_AM5       = 0x49, ///< Socket AM5
    DMI_PROCESSOR_UPGRADE_SOCKET_SP5       = 0x4A, ///< Socket SP5
    DMI_PROCESSOR_UPGRADE_SOCKET_SP6       = 0x4B, ///< Socket SP6
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA883    = 0x4C, ///< Socket BGA883
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1190   = 0x4D, ///< Socket BGA1190
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA4129   = 0x4E, ///< Socket BGA4129
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA4710   = 0x4F, ///< Socket LGA4710
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA7529   = 0x50, ///< Socket LGA7529
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1964   = 0x51, ///< Socket BGA1964
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA1792   = 0x52, ///< Socket BGA1792
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA2049   = 0x53, ///< Socket BGA2049
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA2551   = 0x54, ///< Socket BGA2551
    DMI_PROCESSOR_UPGRADE_SOCKET_LGA1851   = 0x55, ///< Socket LGA1851
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA2114   = 0x56, ///< Socket BGA2114
    DMI_PROCESSOR_UPGRADE_SOCKET_BGA2833   = 0x57, ///< Socket BGA2833
};

DMI_PACKED_STRUCT(dmi_processor_data)
{
    enum dmi_processor_type type;

    enum dmi_processor_family family;

    dmi_string_t manufacturer;

    dmi_qword_t raw_id;

    dmi_string_t version;

    dmi_byte_t voltage;

    dmi_word_t external_clock;

    dmi_word_t maximum_speed;

    dmi_word_t current_speed;

    dmi_byte_t status;

    enum dmi_processor_upgrade upgrade;

    /**
     * @brief L1 cache handle.
     *
     * Handle of a Cache Information structure that defines the attributes of
     * the primary (Level 1) cache for this processor.
     *
     * @note
     * For version 2.1 and version 2.2 implementations, the value is 0xFFFF if
     * the processor has no L1 cache. For version 2.3 and later implementations,
     * the value is 0xFFFF if the Cache Information structure is not provided.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t l1_cache_handle;

    /**
     * @brief L2 cache handle.
     *
     * Handle of a Cache Information structure that defines the attributes of
     * the secondary (Level 2) cache for this processor.
     *
     * @note
     * For version 2.1 and version 2.2 implementations, the value is 0xFFFF if
     * the processor has no L2 cache. For version 2.3 and later implementations,
     * the value is 0xFFFF if the Cache Information structure is not provided.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t l2_cache_handle;

    /**
     * @brief L3 cache handle.
     * 
     * Handle of a Cache Information structure that defines the attributes of
     * the tertiary (Level 3) cache for this processor.
     *
     * @note
     * For version 2.1 and version 2.2 implementations, the value is 0xFFFF if
     * the processor has no L3 cache. For version 2.3 and later implementations,
     * the value is 0xFFFF if the cache information structure is not provided.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t l3_cache_handle;

    /**
     * @brief Serial number.
     *
     * String number for the serial number of this processorю This value is set
     * by the manufacturer and normally not changeable.
     *
     * @since SMBIOS 2.3
     */
    dmi_string_t serial_number;

    /**
     * @since SMBIOS 2.3
     */
    dmi_string_t asset_tag;

    /**
     * @since SMBIOS 2.3
     */
    dmi_string_t part_number;

    /**
     * @since SMBIOS 2.5
     */
    dmi_byte_t core_count;

    /**
     * @since SMBIOS 2.5
     */
    dmi_byte_t core_enabled;

    /**
     * @since SMBIOS 2.5
     */
    dmi_byte_t thread_count;

    /**
     * @since SMBIOS 2.5
     */
    dmi_word_t features;

    dmi_word_t family_ex;

    dmi_word_t core_count_ex;

    dmi_word_t core_enabled_ex;

    dmi_word_t thread_count_ex;

    dmi_word_t thread_enabled;

    dmi_byte_t socket_type;
};

/**
 * @brief Processor information table specification.
 */
extern const struct dmi_table_spec dmi_processor_table;

/**
 * @brief Processor additional information table specification.
 */
extern const struct dmi_table_spec dmi_processor_ex_table;

__BEGIN_DECLS

const char *dmi_processor_type_name(enum dmi_processor_type value);
const char *dmi_processor_family_name(enum dmi_processor_family value);
const char *dmi_processor_upgrade_name(enum dmi_processor_upgrade value);

__END_DECLS

#endif // !OPENDMI_TABLE_PROCESSOR_H
