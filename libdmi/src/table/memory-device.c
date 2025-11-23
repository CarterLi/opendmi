//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <limits.h>

#include <opendmi/name.h>
#include <opendmi/utils.h>
#include <opendmi/table/memory-device.h>

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

static const dmi_name_t dmi_memory_device_type_detail_names[] =
{
    {
        .id   = 1,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = 2,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = 3,
        .code = "fast-paged",
        .name = "Fast-paged"
    },
    {
        .id   = 4,
        .code = "static-column",
        .name = "Static column"
    },
    {
        .id   = 5,
        .code = "pseudo-static",
        .name = "Pseudo-static"
    },
    {
        .id   = 6,
        .code = "rambus",
        .name = "RAMBUS"
    },
    {
        .id   = 7,
        .code = "synchronous",
        .name = "Synchronous"
    },
    {
        .id   = 8,
        .code = "cmos",
        .name = "CMOS"
    },
    {
        .id   = 9,
        .code = "edo",
        .name = "EDO"
    },
    {
        .id   = 10,
        .code = "window-dram",
        .name = "Window DRAM"
    },
    {
        .id   = 11,
        .code = "cache-dram",
        .name = "Cache DRAM"
    },
    {
        .id   = 12,
        .code = "non-volatile",
        .name = "Non-volatile"
    },
    {
        .id   = 13,
        .code = "registered",
        .name = "Registered (buffered)"
    },
    {
        .id   = 14,
        .code = "unbuffered",
        .name = "Unbuffered (unregistered)"
    },
    {
        .id   = 15,
        .code = "lrdimm",
        .name = "LRDIMM"
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

const dmi_attribute_t dmi_memory_device_attrs[] =
{
    DMI_ATTRIBUTE(dmi_memory_device_t, array_handle, HANDLE, {
        .code    = "array-handle",
        .name    = "Memory array handle",
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, error_handle, HANDLE, {
        .code    = "error-handle",
        .name    = "Memory error information handle"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, total_width, INTEGER, {
        .code    = "total-width",
        .name    = "Total width",
        .unit    = "bits",
        .unknown = &(unsigned short){ USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, data_width, INTEGER, {
        .code    = "data-width",
        .name    = "Data width",
        .unit    = "bits",
        .unknown = &(unsigned short){ USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, size, SIZE, {
        .code    = "size",
        .name    = "Size",
        .unknown = &(dmi_size_t){ UINT64_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, form_factor, ENUM, {
        .code    = "form-factor",
        .name    = "Form-factor",
        .values  = dmi_memory_device_form_factor_names
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, device_set, INTEGER, {
        .code    = "device-set",
        .name    = "Device set",
        .unknown = &(unsigned short){ USHRT_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, device_locator, STRING, {
        .code    = "device-locator",
        .name    = "Device locator"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, bank_locator, STRING, {
        .code    = "bank-locator",
        .name    = "Bank locator"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, memory_type, ENUM, {
        .code    = "memory-type",
        .name    = "Memory type",
        .values  = dmi_memory_device_type_names
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, memory_type_detail, SET, {
        .code   = "memory-type-details",
        .name   = "Memory type details",
        .values = dmi_memory_device_type_detail_names
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, maximum_speed, INTEGER, {
        .code    = "maximum-speed",
        .name    = "Maximum speed",
        .unit    = "MT/s",
        .unknown = &(unsigned long){ 0 }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, vendor, STRING, {
        .code    = "vendor",
        .name    = "Manufacturer"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, serial_number, STRING, {
        .code    = "serial-number",
        .name    = "Serial number"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, asset_tag, STRING, {
        .code    = "asset-tag",
        .name    = "Asset tag"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, part_number, STRING, {
        .code    = "part-number",
        .name    = "Part number"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, rank, INTEGER, {
        .code    = "rank",
        .name    = "Rank",
        .unknown = &(unsigned short){ 0 }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, configured_speed, INTEGER, {
        .code    = "configured-speed",
        .name    = "Configured speed",
        .unit    = "MT/s",
        .unknown = &(unsigned long){ 0 }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, minimum_voltage, INTEGER, {
        .code    = "minimum-voltage",
        .name    = "Minimum voltage",
        .unit    = "mV",
        .unknown = &(unsigned short){ 0 }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, maximum_voltage, INTEGER, {
        .code    = "maximum-voltage",
        .name    = "Maximum voltage",
        .unit    = "mV",
        .unknown = &(unsigned short){ 0 }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, configured_voltage, INTEGER, {
        .code    = "configured-voltage",
        .name    = "Configured voltage",
        .unit    = "mV",
        .unknown = &(unsigned short){ 0 }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, memory_technology, ENUM, {
        .code    = "memory-technology",
        .name    = "Memory technology",
        .values  = dmi_memory_device_technology_names
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, memory_mode_caps, INTEGER, {
        .code    = "memory-mode-caps",
        .name    = "Memory operating mode capabilities",
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, firmware_version, STRING, {
        .code    = "firmware-version",
        .name    = "Firmware version"
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, module_vendor_id, INTEGER, {
        .code    = "module-vendor-id",
        .name    = "Module manufacturer ID",
        .unknown = &(uint16_t){ 0x0000U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, module_product_id, INTEGER, {
        .code    = "module-product-id",
        .name    = "Module product ID",
        .unknown = &(uint16_t){ 0x0000U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, controller_vendor_id, INTEGER, {
        .code    = "controller-vendor-id",
        .name    = "Memory subsystem controller manufacturer ID",
        .unknown = &(uint16_t){ 0x0000U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, controller_product_id, INTEGER, {
        .code    = "controller-product-id",
        .name    = "Memory subsystem controller product ID",
        .unknown = &(uint16_t){ 0x0000U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, non_volatile_size, SIZE, {
        .code    = "non-volatile-size",
        .name    = "Non-volatile size",
        .unknown = &(dmi_size_t){ UINT64_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, volatile_size, SIZE, {
        .code    = "volatile-size",
        .name    = "Volatile size",
        .unknown = &(dmi_size_t){ UINT64_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, cache_size, SIZE, {
        .code    = "cache-size",
        .name    = "Cache size",
        .unknown = &(dmi_size_t){ UINT64_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, logical_size, SIZE, {
        .code    = "logical-size",
        .name    = "Logical size",
        .unknown = &(dmi_size_t){ UINT64_MAX }
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, pmic0_vendor_id, INTEGER, {
        .code    = "pmi0-vendor-id",
        .name    = "PMIC0 manufacturer ID",
        .unknown = &(uint16_t){ 0x0000U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, pmic0_revision, INTEGER, {
        .code    = "pmic0-revision",
        .name    = "PMIC0 revision number",
        .unknown = &(uint16_t){ 0xFF00U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, rcd_vendor_id, INTEGER, {
        .code    = "rcd-vendor-id",
        .name    = "RCD manufacturer ID",
        .unknown = &(uint16_t){ 0x0000U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_memory_device_t, rcd_revision, INTEGER, {
        .code    = "rcd-revision",
        .name    = "RCD revision number",
        .unknown = &(uint16_t){ 0xFF00U },
        .flags   = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_memory_device_table =
{
    .tag        = "memory-device",
    .name       = "Memory device",
    .type       = DMI_TYPE_MEMORY_DEVICE,
    .min_length = 0x15,
    .attributes = dmi_memory_device_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_memory_device_decode,
        .free   = (dmi_table_free_fn_t)dmi_memory_device_free
    }
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

dmi_size_t dmi_memory_device_size(uint16_t value)
{
    dmi_size_t size = value & 0x7FFFu;

    if (value & 0x8000u)
        size <<= 10; // Granularity is 1 Kb
    else
        size <<= 20; // Granularity is 1 Mb

    return size;
}

dmi_size_t dmi_memory_device_size_ex(uint32_t value)
{
    if (value & 0x80000000u)
        return SIZE_MAX;

    return (dmi_size_t)(value & 0x7FFFFFFFu) << 20; // Granularity is 1 Mb
}

dmi_memory_device_t *dmi_memory_device_decode(dmi_table_t *table)
{
    dmi_memory_device_t *info = nullptr;
    dmi_memory_device_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    info->array_handle = dmi_value(data->array_handle);
    info->error_handle = dmi_value(data->error_handle);

    info->total_width = dmi_value(data->total_width);
    if (info->total_width == 0xFFFFu)
        info->total_width = USHRT_MAX;

    info->data_width = dmi_value(data->data_width);
    if (info->data_width == 0xFFFFu)
        info->data_width = USHRT_MAX;

    if (data->size != 0xFFFFu)
        info->size = dmi_memory_device_size(dmi_value(data->size));
    else
        info->size = UINT64_MAX;

    info->form_factor = data->form_factor;

    if (data->device_set != 0xFFu)
        info->device_set = data->device_set;
    else
        info->device_set = USHRT_MAX;

    info->device_locator            = dmi_table_string(table, data->device_locator);
    info->bank_locator              = dmi_table_string(table, data->bank_locator);
    info->memory_type               = dmi_value(data->memory_type);
    info->memory_type_detail._value = dmi_value(data->memory_type_detail);

    // SMBIOS 2.3 features
    if (table->body_length >= 0x15) {
        info->maximum_speed = dmi_value(data->maximum_speed);
        info->vendor        = dmi_table_string(table, data->vendor);
        info->serial_number = dmi_table_string(table, data->serial_number);
        info->asset_tag     = dmi_table_string(table, data->asset_tag);
        info->part_number   = dmi_table_string(table, data->part_number);
    }

    // SMBIOS 2.6 features
    if (table->body_length >= 0x1B) {
        info->rank = data->rank;
    }

    // SMBIOS 2.7 features
    if (table->body_length >= 0x1C) {
        if (data->size == 0x7FFFU)
            info->size = dmi_memory_device_size_ex(dmi_value(data->size));

        info->configured_speed = dmi_value(data->configured_speed);
    }

    // SMBIOS 2.8 features
    if (table->body_length >= 0x22) {
        info->minimum_voltage    = dmi_value(data->minimum_voltage);
        info->maximum_voltage    = dmi_value(data->maximum_voltage);
        info->configured_voltage = dmi_value(data->configured_voltage);
    }

    // SMBIOS 3.2 features
    if (table->body_length >= 0x28) {
        info->memory_technology = data->memory_technology;
        info->memory_mode_caps  = dmi_value(data->memory_mode_caps);

        info->firmware_version = dmi_table_string(table, data->firmware_version);

        info->module_vendor_id      = dmi_value(data->module_vendor_id);
        info->module_product_id     = dmi_value(data->module_product_id);
        info->controller_vendor_id  = dmi_value(data->controller_vendor_id);
        info->controller_product_id = dmi_value(data->controller_product_id);

        info->non_volatile_size = dmi_value(data->non_volatile_size);
        info->volatile_size     = dmi_value(data->volatile_size);
        info->cache_size        = dmi_value(data->cache_size);
        info->logical_size      = dmi_value(data->logical_size);
    }

    // SMBIOS 3.3 features
    if (table->body_length >= 0x54) {
        if (data->maximum_speed == 0xFFFFu)
            info->maximum_speed = dmi_value(data->maximum_speed_ex);
        if (data->configured_speed == 0xFFFFu)
            info->configured_speed = dmi_value(data->configured_speed_ex);
    }

    // SMBIOS 3.7 features
    if (table->body_length >= 0x5C) {
        info->pmic0_vendor_id = dmi_value(data->pmic0_vendor_id);
        info->pmic0_revision  = dmi_value(data->pmic0_revision);
        info->rcd_vendor_id   = dmi_value(data->rcd_vendor_id);
        info->rcd_revision    = dmi_value(data->rcd_revision);
    }

    return info;
}

void dmi_memory_device_free(dmi_memory_device_t *info)
{
    free(info);
}
