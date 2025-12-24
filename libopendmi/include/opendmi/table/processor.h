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

#ifndef DMI_PROCESSOR_DATA_T
#define DMI_PROCESSOR_DATA_T
typedef struct dmi_processor_data dmi_processor_data_t;
#endif // !DMI_PROCESSOR_DATA_T

#ifndef DMI_PROCESSOR_T
#define DMI_PROCESSOR_T
typedef struct dmi_processor dmi_processor_t;
#endif // !DMI_PROCESSOR_T

enum dmi_processor_type
{
    DMI_PROCESSOR_TYPE_UNSPEC  = 0x00, ///< Unspecified
    DMI_PROCESSOR_TYPE_OTHER   = 0x01, ///< Other
    DMI_PROCESSOR_TYPE_UNKNOWN = 0x02, ///< Unknown
    DMI_PROCESSOR_TYPE_CENTRAL = 0x03, ///< Central processor
    DMI_PROCESSOR_TYPE_MATH    = 0x04, ///< Math processor
    DMI_PROCESSOR_TYPE_DSP     = 0x05, ///< DSP processor
    DMI_PROCESSOR_TYPE_VIDEO   = 0x06, ///< Video processor
    __DMI_PROCESSOR_TYPE_COUNT
};

enum dmi_processor_family
{
    DMI_PROCERROR_FAMILY_OTHER                    = 0x01, ///< Other
    DMI_PROCESSOR_FAMILY_UNKNOWN                  = 0x02, ///< Unknown
    DMI_PROCESSOR_FAMILY_INTEL_8086               = 0x03, ///< Intel 8086
    DMI_PROCESSOR_FAMILY_INTEL_80286              = 0x04, ///< Intel 80286
    DMI_PROCESSOR_FAMILY_INTEL_80386              = 0x05, ///< Intel 80386
    DMI_PROCESSOR_FAMILY_INTEL_80486              = 0x06, ///< Intel 80486
    DMI_PROCESSOR_FAMILY_INTEL_8087               = 0x07, ///< Intel 8087
    DMI_PROCESSOR_FAMILY_INTEL_80287              = 0x08, ///< Intel 80287
    DMI_PROCESSOR_FAMILY_INTEL_80387              = 0x09, ///< Intel 80387
    DMI_PROCESSOR_FAMILY_INTEL_80487              = 0x0A, ///< Intel 80487
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM            = 0x0B, ///< Intel Pentium
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_PRO        = 0x0C, ///< Intel Pentium Pro
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_II         = 0x0D, ///< Intel Pentium II
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_MMX        = 0x0E, ///< Intel Pentium MMX
    DMI_PROCESSOR_FAMILY_INTEL_CELERON            = 0x0F, ///< Intel Celeron
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_II_XEON    = 0x10, ///< Intel Pentium II Xeon
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_III        = 0x11, ///< Intel Pentium III
    DMI_PROCESSOR_FAMILY_APPLE_M1                 = 0x12, ///< Apple M1
    DMI_PROCESSOR_FAMILY_APPLE_M2                 = 0x13, ///< Apple M2
    DMI_PROCESSOR_FAMILY_INTEL_CELERON_M          = 0x14, ///< Intel Celeron M
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_4_HT       = 0x15, ///< Intel Pentium 4 HT
    DMI_PROCESSOR_FAMILY_INTEL                    = 0x16, ///< Intel
    // Unassigned: 0x17
    DMI_PROCESSOR_FAMILY_AMD_DURON                = 0x18, ///< AMD Duron
    DMI_PROCESSOR_FAMILY_AMD_K5                   = 0x19, ///< AMD K5
    DMI_PROCESSOR_FAMILY_AMD_K6                   = 0x1A, ///< AMD K6
    DMI_PROCESSOR_FAMILY_AMD_K6_2                 = 0x1B, ///< AMD K6-2
    DMI_PROCESSOR_FAMILY_AMD_K6_3                 = 0x1C, ///< AMD K6-3
    DMI_PROCESSOR_FAMILY_AMD_ATHLON               = 0x1D, ///< AMD Athlon
    DMI_PROCESSOR_FAMILY_AMD_29000                = 0x1E, ///< AMD 29000
    DMI_PROCESSOR_FAMILY_AMD_K6_2_PLUS            = 0x1F, ///< AMD K6-2+
    DMI_PROCESSOR_FAMILY_POWERPC                  = 0x20, ///< PowerPC
    DMI_PROCESSOR_FAMILY_POWERPC_601              = 0x21, ///< PowerPC 601
    DMI_PROCESSOR_FAMILY_POWERPC_603              = 0x22, ///< PowerPC 603
    DMI_PROCESSOR_FAMILY_POWERPC_603_PLUS         = 0x23, ///< PowerPC 603+
    DMI_PROCESSOR_FAMILY_POWERPC_604              = 0x24, ///< PowerPC 604
    DMI_PROCESSOR_FAMILY_POWERPC_620              = 0x25, ///< PowerPC 620
    DMI_PROCESSOR_FAMILY_POWERPC_X704             = 0x26, ///< PowerPC x704
    DMI_PROCESSOR_FAMILY_POWERPC_750              = 0x27, ///< PowerPC 750
    DMI_PROCESSOR_FAMILY_INTEL_CORE_DUO           = 0x28, ///< Intel Core Duo
    DMI_PROCESSOR_FAMILY_INTEL_CORE_DUO_M         = 0x29, ///< Intel Core Duo M
    DMI_PROCESSOR_FAMILY_INTEL_CORE_SOLO_M        = 0x2A, ///< Intel Core Solo M
    DMI_PROCESSOR_FAMILY_INTEL_ATOM               = 0x2B, ///< Intel Atom
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M             = 0x2C, ///< Intel Core M
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M3            = 0x2D, ///< Intel Core m3
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M5            = 0x2E, ///< Intel Core m5
    DMI_PROCESSOR_FAMILY_INTEL_CORE_M7            = 0x2F, ///< Intel Core m7
    DMI_PROCESSOR_FAMILY_ALPHA                    = 0x30, ///< Alpha
    DMI_PROCESSOR_FAMILY_ALPHA_21064              = 0x31, ///< Alpha 21064
    DMI_PROCESSOR_FAMILY_ALPHA_21066              = 0x32, ///< Alpha 21066
    DMI_PROCESSOR_FAMILY_ALPHA_21164              = 0x33, ///< Alpha 21164
    DMI_PROCESSOR_FAMILY_ALPHA_21164_PC           = 0x34, ///< Alpha 21164PC
    DMI_PROCESSOR_FAMILY_ALPHA_21164_A            = 0x35, ///< Alpha 21164a
    DMI_PROCESSOR_FAMILY_ALPHA_21264              = 0x36, ///< Alpha 21264
    DMI_PROCESSOR_FAMILY_ALPHA_21364              = 0x37, ///< Alpha 21364
    DMI_PROCESSOR_FAMILY_AMD_TURION_II_ULTRA_2C_M = 0x38, ///< AMD Turion II Ultra Dual-Core M
    DMI_PROCESSOR_FAMILY_AMD_TURION_II_2C_M       = 0x39, ///< AMD Turion II Dual-Core M
    DMI_PROCESSOR_FAMILY_AMD_ATHLON_II_2C_M       = 0x3A, ///< AMD Athlon II Dual-Core M
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_6100         = 0x3B, ///< AMD Opteron 6100 series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_4100         = 0x3C, ///< AMD Opteron 4100 series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_6200         = 0x3D, ///< AMD Opteron 6200 series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_4200         = 0x3E, ///< AMD Opteron 4200 series
    DMI_PROCESSOR_FAMILY_AMD_FX                   = 0x3F, ///< AMD FX series
    DMI_PROCESSOR_FAMILY_MIPS                     = 0x40, ///< MIPS
    DMI_PROCESSOR_FAMILY_MIPS_R4000               = 0x41, ///< MIPS R4000
    DMI_PROCESSOR_FAMILY_MIPS_R4200               = 0x42, ///< MIPS R4200
    DMI_PROCESSOR_FAMILY_MIPS_R4400               = 0x43, ///< MIPS R4400
    DMI_PROCESSOR_FAMILY_MIPS_R4600               = 0x44, ///< MIPS R4600
    DMI_PROCESSOR_FAMILY_MIPS_R10000              = 0x45, ///< MIPS R10000
    DMI_PROCESSOR_FAMILY_AMD_C                    = 0x46, ///< AMD C-series
    DMI_PROCESSOR_FAMILY_AMD_E                    = 0x47, ///< AMD E-series
    DMI_PROCESSOR_FAMILY_AMD_A                    = 0x48, ///< AMD A-series
    DMI_PROCESSOR_FAMILY_AMD_G                    = 0x49, ///< AMD G-series
    DMI_PROCESSOR_FAMILY_AMD_Z                    = 0x4A, ///< AMD Z-series
    DMI_PROCESSOR_FAMILY_AMD_R                    = 0x4B, ///< AMD R-series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_4300         = 0x4C, ///< AMD Opteron 4300 series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_6300         = 0x4D, ///< AMD Opteron 6300 series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_3300         = 0x4E, ///< AMD Opteron 3300 series
    DMI_PROCESSOR_FAMILY_AMD_FIREPRO              = 0x4F, ///< AMD FirePro series
    DMI_PROCESSOR_FAMILY_SPARC                    = 0x50, ///< SPARC
    DMI_PROCESSOR_FAMILY_SUPERSPARC               = 0x51, ///< SuperSPARC
    DMI_PROCESSOR_FAMILY_MICROSPARC_II            = 0x52, ///< microSPARC II
    DMI_PROCESSOR_FAMILY_MICROSPARC_II_EP         = 0x53, ///< microSPARC IIep
    DMI_PROCESSOR_FAMILY_ULTRASPARC               = 0x54, ///< UltraSPARC
    DMI_PROCESSOR_FAMILY_ULTRASPARC_II            = 0x55, ///< UltraSPARC II
    DMI_PROCESSOR_FAMILY_ULTRASPARC_II_I          = 0x56, ///< UltraSPARC IIi
    DMI_PROCESSOR_FAMILY_ULTRASPARC_III           = 0x57, ///< UltraSPARC III
    DMI_PROCESSOR_FAMILY_ULTRASPARC_III_I         = 0x58, ///< UltraSPARC_IIIi
    // Unassigned: 0x59 .. 0x5F
    DMI_PROCESSOR_FAMILY_MOTOROLA_68040           = 0x60, ///< Motorola 68040
    DMI_PROCESSOR_FAMILY_MOTOROLA_68XXX           = 0x61, ///< Motorola 68xxx
    DMI_PROCESSOR_FAMILY_MOTOROLA_68000           = 0x62, ///< Motorola 68000
    DMI_PROCESSOR_FAMILY_MOTOROLA_68010           = 0x63, ///< Motorola 68010
    DMI_PROCESSOR_FAMILY_MOTOROLA_68020           = 0x64, ///< Motorola 68020
    DMI_PROCESSOR_FAMILY_MOTOROLA_68030           = 0x65, ///< Motorola 68030
    DMI_PROCESSOR_FAMILY_AMD_ATHLON_X4_4C         = 0x66, ///< AMD Athlon X4 Quad-Core
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_X1000        = 0x67, ///< AMD Opteron X1000 series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_X2000        = 0x68, ///< AMD Opteron X2000 series APU
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_A            = 0x69, ///< AMD Opteron A-series
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_X3000        = 0x6A, ///< AMD Opteron X3000 series APU
    DMI_PROCESSOR_FAMILY_AMD_ZEN                  = 0x6B, ///< AMD Zen
    // Unassigned: 0x6C .. 0x6F
    DMI_PROCESSOR_FAMILY_HOBBIT                   = 0x70, ///< Hobbit
    // Unassigned: 0x71 .. 0x77
    DMI_PROCESSOR_FAMILY_CRUSOE_TM5000            = 0x78, ///< Crusoe TM5000
    DMI_PROCESSOR_FAMILY_CRUSOR_TM3000            = 0x79, ///< Crusoe TM3000
    DMI_PROCESSOR_FAMILY_EFFICEON_TM8000          = 0x7A, ///< Efficeon TM8000
    // Unassigned: 0x7B .. 0x7F
    DMI_PROCESSOR_FAMILY_WEITEK                   = 0x80, ///< Weitek
    // Unassigned: 0x81
    DMI_PROCESSOR_FAMILY_INTEL_ITANIUM            = 0x82, ///< Itanium
    DMI_PROCESSOR_FAMILY_AMD_ATHLON_64            = 0x83, ///< AMD Athlon 64
    DMI_PROCESSOR_FAMILY_AMD_OPTERON              = 0x84, ///< AMD Opteron
    DMI_PROCESSOR_FAMILY_AMD_SEMPRON              = 0x85, ///< AMD Sempron
    DMI_PROCESSOR_FAMILY_AMD_TURION_64_M          = 0x86, ///< AMD Turion 64 Mobile
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_2C           = 0x87, ///< Dual-Core AMD Opteron
    DMI_PROCESSOR_FAMILY_AMD_ATHLON_64_X2_2C      = 0x88, ///< AMD Athlon 64 X2 Dual-Core
    DMI_PROCESSOR_FAMILY_AMD_TURION_64_X2_M       = 0x89, ///< AMD Turion 64 X2 Mobile
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_4C           = 0x8A, ///< Quad-Core AMD Opteron
    DMI_PROCESSOR_FAMILY_AMD_OPTERON_G3           = 0x8B, ///< Third-Generation AMD Opteron
    DMI_PROCESSOR_FAMILY_AMD_PHENOM_FX_4C         = 0x8C, ///< AMD Phenom FX Quad-Core
    DMI_PROCESSOR_FAMILY_AMD_PHENOM_X4_4C         = 0x8D, ///< AMD Phenom X4 Quad-Core
    DMI_PROCESSOR_FAMILY_AMD_PHENOM_X2_2C         = 0x8E, ///< AMD Phenom X2 Dual-Core
    DMI_PROCESSOR_FAMILY_AMD_ATHLON_X2_2C         = 0x8F, ///< AMD Athlon X2 Dual-Core
    DMI_PROCESSOR_FAMILY_PARISC                   = 0x90, ///< PA-RISC
    DMI_PROCESSOR_FAMILY_PARISC_8500              = 0x91, ///< PA-RISC 8500
    DMI_PROCESSOR_FAMILY_PARISC_8000              = 0x92, ///< PA-RISC 8000
    DMI_PROCESSOR_FAMILY_PARISC_7300_LC           = 0x93, ///< PA-RISC 7300LC
    DMI_PROCESSOR_FAMILY_PARISC_7200              = 0x94, ///< PA-RISC 7200
    DMI_PROCESSOR_FAMILY_PARISC_7100_LC           = 0x95, ///< PA-RISC 7100LC
    DMI_PROCESSOR_FAMILY_PARISC_7100              = 0x96, ///< PA-RISC 7100
    // Unassigned: 0x97 .. 0x9F
    DMI_PROCESSOR_FAMILY_V30 = 0xA0, ///< V30
    DMI_PROCESSOR_FAMILY_INTEL_XEON_3200_4C       = 0xA1, ///< Quad-Core Intel Xeon 3200 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_3000_2C       = 0xA2, ///< Dual-Core Intel Xeon 3000 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_5300_4C       = 0xA3, ///< Quad-Core Intel Xeon 5300 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_5100_2C       = 0xA4, ///< Dual-Core Intel Xeon 5100 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_5000_2C       = 0xA5, ///< Dual-Core Intel Xeon 5000 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_LV_2C         = 0xA6, ///< Dual-Core Intel Xeon LV
    DMI_PROCESSOR_FAMILY_INTEL_XEON_ULV_2C        = 0xA7, ///< Dual-Core Intel Xeon ULV
    DMI_PROCESSOR_FAMILY_INTEL_XEON_7100_2C       = 0xA8, ///< Dual-Core Intel Xeon 7100 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_5400_4C       = 0xA9, ///< Quad-Core Intel Xeon 5400 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_4C            = 0xAA, ///< Quad-Core Intel Xeon
    DMI_PROCESSOR_FAMILY_INTEL_XEON_5200_2C       = 0xAB, ///< Dual-Core Intel Xeon 5200 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_7200_2C       = 0xAC, ///< Dual-Core Intel Xeon 7200 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_7300_4C       = 0xAD, ///< Quad-Core Intel Xeon 7300 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_7400_4C       = 0xAE, ///< Quad-Core Intel Xeon 7400 series
    DMI_PROCESSOR_FAMILY_INTEL_XEON_7400_MC       = 0xAF, ///< Multi-Core Intel Xeon 7400 series
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_III_XEON   = 0xB0, ///< Intel Pentium III Xeon
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_III_SS     = 0xB1, ///< Intel Pentium III with SpeedStep technology
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_4          = 0xB2, ///< Intel Pentium 4
    DMI_PROCESSOR_FAMILY_INTEL_XEON               = 0xB3, ///< Intel Xeon
    DMI_PROCESSOR_FAMILY_IBM_AS400                = 0xB4, ///< IBM AS400 Family
    DMI_PROCESSOR_FAMILY_INTEL_XEON_MP            = 0xB5, ///< Intel Xeon processor MP
    DMI_PROCESSOR_FAMILY_AMD_ATHLON_XP            = 0xB6, ///< AMD Athlon XP
    DMI_PROCESSOR_FAMILY_AMD_ATHLON_MP            = 0xB7, ///< AMD Athlon MP
    DMI_PROCESSOR_FAMILY_INTEL_ITANIUM_2          = 0xB8, ///< Intel Itanium 2
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_M          = 0xB9, ///< Intel Pentium M
    DMI_PROCESSOR_FAMILY_INTEL_CELERON_D          = 0xBA, ///< Intel Celeron D
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_D          = 0xBB, ///< Intel Pentium D
    DMI_PROCESSOR_FAMILY_INTEL_PENTIUM_EXTREME    = 0xBC, ///< Intel Pentium Extreme Edition
    DMI_PROCESSOR_FAMILY_INTEL_CORE_SOLO          = 0xBD, ///< Intel Core Solo
    DMI_PROCESSOR_FAMILY_RESERVED                 = 0xBE, ///< Reserved (AMD K7/Intel Core 2)
    DMI_PROCESSOR_FAMILY_INTEL_CORE_2_DUO         = 0xBF, ///< Intel Core 2 Duo
    DMI_PROCESSOR_FAMILY_INTEL_CORE_2_SOLO        = 0xC0, ///< Intel Core 2 Solo
    DMI_PROCESSOR_FAMILY_INTEL_CORE_2_EXTREME     = 0xC1, ///< Intel Core 2 Extreme
    DMI_PROCESSOR_FAMILY_INTEL_CORE_2_QUAD        = 0xC2, ///< Intel Core 2 Quad
    DMI_PROCESSOR_FAMILY_INTEL_CORE_2_EXTREME_M   = 0xC3, ///< Intel Core 2 Extreme mobile
    DMI_PROCESSOR_FAMILY_INTEL_CORE_2_DUO_M       = 0xC4, ///< Intel Core 2 Duo mobile
    DMI_PROCESSOR_FAMILY_INTEL_CORE_2_SOLO_M      = 0xC5, ///< Intel Core 2 Solo mobile
    DMI_PROCESSOR_FAMILY_INTEL_CORE_I7            = 0xC6, ///< Intel Core i7
    DMI_PROCESSOR_FAMILY_INTEL_CELERON_2C         = 0xC7, ///< Dual-Core Intel Celeron
    DMI_PROCESSOR_FAMILY_IBM_ESA390               = 0xC8, ///< IBM ESA/390
    DMI_PROCESSOR_FAMILY_POWERPC_G4               = 0xC9, ///< PowerPC G4
    DMI_PROCESSOR_FAMILY_POWERPC_G5               = 0xCA, ///< PowerPC G5
    DMI_PROCESSOR_FAMILY_IBM_ESA390_G6            = 0xCB, ///< IBM ESA/390 G6
    DMI_PROCESSOR_FAMILY_IBM_ZARCH                = 0xCC, ///< z/Architecture base
    DMI_PROCESSOR_FAMILY_INTEL_CORE_I5            = 0xCD, ///< Intel Core i5
    DMI_PROCESSOR_FAMILY_INTEL_CORE_I3            = 0xCE, ///< Intel Core i3
    DMI_PROCESSOR_FAMILY_INTEL_CORE_I9            = 0xCF, ///< Intel Core i9
    DMI_PROCESSOR_FAMILY_INTEL_XEON_D             = 0xD0, ///< Intel Xeon D
    // Unassigned: 0xD1
};

enum dmi_processor_upgrade
{
    DMI_PROCESSOR_UPGRADE_UNSPEC           = 0x00, ///< Unspecified
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

    dmi_string_t vendor;

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
