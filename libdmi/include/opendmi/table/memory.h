//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_H
#define OPENDMI_TABLE_MEMORY_H

#pragma once

#include <opendmi/table.h>

enum dmi_mem_array_location
{
    DMI_MEM_ARRAY_LOCATION_OTHER           = 0x01, ///< Other
    DMI_MEM_ARRAY_LOCATION_UNKNOWN         = 0x02, ///< Unknown
    DMI_MEM_ARRAY_LOCATION_MOTHERBOARD     = 0x03, ///< System board or motherboard
    DMI_MEM_ARRAY_LOCATION_ISA             = 0x04, ///< ISA add-on card
    DMI_MEM_ARRAY_LOCATION_EISA            = 0x05, ///< EISA add-on card
    DMI_MEM_ARRAY_LOCATION_PCI             = 0x06, ///< PCI add-on card
    DMI_MEM_ARRAY_LOCATION_MCA             = 0x07, ///< MCA add-on card
    DMI_MEM_ARRAY_LOCATION_PCMCIA          = 0x08, ///< PCMCIA add-on card
    DMI_MEM_ARRAY_LOCATION_PROPRIETARY     = 0x09, ///< Proprietary add-on card
    DMI_MEM_ARRAY_LOCATION_NUBUS           = 0x0A, ///< NuBus
    DMI_MEM_ARRAY_LOCATION_PC_98_C20       = 0xA0, ///< PC-98/C20 add-on card
    DMI_MEM_ARRAY_LOCATION_PC_98_C24       = 0xA1, ///< PC-98/C24 add-on card
    DMI_MEM_ARRAY_LOCATION_PC_98_E         = 0xA2, ///< PC-98/E add-on card
    DMI_MEM_ARRAY_LOCATION_PC_98_LOCAL_BUS = 0xA3, ///< PC-98/Local bus add-on card
    DMI_MEM_ARRAY_LOCATION_CXL             = 0xA4, ///< CXL add-on card
    __DMI_MEM_ARRAY_LOCATION_COUNT
};

enum dmi_mem_array_usage
{
    DMI_MEM_ARRAY_USAGE_OTHER   = 0x01, ///< Other
    DMI_MEM_ARRAY_USAGE_UNKNOWN = 0x02, ///< Unknown
    DMI_MEM_ARRAY_USAGE_SYSTEM  = 0x03, ///< System memory
    DMI_MEM_ARRAY_USAGE_VIDEO   = 0x04, ///< Video memory
    DMI_MEM_ARRAY_USAGE_FLASH   = 0x05, ///< Flash memory
    DMI_MEM_ARRAY_USAGE_NVRAM   = 0x06, ///< Non-volatile RAM
    DMI_MEM_ARRAY_USAGE_CACHE   = 0x07, ///< Cache memory
    __DMI_MEM_ARRAY_USAGE_COUNT
};

enum dmi_mem_device_type
{
    DMI_MEM_DEVICE_TYPE_OTHER             = 0x01,
    DMI_MEM_DEVICE_TYPE_UNKNOWN           = 0x02,
    DMI_MEM_DEVICE_TYPE_DRAM              = 0x03,
    DMI_MEM_DEVICE_TYPE_EDRAM             = 0x04,
    DMI_MEM_DEVICE_TYPE_VRAM              = 0x05,
    DMI_MEM_DEVICE_TYPE_SRAM              = 0x06,
    DMI_MEM_DEVICE_TYPE_RAM               = 0x07,
    DMI_MEM_DEVICE_TYPE_ROM               = 0x08,
    DMI_MEM_DEVICE_TYPE_FLASH             = 0x09,
    DMI_MEM_DEVICE_TYPE_EEPROM            = 0x0A,
    DMI_MEM_DEVICE_TYPE_FEPROM            = 0x0B,
    DMI_MEM_DEVICE_TYPE_EPROM             = 0x0C,
    DMI_MEM_DEVICE_TYPE_CDRAM             = 0x0D,
    DMI_MEM_DEVICE_TYPE_3DRAM             = 0x0E,
    DMI_MEM_DEVICE_TYPE_SDRAM             = 0x0F,
    DMI_MEM_DEVICE_TYPE_SGRAM             = 0x10,
    DMI_MEM_DEVICE_TYPE_RDRAM             = 0x11,
    DMI_MEM_DEVICE_TYPE_DDR               = 0x12,
    DMI_MEM_DEVICE_TYPE_DDR2              = 0x13,
    DMI_MEM_DEVICE_TYPE_DDR2_FBDIMM       = 0x14,
    // Unassigned: 0x15 .. 0x17
    DMI_MEM_DEVICE_TYPE_DDR3              = 0x18,
    DMI_MEM_DEVICE_TYPE_FBD2              = 0x19,
    DMI_MEM_DEVICE_TYPE_DDR4              = 0x1A,
    DMI_MEM_DEVICE_TYPE_LPDDR             = 0x1B,
    DMI_MEM_DEVICE_TYPE_LPDDR2            = 0x1C,
    DMI_MEM_DEVICE_TYPE_LPDDR3            = 0x1D,
    DMI_MEM_DEVICE_TYPE_LPDDR4            = 0x1E,
    DMI_MEM_DEVICE_TYPE_LOGICAL_NV_DEVICE = 0x1F,
    DMI_MEM_DEVICE_TYPE_HBM               = 0x20,
    DMI_MEM_DEVICE_TYPE_HBM2              = 0x21,
    DMI_MEM_DEVICE_TYPE_DDR5              = 0x22,
    DMI_MEM_DEVICE_TYPE_LPDDR5            = 0x23,
    DMI_MEM_DEVICE_TYPE_HBM3              = 0x24,
    DMI_MEM_DEVICE_TYPE_MRDIMM            = 0x25,
};

enum dmi_mem_device_form_factor
{
    DMI_MEM_DEVICE_FORM_FACTOR_OTHER   = 0x01, ///< Other
    DMI_MEM_DEVICE_FORM_FACTOR_UNKNOWN = 0x02, ///< Unknown
    DMI_MEM_DEVICE_FORM_FACTOR_SIMM    = 0x03, ///< SIMM
    DMI_MEM_DEVICE_FORM_FACTOR_SIP     = 0x04, ///< SIP
    DMI_MEM_DEVICE_FORM_FACTOR_CHIP    = 0x05, ///< Chip
    DMI_MEM_DEVICE_FORM_FACTOR_DIP     = 0x06, ///< DIP
    DMI_MEM_DEVICE_FORM_FACTOR_ZIP     = 0x07, ///< ZIP
    DMI_MEM_DEVICE_FORM_FACTOR_CARD    = 0x08, ///< Proprietary card
    DMI_MEM_DEVICE_FORM_FACTOR_DIMM    = 0x09, ///< DIMM
    DMI_MEM_DEVICE_FORM_FACTOR_TSOP    = 0x0A, ///< TSOP
    DMI_MEM_DEVICE_FORM_FACTOR_ROW     = 0x0B, ///< Row of chips
    DMI_MEM_DEVICE_FORM_FACTOR_RIMM    = 0x0C, ///< RIMM
    DMI_MEM_DEVICE_FORM_FACTOR_SODIMM  = 0x0D, ///< SODIMM
    DMI_MEM_DEVICE_FORM_FACTOR_SRIMM   = 0x0E, ///< SRIMM
    DMI_MEM_DEVICE_FORM_FACTOR_FBDIMM  = 0x0F, ///< FBDIMM
    DMI_MEM_DEVICE_FORM_FACTOR_DIE     = 0x10, ///< Die
    DMI_MEM_DEVICE_FORM_FACTOR_CAMM    = 0x11, ///< CAMM
    DMI_MEM_DEVICE_FORM_FACTOR_CUDIMM  = 0x12, ///< CUDIMM
    DMI_MEM_DEVICE_FORM_FACTOR_CSODIMM = 0x13, ///< CSODIMM
    __DMI_MEM_DEVICE_FORM_FACTOR_COUNT
};

__BEGIN_DECLS

const char *dmi_mem_array_location_name(enum dmi_mem_array_location value);
const char *dmi_mem_device_type_name(enum dmi_mem_device_type value);
const char *dmi_mem_device_form_factor_name(enum dmi_mem_device_form_factor value);

__END_DECLS

#endif // !OPENDMI_TABLE_MEMORY_H
