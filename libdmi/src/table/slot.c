//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/slot.h>
#include <opendmi/utils.h>

static const char *dmi_slot_type_names[__DMI_SLOT_TYPE_COUNT] =
{
    [DMI_SLOT_TYPE_OTHER]                 = "Other",
    [DMI_SLOT_TYPE_UNKNOWN]               = "Unknown",
    [DMI_SLOT_TYPE_ISA]                   = "ISA",
    [DMI_SLOT_TYPE_MCA]                   = "MCA",
    [DMI_SLOT_TYPE_EISA]                  = "EISA",
    [DMI_SLOT_TYPE_PCI]                   = "PCI",
    [DMI_SLOT_TYPE_PCMCIA]                = "PC card (PCMCIA)",
    [DMI_SLOT_TYPE_VESA]                  = "VL-VESA",
    [DMI_SLOT_TYPE_PROPRIETARY]           = "Proprietary",
    [DMI_SLOT_TYPE_PROCESSOR_CARD]        = "Processor card slot",
    [DMI_SLOT_TYPE_MEMORY_CARD]           = "Memory card slot",
    [DMI_SLOT_TYPE_IO_RISER_CARD]         = "I/O riser card slot",
    [DMI_SLOT_TYPE_NUBUS]                 = "NuBus",
    [DMI_SLOT_TYPE_PCI_66]                = "PCI 66 Mhz",
    [DMI_SLOT_TYPE_AGP]                   = "AGP",
    [DMI_SLOT_TYPE_AGP_2X]                = "AGP 2x",
    [DMI_SLOT_TYPE_AGP_4X]                = "AGP 4x",
    [DMI_SLOT_TYPE_PCI_X]                 = "PCI-X",
    [DMI_SLOT_TYPE_AGP_8X]                = "AGP 8x",
    [DMI_SLOT_TYPE_M2_S1_DP]              = "M.2 Socket 1-DP (Mechanical key A)",
    [DMI_SLOT_TYPE_M2_S1_SD]              = "M.2 Socket 1-SD (Mechanical key E)",
    [DMI_SLOT_TYPE_M2_S2]                 = "M.2 Socket 2 (Mechanical key B)",
    [DMI_SLOT_TYPE_M2_S3]                 = "M.2 Socket 3 (Mechanical key M)",
    [DMI_SLOT_TYPE_MXM_I]                 = "MXM Type I",
    [DMI_SLOT_TYPE_MXM_II]                = "MXM Type II",
    [DMI_SLOT_TYPE_MXM_III_STD]           = "MXM Type III (Standard connector)",
    [DMI_SLOT_TYPE_MXM_III_HE]            = "MXM Type III (HE connector)",
    [DMI_SLOT_TYPE_MXM_IV]                = "MXM Type IV",
    [DMI_SLOT_TYPE_MXM_30_A]              = "MXM 3.0 Type A",
    [DMI_SLOT_TYPE_MXM_30_B]              = "MXM 3.0 Type B",
    [DMI_SLOT_TYPE_PCI_E_G2_SFF8639]      = "PCI Express Gen 2 SFF-8639 (U.2)",
    [DMI_SLOT_TYPE_PCI_E_G3_SFF8639]      = "PCI Express Gen 3 SFF-8639 (U.2)",
    [DMI_SLOT_TYPE_PCI_E_MINI_52PIN_BSKO] = "PCI Express Mini 52-pin (CEM spec. 2.0) with bottom-side keep-outs",
    [DMI_SLOT_TYPE_PCI_E_MINI_52PIN]      = "PCI Express Mini 52-pin (CEM spec. 2.0) without bottom-side keep-outs",
    [DMI_SLOT_TYPE_PCI_E_MINI_76PIN]      = "PCI Express Mini 76-pin (CEM spec. 2.0)",
    [DMI_SLOT_TYPE_PCI_E_G4_SFF8639]      = "PCI Express Gen 4 SFF-8639 (U.2)",
    [DMI_SLOT_TYPE_PCI_E_G5_SFF8639]      = "PCI Express Gen 5 SFF-8639 (U.2)",
    [DMI_SLOT_TYPE_OCP_NIC_30_SFF]        = "OCP NIC 3.0 Small Form Factor (SFF)",
    [DMI_SLOT_TYPE_OCP_NIC_30_LFF]        = "OCP NIC 3.0 Large Form Factor (LFF)",
    [DMI_SLOT_TYPP_OCP_NIC_LEGACY]        = "OCP NIC prior to 3.0",
    [DMI_SLOT_TYPE_CXL_FLEXBUS_10]        = "CXL FlexBus 1.0",
    [DMI_SLOT_TYPE_PC_98_C20]             = "PC-98/C20",
    [DMI_SLOT_TYPE_PC_98_C24]             = "PC-98/C24",
    [DMI_SLOT_TYPE_PC_98_E]               = "PC-98/E",
    [DMI_SLOT_TYPE_PC_98_LOCAL_BUS]       = "PC-98/Local bus",
    [DMI_SLOT_TYPE_PC_98_CARD]            = "PC-98/Card",
    [DMI_SLOT_TYPE_PCI_E]                 = "PCI Express",
    [DMI_SLOT_TYPE_PCI_E_X1]              = "PCI Express x1",
    [DMI_SLOT_TYPE_PCI_E_X2]              = "PCI Express x2",
    [DMI_SLOT_TYPE_PCI_E_X4]              = "PCI Express x4",
    [DMI_SLOT_TYPE_PCI_E_X8]              = "PCI Express x8",
    [DMI_SLOT_TYPE_PCI_E_X16]             = "PCI Express x16",
    [DMI_SLOT_TYPE_PCI_E_G2]              = "PCI Express Gen 2",
    [DMI_SLOT_TYPE_PCI_E_G2_X1]           = "PCI Express Gen 2 x1",
    [DMI_SLOT_TYPE_PCI_E_G2_X2]           = "PCI Express Gen 2 x2",
    [DMI_SLOT_TYPE_PCI_E_G2_X4]           = "PCI Express Gen 2 x4",
    [DMI_SLOT_TYPE_PCI_E_G2_X8]           = "PCI Express Gen 2 x8",
    [DMI_SLOT_TYPE_PCI_E_G2_X16]          = "PCI Express Gen 2 x16",
    [DMI_SLOT_TYPE_PCI_E_G3]              = "PCI Express Gen 3",
    [DMI_SLOT_TYPE_PCI_E_G3_X1]           = "PCI Express Gen 3 x1",
    [DMI_SLOT_TYPE_PCI_E_G3_X2]           = "PCI Express Gen 3 x2",
    [DMI_SLOT_TYPE_PCI_E_G3_X4]           = "PCI Express Gen 3 x4",
    [DMI_SLOT_TYPE_PCI_E_G3_X8]           = "PCI Express Gen 3 x8",
    [DMI_SLOT_TYPE_PCI_E_G3_X16]          = "PCI Express Gen 3 x16",
    [DMI_SLOT_TYPE_PCI_E_G4]              = "PCI Express Gen 4",
    [DMI_SLOT_TYPE_PCI_E_G4_X1]           = "PCI Express Gen 4 x1",
    [DMI_SLOT_TYPE_PCI_E_G4_X2]           = "PCI Express Gen 4 x2",
    [DMI_SLOT_TYPE_PCI_E_G4_X4]           = "PCI Express Gen 4 x4",
    [DMI_SLOT_TYPE_PCI_E_G4_X8]           = "PCI Express Gen 4 x8",
    [DMI_SLOT_TYPE_PCI_E_G4_X16]          = "PCI Express Gen 4 x16",
    [DMI_SLOT_TYPE_PCI_E_G5]              = "PCI Express Gen 5",
    [DMI_SLOT_TYPE_PCI_E_G5_X1]           = "PCI Express Gen 5 x1",
    [DMI_SLOT_TYPE_PCI_E_G5_X2]           = "PCI Express Gen 5 x2",
    [DMI_SLOT_TYPE_PCI_E_G5_X4]           = "PCI Express Gen 5 x4",
    [DMI_SLOT_TYPE_PCI_E_G5_X8]           = "PCI Express Gen 5 x8",
    [DMI_SLOT_TYPE_PCI_E_G5_X16]          = "PCI Express Gen 5 x16",
    [DMI_SLOT_TYPE_PCI_E_G6]              = "PCI Express Gen 6 and beyond",
    [DMI_SLOT_TYPE_EDSFF_E1]              = "Enterprise and datacenter 1U E1 form factor slot (EDSFF E1.S, E1.L)",
    [DMI_SLOT_TYPE_EDSFF_E3]              = "Enterprise and datacenter 3\" E3 form factor slot (EDSFF E3.S, E3.L)"
};

static const char *dmi_slot_width_names[__DMI_SLOT_WIDTH_COUNT] =
{
    [DMI_SLOT_WIDTH_OTHER]   = "Other",
    [DMI_SLOT_WIDTH_UNKNOWN] = "Unknown",
    [DMI_SLOT_WIDTH_8_BIT]   = "8 bit",
    [DMI_SLOT_WIDTH_16_BIT]  = "16 bit",
    [DMI_SLOT_WIDTH_32_BIT]  = "32 bit",
    [DMI_SLOT_WIDTH_64_BIT]  = "64 bit",
    [DMI_SLOT_WIDTH_128_BIT] = "128 bit",
    [DMI_SLOT_WIDTH_1X]      = "1x or x1",
    [DMI_SLOT_WIDTH_2X]      = "2x or x2",
    [DMI_SLOT_WIDTH_4X]      = "4x or x4",
    [DMI_SLOT_WIDTH_8X]      = "8x or x8",
    [DMI_SLOT_WIDTH_12X]     = "12x or x12",
    [DMI_SLOT_WIDTH_16X]     = "16x or x16",
    [DMI_SLOT_WIDTH_32X]     = "32x or x32"
};

static const char *dmi_slot_usage_names[__DMI_SLOT_USAGE_COUNT] =
{
    [DMI_SLOT_USAGE_OTHER]       = "Other",
    [DMI_SLOT_USAGE_UNKNOWN]     = "Unknown",
    [DMI_SLOT_USAGE_AVAILABLE]   = "Available",
    [DMI_SLOT_USAGE_IN_USE]      = "In use",
    [DMI_SLOT_USAGE_UNAVAILABLE] = "Unavailable"
};

const struct dmi_attribute_spec dmi_slot_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_slot_table_spec =
{
    .tag        = "slot",
    .name       = "System slots",
    .type       = DMI_TYPE_SYSTEM_SLOTS,
    .min_length = 0x0C,
    .attributes = dmi_slot_attrs
};

const char *dmi_slot_type_name(enum dmi_slot_type value)
{
    return dmi_name(dmi_slot_type_names, value, __DMI_SLOT_TYPE_COUNT);
}

const char *dmi_slot_width_name(enum dmi_slot_width value)
{
    return dmi_name(dmi_slot_width_names, value, __DMI_SLOT_WIDTH_COUNT);
}

const char *dmi_slot_usage_name(enum dmi_slot_usage value)
{
    return dmi_name(dmi_slot_usage_names, value, __DMI_SLOT_USAGE_COUNT);
}
