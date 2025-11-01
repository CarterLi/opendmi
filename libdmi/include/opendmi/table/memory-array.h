//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_ARRAY_H
#define OPENDMI_TABLE_MEMORY_ARRAY_H

#pragma once

#include <opendmi/table.h>
#include <opendmi/table/common.h>

/**
 * @brief Memory array location values.
 */
enum dmi_memory_array_location
{
    DMI_MEMORY_ARRAY_LOCATION_OTHER           = 0x01, ///< Other
    DMI_MEMORY_ARRAY_LOCATION_UNKNOWN         = 0x02, ///< Unknown
    DMI_MEMORY_ARRAY_LOCATION_MOTHERBOARD     = 0x03, ///< System board or motherboard
    DMI_MEMORY_ARRAY_LOCATION_ISA             = 0x04, ///< ISA add-on card
    DMI_MEMORY_ARRAY_LOCATION_EISA            = 0x05, ///< EISA add-on card
    DMI_MEMORY_ARRAY_LOCATION_PCI             = 0x06, ///< PCI add-on card
    DMI_MEMORY_ARRAY_LOCATION_MCA             = 0x07, ///< MCA add-on card
    DMI_MEMORY_ARRAY_LOCATION_PCMCIA          = 0x08, ///< PCMCIA add-on card
    DMI_MEMORY_ARRAY_LOCATION_PROPRIETARY     = 0x09, ///< Proprietary add-on card
    DMI_MEMORY_ARRAY_LOCATION_NUBUS           = 0x0A, ///< NuBus
    DMI_MEMORY_ARRAY_LOCATION_PC_98_C20       = 0xA0, ///< PC-98/C20 add-on card
    DMI_MEMORY_ARRAY_LOCATION_PC_98_C24       = 0xA1, ///< PC-98/C24 add-on card
    DMI_MEMORY_ARRAY_LOCATION_PC_98_E         = 0xA2, ///< PC-98/E add-on card
    DMI_MEMORY_ARRAY_LOCATION_PC_98_LOCAL_BUS = 0xA3, ///< PC-98/Local bus add-on card
    DMI_MEMORY_ARRAY_LOCATION_CXL             = 0xA4, ///< CXL add-on card
};

/**
 * @brief Memory array usage values.
 */
enum dmi_memory_array_usage
{
    DMI_MEMORY_ARRAY_USAGE_OTHER   = 0x01, ///< Other
    DMI_MEMORY_ARRAY_USAGE_UNKNOWN = 0x02, ///< Unknown
    DMI_MEMORY_ARRAY_USAGE_SYSTEM  = 0x03, ///< System memory
    DMI_MEMORY_ARRAY_USAGE_VIDEO   = 0x04, ///< Video memory
    DMI_MEMORY_ARRAY_USAGE_FLASH   = 0x05, ///< Flash memory
    DMI_MEMORY_ARRAY_USAGE_NVRAM   = 0x06, ///< Non-volatile RAM
    DMI_MEMORY_ARRAY_USAGE_CACHE   = 0x07, ///< Cache memory
};

/**
 * @brief Physical memory array table (type 16).
 * @since SMBIOS 2.1
 */
DMI_PACKED_STRUCT(dmi_memory_array_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Physical location of the memory array, whether on the system
     * board or an add-in board.
     *
     * @since SMBIOS 2.1
     */
    enum dmi_memory_array_location location : 8;

    /**
     * @brief Function for which the array is used.
     *
     * @since SMBIOS 2.1
     */
    enum dmi_memory_array_usage usage : 8;

    /**
     * @brief Primary hardware error correction or detection method supported
     * by this memory array.
     *
     * @since SMBIOS 2.1
     */
    enum dmi_ecc_type ecc_type : 8;

    /**
     * @brief Maximum memory capacity, in kibibytes, for this array.
     *
     * If the capacity is not represented in this field, then this field
     * contains 0x80000000 and the extended maximum capacity field should be
     * used. Values 2 TB (0x80000000) or greater must be represented in the
     * extended maximum capacity field.
     * 
     * @since SMBIOS 2.1
     */
    uint32_t maximum_capacity;

    /**
     * @brief Handle, or instance number, associated with any error that was
     * previously detected for the array.
     *
     * If the system does not provide the error information structure, the
     * field contains 0xFFFE. Otherwise, the field contains either 0xFFFF (if
     * no error was detected) or the handle of the error-information structure.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t error_handle;

    /**
     * @brief Number of slots or sockets available for memory devices in this
     * array.
     *
     * This value represents the number of memory device structures that
     * compose this memory array. Each memory device has a reference to the
     * "owning" memory array.
     * 
     * @since SMBIOS 2.1
     */
    uint16_t device_count;

    /**
     * @brief Extended maximum memory capacity, in bytes, for this array.
     *
     * This field is only valid when the maximum capacity field contains
     * 0x80000000. When maximum capacity contains a value that is not
     * 0x80000000, extended maximum capacity must contain zeros.
     *
     * @since SMBIOS 2.7
     */
    uint64_t maximum_capacity_ex;
};

/**
 * @brief Physical memory array table specification.
 */
extern const dmi_table_spec_t dmi_memory_array_table;

/**
 * @brief Memory array mapped address table specification.
 */
extern const dmi_table_spec_t dmi_memory_array_addr_table;

__BEGIN_DECLS

const char *dmi_memory_array_location_name(enum dmi_memory_array_location value);
const char *dmi_memory_array_usage_name(enum dmi_memory_array_usage value);

__END_DECLS

#endif // !OPENDMI_TABLE_MEMORY_ARRAY_H
