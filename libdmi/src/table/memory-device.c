//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-device.h>
#include <opendmi/utils.h>

static const char *dmi_memory_device_type_names[__DMI_MEMORY_DEVICE_TYPE_COUNT] =
{
    [DMI_MEMORY_DEVICE_TYPE_OTHER]       = "Other",
    [DMI_MEMORY_DEVICE_TYPE_UNKNOWN]     = "Unknown",
    [DMI_MEMORY_DEVICE_TYPE_DRAM]        = "DRAM",
    [DMI_MEMORY_DEVICE_TYPE_EDRAM]       = "EDRAM",
    [DMI_MEMORY_DEVICE_TYPE_VRAM]        = "VRAM",
    [DMI_MEMORY_DEVICE_TYPE_SRAM]        = "SRAM",
    [DMI_MEMORY_DEVICE_TYPE_RAM]         = "RAM",
    [DMI_MEMORY_DEVICE_TYPE_ROM]         = "ROM",
    [DMI_MEMORY_DEVICE_TYPE_FLASH]       = "Flash",
    [DMI_MEMORY_DEVICE_TYPE_EEPROM]      = "EEPROM",
    [DMI_MEMORY_DEVICE_TYPE_FEPROM]      = "FEPROM",
    [DMI_MEMORY_DEVICE_TYPE_EPROM]       = "EPROM",
    [DMI_MEMORY_DEVICE_TYPE_CDRAM]       = "CDRAM",
    [DMI_MEMORY_DEVICE_TYPE_3DRAM]       = "3DRAM",
    [DMI_MEMORY_DEVICE_TYPE_SDRAM]       = "SDRAM",
    [DMI_MEMORY_DEVICE_TYPE_SGRAM]       = "SGRAM",
    [DMI_MEMORY_DEVICE_TYPE_RDRAM]       = "RDRAM",
    [DMI_MEMORY_DEVICE_TYPE_DDR]         = "DDR",
    [DMI_MEMORY_DEVICE_TYPE_DDR2]        = "DDR2",
    [DMI_MEMORY_DEVICE_TYPE_DDR2_FBDIMM] = "DDR2 FB-DIMM",
    [DMI_MEMORY_DEVICE_TYPE_DDR3]        = "DDR3",
    [DMI_MEMORY_DEVICE_TYPE_FBD2]        = "FBD2",
    [DMI_MEMORY_DEVICE_TYPE_DDR4]        = "DDR4",
    [DMI_MEMORY_DEVICE_TYPE_LPDDR]       = "LPDDR",
    [DMI_MEMORY_DEVICE_TYPE_LPDDR2]      = "LPDDR2",
    [DMI_MEMORY_DEVICE_TYPE_LPDDR3]      = "LPDDR3",
    [DMI_MEMORY_DEVICE_TYPE_LPDDR4]      = "LPDDR4",
    [DMI_MEMORY_DEVICE_TYPE_LOGICAL_NV]  = "Logical non-volatile device",
    [DMI_MEMORY_DEVICE_TYPE_HBM]         = "HBM (High Bandwidth Memory)",
    [DMI_MEMORY_DEVICE_TYPE_HBM2]        = "HBM2 (High Bandwidth Memory Generation 2)",
    [DMI_MEMORY_DEVICE_TYPE_DDR5]        = "DDR5",
    [DMI_MEMORY_DEVICE_TYPE_LPDDR5]      = "LPDDR5",
    [DMI_MEMORY_DEVICE_TYPE_HBM3]        = "HBM3 (High Bandwidth Memory Generation 3)",
    [DMI_MEMORY_DEVICE_TYPE_MRDIMM]      = "MRDIMM"
};

static const char *dmi_memory_device_form_factor_names[__DMI_MEMORY_DEVICE_FORM_FACTOR_COUNT] =
{
    [DMI_MEMORY_DEVICE_FORM_FACTOR_OTHER]   = "Other",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_UNKNOWN] = "Unknown",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_SIMM]    = "SIMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_SIP]     = "SIP",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_CHIP]    = "Chip",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_DIP]     = "DIP",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_ZIP]     = "ZIP",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_CARD]    = "Proprietary card",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_DIMM]    = "DIMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_TSOP]    = "TSOP",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_ROW]     = "Row of chips",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_RIMM]    = "RIMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_SODIMM]  = "SODIMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_SRIMM]   = "SRIMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_FBDIMM]  = "FBDIMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_DIE]     = "Die",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_CAMM]    = "CAMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_CUDIMM]  = "CUDIMM",
    [DMI_MEMORY_DEVICE_FORM_FACTOR_CSODIMM] = "CSODIMM"
};

static const char *dmi_memory_device_technology_names[__DMI_MEMORY_DEVICE_TECHNOLOGY_COUNT] =
{
    [DMI_MEMORY_DEVICE_TECHNOLOGY_OTHER]    = "Other",
    [DMI_MEMORY_DEVICE_TECHNOLOGY_UNKNOWN]  = "Unknown",
    [DMI_MEMORY_DEVICE_TECHNOLOGY_DRAM]     = "DRAM",
    [DMI_MEMORY_DEVICE_TECHNOLOGY_NVDIMM_N] = "NVDIMM-N",
    [DMI_MEMORY_DEVICE_TECHNOLOGY_NVDIMM_F] = "NVDIMM-F",
    [DMI_MEMORY_DEVICE_TECHNOLOGY_NVDIMM_P] = "NVDIMM-P",
    [DMI_MEMORY_DEVICE_TECHNOLOGY_OPTANE]   = "Intel Optane persistent memory",
    [DMI_MEMORY_DEVICE_TECHNOLOGY_MRDIMM]   = "MRDIMM"
};

const dmi_attribute_spec_t dmi_memory_device_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_memory_device_table =
{
    .tag        = "memory-device",
    .name       = "Memory device",
    .type       = DMI_TYPE_MEMORY_DEVICE,
    .min_length = 0x15,
    .attributes = dmi_memory_device_attrs
};

const dmi_attribute_spec_t dmi_memory_device_addr_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_memory_device_addr_table =
{
    .tag         = "memory-device-address",
    .name        = "Memory device mapped address",
    .type        = DMI_TYPE_MEMORY_DEVICE_ADDR,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x13,
    .attributes  = dmi_memory_device_addr_attrs
};

const char *dmi_memory_device_type_name(enum dmi_memory_device_type value)
{
    return dmi_name(dmi_memory_device_type_names, value, __DMI_MEMORY_DEVICE_TYPE_COUNT);
}

const char *dmi_memory_device_form_factor_name(enum dmi_memory_device_form_factor value)
{
    return dmi_name(dmi_memory_device_form_factor_names, value, __DMI_MEMORY_DEVICE_FORM_FACTOR_COUNT);
}

const char *dmi_memory_device_technology_name(enum dmi_memory_device_technology value)
{
    return dmi_name(dmi_memory_device_technology_names, value, __DMI_MEMORY_DEVICE_TECHNOLOGY_COUNT);
}
