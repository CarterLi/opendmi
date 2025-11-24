//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_ERROR_64_H
#define OPENDMI_TABLE_MEMORY_ERROR_64_H

#pragma once

#include <opendmi/table/memory-error.h>

/**
 * @brief 64-Bit memory error information table (type 33).
 * @since SMBIOS 2.3
 */
DMI_PACKED_STRUCT(dmi_memory_error_64_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Type of error that is associated with the current status reported
     * for the memory array or device.
     */
    dmi_byte_t type;

    /**
     * @brief Granularity (for example, device versus partition) to which the
     * error can be resolved.
     */
    dmi_byte_t granularity;

    /**
     * @brief Memory access operation that caused the error.
     */
    dmi_byte_t operation;

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
    dmi_qword_t array_addr;

    /**
     * @brief 64-bit physical address of the error relative to the start of
     * the failing memory device, in bytes. If the address is unknown, this
     * field contains 0x8000000000000000.
     */
    dmi_qword_t device_addr;

    /**
     * @brief Range, in bytes, within which the error can be determined, when
     * an error address is given. If the range is unknown, this field contains
     * 0x80000000.
     */
    dmi_dword_t resolution;
};

#ifndef DMI_MEMORY_ERROR_64_DATA_T
#define DMI_MEMORY_ERROR_64_DATA_T
typedef struct dmi_memory_error_64_data dmi_memory_error_64_data_t;
#endif // !DMI_MEMORY_ERROR_64_DATA_T

/**
 * @brief 64-bit memory error information table specification.
 */
extern const dmi_table_spec_t dmi_memory_error_64_table;

__BEGIN_DECLS

dmi_memory_error_t *dmi_memory_error_64_decode(const dmi_table_t *table);

__END_DECLS

#endif // !OPENDMI_TABLE_MEMORY_ERROR_64_H
