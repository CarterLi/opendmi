//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_ERROR_H
#define OPENDMI_TABLE_MEMORY_ERROR_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_MEMORY_ERROR_32_DATA_T
#define DMI_MEMORY_ERROR_32_DATA_T
typedef struct dmi_memory_error_32_data dmi_memory_error_32_data_t;
#endif // !DMI_MEMORY_ERROR_32_DATA_T

#ifndef DMI_MEMORY_ERROR_32_T
#define DMI_MEMORY_ERROR_32_T
typedef struct dmi_memory_error_32 dmi_memory_error_32_t;
#endif // !DMI_MEMORY_ERROR_32_T

#ifndef DMI_MEMORY_ERROR_64_DATA_T
#define DMI_MEMORY_ERROR_64_DATA_T
typedef struct dmi_memory_error_64_data dmi_memory_error_64_data_t;
#endif // !DMI_MEMORY_ERROR_64_DATA_T

#ifndef DMI_MEMORY_ERROR_64_T
#define DMI_MEMORY_ERROR_64_T
typedef struct dmi_memory_error_64 dmi_memory_error_64_t;
#endif // !DMI_MEMORY_ERROR_64_T

/**
 * @brief Memory error types.
 */
enum dmi_memory_error_type
{
    DMI_MEMORY_ERROR_TYPE_OTHER                = 0x01, ///< Other
    DMI_MEMORY_ERROR_TYPE_UNKNOWN              = 0x02, ///< Unknown
    DMI_MEMORY_ERROR_TYPE_OK                   = 0x03, ///< OK
    DMI_MEMORY_ERROR_TYPE_BAD_READ             = 0x04, ///< Bad read
    DMI_MEMORY_ERROR_TYPE_PARITY               = 0x05, ///< Parity error
    DMI_MEMORY_ERROR_TYPE_SINGLE_BIT           = 0x06, ///< Single-bit error
    DMI_MEMORY_ERROR_TYPE_DOUBLE_BIT           = 0x07, ///< Double-bit error
    DMI_MEMORY_ERROR_TYPE_MULTI_BIT            = 0x08, ///< Multi-bit error
    DMI_MEMORY_ERROR_TYPE_NIBBLE               = 0x09, ///< Nibble error
    DMI_MEMORY_ERROR_TYPE_CHECKSUM             = 0x0A, ///< Checksum error
    DMI_MEMORY_ERROR_TYPE_CRC                  = 0x0B, ///< CRC error
    DMI_MEMORY_ERROR_TYPE_CORRECTED_SINGLE_BIT = 0x0C, ///< Corrected single-bit error
    DMI_MEMORY_ERROR_TYPE_CORRECTED            = 0x0D, ///< Corrected error
    DMI_MEMORY_ERROR_TYPE_UNCORRECTABLE        = 0x0E, ///< Uncorrectable error
};

/**
 * @brief Memory error granularities.
 */
enum dmi_memory_error_granularity
{
    DMI_MEMORY_ERROR_GRANULARITY_OTHER     = 0x01, ///< Other
    DMI_MEMORY_ERROR_GRANULARITY_UNKNOWN   = 0x02, ///< Unknown
    DMI_MEMORY_ERROR_GRANULARITY_DEVICE    = 0x03, ///< Device level
    DMI_MEMORY_ERROR_GRANULARITY_PARTITION = 0x04, ///< Memory partition level
};

/**
 * @brief Memory error operations.
 */
enum dmi_memory_error_operation
{
    DMI_MEMORY_ERROR_OPERATION_OTHER         = 0x01, ///< Other
    DMI_MEMORY_ERROR_OPERATION_UNKNOWN       = 0x02, ///< Unknown
    DMI_MEMORY_ERROR_OPERATION_READ          = 0x03, ///< Read
    DMI_MEMORY_ERROR_OPERATION_WRITE         = 0x04, ///< Write
    DMI_MEMORY_ERROR_OPERATION_PARTIAL_WRITE = 0x05, ///< Partial write
};

/**
 * @brief 32-Bit memory error information table (type 18).
 * @since SMBIOS 2.1
 */
DMI_PACKED_STRUCT(dmi_memory_error_32_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Type of error that is associated with the current status reported
     * for the memory array or device.
     */
    enum dmi_memory_error_type type : 8;

    /**
     * @brief Granularity (for example, device versus partition) to which the
     * error can be resolved.
     */
    enum dmi_memory_error_granularity granularity : 8;

    /**
     * @brief Memory access operation that caused the error.
     */
    enum dmi_memory_error_operation operation : 8;

    /**
     * @brief Vendor-specific ECC syndrome or CRC data associated with the
     * erroneous access. If the value is unknown, this field contains 0.
     */
    dmi_dword_t vendor_syndrome;

    /**
     * @brief 32-bit physical address of the error based on the addressing of
     * the bus to which the memory array is connected. If the address is
     * unknown, this field contains 0x80000000.
     */
    dmi_dword_t array_address;

    /**
     * @brief 32-bit physical address of the error relative to the start of
     * the failing memory device, in bytes. If the address is unknown, this
     * field contains 0x80000000.
     */
    dmi_dword_t device_address;

    /**
     * @brief Range, in bytes, within which the error can be determined, when
     * an error address is given. If the range is unknown, this field contains
     * 0x80000000.
     */
    dmi_dword_t resolution;
};

/**
 * @brief 64-Bit memory error information table (type 33).
 * @since SMBIOS 2.3
 */
DMI_PACKED_STRUCT(dmi_memory_error_64_table)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Type of error that is associated with the current status reported
     * for the memory array or device.
     */
    enum dmi_memory_error_type type : 8;

    /**
     * @brief Granularity (for example, device versus partition) to which the
     * error can be resolved.
     */
    enum dmi_memory_error_granularity granularity : 8;

    /**
     * @brief Memory access operation that caused the error.
     */
    enum dmi_memory_error_operation operation : 8;

    /**
     * @brief Vendor-specific ECC syndrome or CRC data associated with the
     * erroneous access. If the value is unknown, this field contains 0.
     */
    dmi_dword_t vendor_syndrome;

    /**
     * @brief 64-bit physical address of the error based on the addressing of
     * the bus to which the memory array is connected. If the address is
     * unknown, this field contains 0x8000000000000000.
     */
    dmi_qword_t array_address;

    /**
     * @brief 64-bit physical address of the error relative to the start of
     * the failing memory device, in bytes. If the address is unknown, this
     * field contains 0x8000000000000000.
     */
    dmi_qword_t device_address;

    /**
     * @brief Range, in bytes, within which the error can be determined, when
     * an error address is given. If the range is unknown, this field contains
     * 0x80000000.
     */
    dmi_dword_t resolution;
};

/**
 * @brief 32-bit memory error information table specification.
 */
extern const dmi_table_spec_t dmi_memory_error_32_table;

/**
 * @brief 64-bit memory error information table specification.
 */
extern const dmi_table_spec_t dmi_memory_error_64_table;

__BEGIN_DECLS

const char *dmi_memory_error_type_name(enum dmi_memory_error_type value);
const char *dmi_memory_error_granularity_name(enum dmi_memory_error_granularity value);
const char *dmi_memory_error_operation_name(enum dmi_memory_error_operation value);

__END_DECLS

#endif // !OPENDMI_TABLE_MEMORY_ERROR_H
