//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/memory-device.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_memory_device_type_names[] =
{
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_DRAM,
        .code = "dram",
        .name = "DRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_EDRAM,
        .code = "edram",
        .name = "EDRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_VRAM,
        .code = "vram",
        .name = "VRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_SRAM,
        .code = "sram",
        .name = "SRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_RAM,
        .code = "ram",
        .name = "RAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_ROM,
        .code = "rom",
        .name = "ROM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_FLASH,
        .code = "flash",
        .name = "Flash"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_EEPROM,
        .code = "eeprom",
        .name = "EEPROM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_FEPROM,
        .code = "feprom",
        .name = "FEPROM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_EPROM,
        .code = "eprom",
        .name = "EPROM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_CDRAM,
        .code = "cdram",
        .name = "CDRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_3DRAM,
        .code = "3dram",
        .name = "3DRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_SDRAM,
        .code = "sdram",
        .name = "SDRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_SGRAM,
        .code = "sgram",
        .name = "SGRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_RDRAM,
        .code = "rdram",
        .name = "RDRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_DDR,
        .code = "ddr",
        .name = "DDR"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_DDR2,
        .code = "ddr2",
        .name = "DDR2"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_DDR2_FBDIMM,
        .code = "ddr2-fbdimm",
        .name = "DDR2 FB-DIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_DDR3,
        .code = "ddr3",
        .name = "DDR3"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_FBD2,
        .code = "fbd2",
        .name = "FBD2"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_DDR4,
        .code = "ddr4",
        .name = "DDR4"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_LPDDR,
        .code = "lpddr",
        .name = "LPDDR"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_LPDDR2,
        .code = "lpddr2",
        .name = "LPDDR2"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_LPDDR3,
        .code = "lpddr3",
        .name = "LPDDR3"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_LPDDR4,
        .code = "lpddr4",
        .name = "LPDDR4"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_LOGICAL_NV,
        .code = "logical-nv",
        .name = "Logical non-volatile device"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_HBM,
        .code = "hbm",
        .name = "HBM (High Bandwidth Memory)"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_HBM2,
        .code = "hbm2",
        .name = "HBM2 (High Bandwidth Memory Generation 2)"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_DDR5,
        .code = "ddr5",
        .name = "DDR5"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_LPDDR5,
        .code = "lpddr5",
        .name = "LPDDR5"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_HBM3,
        .code = "hbm3",
        .name = "HBM3 (High Bandwidth Memory Generation 3)"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TYPE_MRDIMM,
        .code = "mrdimm",
        .name = "MRDIMM"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_memory_device_form_factor_names[] =
{
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_SIMM,
        .code = "simm",
        .name = "SIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_SIP,
        .code = "sip",
        .name = "SIP"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_CHIP,
        .code = "chip",
        .name = "Chip"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_DIP,
        .code = "dip",
        .name = "DIP"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_ZIP,
        .code = "zip",
        .name = "ZIP"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_CARD,
        .code = "card",
        .name = "Proprietary card"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_DIMM,
        .code = "dimm",
        .name = "DIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_TSOP,
        .code = "tsop",
        .name = "TSOP"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_CHIP_ROW,
        .code = "chip-row",
        .name = "Row of chips"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_RIMM,
        .code = "rimm",
        .name = "RIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_SODIMM,
        .code = "sodimm",
        .name = "SODIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_SRIMM,
        .code = "srimm",
        .name = "SRIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_FBDIMM,
        .code = "fbdimm",
        .name = "FBDIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_DIE,
        .code = "die",
        .name = "Die"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_CAMM,
        .code = "camm",
        .name = "CAMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_CUDIMM,
        .code = "cudimm",
        .name = "CUDIMM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_FORM_FACTOR_CSODIMM,
        .code = "csodimm",
        .name = "CSODIMM"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_memory_device_technology_names[] =
{
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_DRAM,
        .code = "dram",
        .name = "DRAM"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_NVDIMM_N,
        .code = "nvdimm-n",
        .name = "NVDIMM-N"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_NVDIMM_F,
        .code = "nvdimm-f",
        .name = "NVDIMM-F"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_NVDIMM_P,
        .code = "nvdimm-p",
        .name = "NVDIMM-P"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_OPTANE,
        .code = "optane",
        .name = "Intel Optane persistent memory"
    },
    {
        .id   = DMI_MEMORY_DEVICE_TECHNOLOGY_MRDIMM,
        .code = "mrdimm",
        .name = "MRDIMM"
    },
    DMI_NAME_NULL
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
    return dmi_name_lookup(dmi_memory_device_type_names, value);
}

const char *dmi_memory_device_form_factor_name(enum dmi_memory_device_form_factor value)
{
    return dmi_name_lookup(dmi_memory_device_form_factor_names, value);
}

const char *dmi_memory_device_technology_name(enum dmi_memory_device_technology value)
{
    return dmi_name_lookup(dmi_memory_device_technology_names, value);
}
