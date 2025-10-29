//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_H
#define OPENDMI_TABLE_MEMORY_H

#pragma once

#include <opendmi/table.h>

enum dmi_memory_array_location
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

enum dmi_memory_array_usage
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

enum dmi_memory_device_type
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

enum dmi_memory_device_form_factor
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

enum dmi_memory_device_technology
{
    DMI_MEM_DEVICE_TECHNOLOGY_OTHER    = 0x01, ///< Other
    DMI_MEM_DEVICE_TECHNOLOGY_UNKNOWN  = 0x02, ///< Unknown
    DMI_MEM_DEVICE_TECHNOLOGY_DRAM     = 0x03, ///< DRAM
    DMI_MEM_DEVICE_TECHNOLOGY_NVDIMM_N = 0x04, ///< NVDIMM-N
    DMI_MEM_DEVICE_TECHNOLOGY_NVDIMM_F = 0x05, ///< NVDIMM-F
    DMI_MEM_DEVICE_TECHNOLOGY_NVDIMM_P = 0x06, ///< NVDIMM-P
    DMI_MEM_DEVICE_TECHNOLOGY_OPTANE   = 0x07, ///< Intel Optane persistent memory
    DMI_MEM_DEVICE_TECHNOLOGY_MRDIMM   = 0x08, ///< MRDIMM (deprecated)
    __DMI_MEM_DEVICE_TECHNOLOGY_COUNT
};

union dmi_memory_device_type_detail
{
    uint16_t raw_value;

    struct
    {
        bool reserved : 1;
        bool other : 1;
        bool unknown : 1;
        bool fast_paged : 1;
        bool static_column : 1;
        bool pseudo_static : 1;
        bool rambus : 1;
        bool synchronous: 1;
        bool cmos : 1;
        bool edo : 1;
        bool window_dram : 1;
        bool cache_dram : 1;
        bool non_volatile : 1;
        bool registered : 1;
        bool unbuffered : 1;
        bool lrdimm : 1;
    } __attribute__((packed));
} __attribute__((packed));

/**
 * @since SMBIOS 2.1
 */
struct dmi_memory_device_table
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Handle, or instance number, associated with the physical
     * memory array to which this device belongs.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t mem_array_handle;

    /**
     * @brief Handle, or instance number, associated with any error that was
     * previously detected for the device. If the system does not provide the
     * error information structure, the field contains 0xFFFE. Otherwise, the
     * field contains either 0xFFFF (if no error was detected) or the handle
     * of the error-information structure.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t mem_error_handle;

    /**
     * @brief Total width, in bits, of this memory device, including any check
     * or error-correction bits. If there are no error-correction bits, this
     * value should be equal to data width. If the width is unknown, the field
     * is set to 0xFFFF.
     *
     * @since SMBIOS 2.1
     */
    uint16_t total_width;

    /**
     * @brief Data width, in bits, of this memory device. A data width of 0 and
     * a total width of 8 indicates that the device is being used solely to
     * provide 8 error-correction bits. If the width is unknown, the field is
     * set to 0xFFFF.
     *
     * @since SMBIOS 2.1
     */
    uint16_t data_width;

    /**
     * @brief Size of the memory device.
     *
     * If the value is 0, no memory device is installed in the socket. If the
     * size is unknown, the field value is 0xFFFF. If the size is 32 GiB-1 MiB
     * or greater, the field value is 0x7FFF and the actual size is stored in
     * the extended size field.
     *
     * The granularity in which the value is specified depends on the setting
     * of the most-significant bit (bit 15). If the bit is 0, the value is
     * specified in megabyte units; if the bit is 1, the value is specified in
     * kilobyte units. For example, the value 0x8100 identifies a 256 KiB
     * memory device and 0x0100 identifies a 256 MiB memory device.
     *
     * @since SMBIOS 2.1
     */
    uint16_t size;

    /**
     * @brief Implementation form factor for this memory device.
     *
     * @since SMBIOS 2.1
     */
    enum dmi_memory_device_form_factor form_factor : 8;

    /**
     * @brief Identifies when the memory device is one of a set of memory
     * devices that must be populated with all devices of the same type and
     * size, and the set to which this device belongs.
     *
     * A value of 0 indicates that the device is not part of a set. A value of
     * 0xFF indicates that the attribute is unknown.
     *
     * @since SMBIOS 2.1
     */
    uint8_t device_set;

    /**
     * @brief String number of the string that identifies the physically
     * labeled socket or board position where the memory device is located.
     * Example: "SIMM 3".
     *
     * @since SMBIOS 2.1
     */
    dmi_string_t device_locator;

    /**
     * @brief String number of the string that identifies the physically
     * labeled bank where the memory device is located. Example: "Bank 0" or
     * "A".
     *
     * @since SMBIOS 2.1
     */
    dmi_string_t bank_locator;

    /**
     * @brief Type of memory used in this device.
     *
     * @since SMBIOS 2.1
     */
    enum dmi_memory_device_type memory_type : 8;

    /**
     * @brief Additional detail on the memory device type.
     *
     * @since SMBIOS 2.1
     */
    union dmi_memory_device_type_detail memory_type_detail;

    /**
     * @brief Identifies the maximum capable speed of the device, in
     * megatransfers per second (MT/s). A value of 0x0000 indicated that the
     * speed is unknown. A value of 0xFFFF indicates that the speed is
     * 65,535 MT/s or greater, and the actual speed is stored in the extended
     * speed field.
     *
     * @since SMBIOS 2.3
     */
    uint16_t maximum_speed;

    /**
     * @brief String number for the manufacturer of this memory device.
     *
     * @since SMBIOS 2.3
     */
    dmi_string_t manufacturer;

    /**
     * @brief String number for the serial number of this memory device. This
     * value is set by the manufacturer and normally is not changeable.
     *
     * @since SMBIOS 2.3
     */
    dmi_string_t serial_number;

    /**
     * @brief String number for the asset tag of this memory device.
     *
     * @since SMBIOS 2.3
     */
    dmi_string_t asset_tag;

    /**
     * @brief String number for the part number of this memory device. This
     * value is set by the manufacturer and normally is not changeable.
     * 
     * @since SMBIOS 2.3
     */
    dmi_string_t part_number;

    /**
     * @since SMBIOS 2.6
     */
    uint8_t attributes;

    /**
     * @since SMBIOS 2.7
     */
    uint32_t size_ex;

    /**
     * @since SMBIOS 2.7
     */
    uint16_t configured_speed;

    /**
     * @since SMBIOS 2.8
     */
    uint16_t minimum_voltage;

    /**
     * @since SMBIOS 2.8
     */
    uint16_t maximum_voltage;

    /**
     * @since SMBIOS 2.8
     */
    uint16_t configured_voltage;

    /**
     * @since SMBIOS 3.2
     */
    uint8_t memory_technology;

    /**
     * @since SMBIOS 3.2
     */
    uint16_t memory_mode_caps;

    /**
     * @since SMBIOS 3.2
     */
    dmi_string_t firmware_version;

    /**
     * @since SMBIOS 3.2
     */
    uint16_t module_manufacturer_id;

    /**
     * @since SMBIOS 3.2
     */
    uint16_t module_product_id;

    /**
     * @since SMBIOS 3.2
     */
    uint16_t memory_subsys_ctrl_manufacturer_id;

    /**
     * @since SMBIOS 3.2
     */
    uint16_t memory_subsys_ctrl_product_id;

    /**
     * @since SMBIOS 3.2
     */
    uint64_t non_volatile_size;

    /**
     * @since SMBIOS 3.2
     */
    uint64_t volatile_size;

    /**
     * @since SMBIOS 3.2
     */
    uint64_t cache_size;

    /**
     * @since SMBIOS 3.2
     */
    uint64_t logical_size;

    /**
     * @since SMBIOS 3.3
     */
    uint32_t maximum_speed_ex;

    /**
     * @since SMBIOS 3.3
     */
    uint32_t configured_speed_ex;

    /**
     * @brief The two-byte PMIC0 manufacturer ID found in the SPD of this
     * memory device, LSB first.
     *
     * @since SMBIOS 3.7
     */
    uint16_t pmic0_manufacturer_id;

    /**
     * @brief The PMIC 0 Revision Number found in the SPD of this memory
     * device.
     *
     * @since SMBIOS 3.7
     */
    uint16_t pmic0_revision_number;

    /**
     * @brief The two-byte RCD manufacturer ID found in the SPD of this memory
     * device, LSB first.
     *
     * @since SMBIOS 3.7
     */
    uint16_t rcd_manufacturer_id;

    /**
     * @brief The RCD 0 Revision Number found in the SPD of this memory device.
     *
     * @since SMBIOS 3.7
     */
    uint16_t rcd_revision_number;
} __attribute__((packed));

/**
 * @brief Memory controller information table specification.
 */
extern const dmi_table_spec_t dmi_memory_controller_table_spec;

/**
 * @brief Memory module information table specification.
 */
extern const dmi_table_spec_t dmi_memory_module_table_spec;

__BEGIN_DECLS

const char *dmi_memory_array_location_name(enum dmi_memory_array_location value);
const char *dmi_memory_device_type_name(enum dmi_memory_device_type value);
const char *dmi_memory_device_form_factor_name(enum dmi_memory_device_form_factor value);

__END_DECLS

#endif // !OPENDMI_TABLE_MEMORY_H
