//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MEMORY_ERROR_H
#define OPENDMI_ENTITY_MEMORY_ERROR_H

#pragma once

#include <opendmi/entity.h>
#include <opendmi/utils/name.h>

/**
 * @brief Memory error types.
 */
typedef enum dmi_memory_error_type
{
    DMI_MEMORY_ERROR_TYPE_UNSPEC               = 0x00, ///< Unspecified
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
    __DMI_MEMORY_ERROR_TYPE_COUNT
} dmi_memory_error_type_t;

/**
 * @brief Memory error granularities.
 */
typedef enum dmi_memory_error_granularity
{
    DMI_MEMORY_ERROR_GRANULARITY_UNSPEC    = 0x00, ///< Unspecified
    DMI_MEMORY_ERROR_GRANULARITY_OTHER     = 0x01, ///< Other
    DMI_MEMORY_ERROR_GRANULARITY_UNKNOWN   = 0x02, ///< Unknown
    DMI_MEMORY_ERROR_GRANULARITY_DEVICE    = 0x03, ///< Device level
    DMI_MEMORY_ERROR_GRANULARITY_PARTITION = 0x04, ///< Memory partition level
    __DMI_MEMORY_ERROR_GRANULARITY_COUNT
} dmi_memory_error_granularity_t;

/**
 * @brief Memory error operations.
 */
typedef enum dmi_memory_error_operation
{
    DMI_MEMORY_ERROR_OPERATION_UNSPEC        = 0x00, ///< Unspecified
    DMI_MEMORY_ERROR_OPERATION_OTHER         = 0x01, ///< Other
    DMI_MEMORY_ERROR_OPERATION_UNKNOWN       = 0x02, ///< Unknown
    DMI_MEMORY_ERROR_OPERATION_READ          = 0x03, ///< Read
    DMI_MEMORY_ERROR_OPERATION_WRITE         = 0x04, ///< Write
    DMI_MEMORY_ERROR_OPERATION_PARTIAL_WRITE = 0x05, ///< Partial write
    __DMI_MEMORY_ERROR_OPERATION_COUNT
} dmi_memory_error_operation_t;

struct dmi_memory_error
{
    /**
     * @brief Type of error that is associated with the current status reported
     * for the memory array or device.
     */
    dmi_memory_error_type_t type;

    /**
     * @brief Granularity (for example, device versus partition) to which the
     * error can be resolved.
     */
    dmi_memory_error_granularity_t granularity;

    /**
     * @brief Memory access operation that caused the error.
     */
    dmi_memory_error_operation_t operation;

    /**
     * @brief Vendor-specific ECC syndrome or CRC data associated with the
     * erroneous access. If the value is unknown, this field contains 0.
     */
    uint32_t vendor_syndrome;

    /**
     * @brief Physical address of the error based on the addressing of
     * the bus to which the memory array is connected. If the address is
     * unknown, this field contains `0x8000000000000000`.
     */
    dmi_size_t array_addr;

    /**
     * @brief Physical address of the error relative to the start of
     * the failing memory device, in bytes. If the address is unknown, this
     * field contains `0x8000000000000000`.
     */
    dmi_size_t device_addr;

    /**
     * @brief Range, in bytes, within which the error can be determined, when
     * an error address is given. If the range is unknown, this field contains
     * `0`
     */
    dmi_size_t resolution;
};

typedef struct dmi_memory_error dmi_memory_error_t;

/**
 * @brief Memory error attributes.
 */
extern const dmi_attribute_t dmi_memory_error_attrs[];

__BEGIN_DECLS

const char *dmi_memory_error_type_name(dmi_memory_error_type_t value);
const char *dmi_memory_error_granularity_name(dmi_memory_error_granularity_t value);
const char *dmi_memory_error_operation_name(dmi_memory_error_operation_t value);

__END_DECLS

#endif // !OPENDMI_ENTITY_MEMORY_ERROR_H
