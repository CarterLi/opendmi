//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MEMORY_ERROR_32_H
#define OPENDMI_ENTITY_MEMORY_ERROR_32_H

#pragma once

#include <opendmi/entity/memory-error.h>

/**
 * @brief 32-Bit memory error information structure (type 18).
 * @since SMBIOS 2.1
 */
dmi_packed_struct(dmi_memory_error_32_data)
{
    /**
     * @brief SMBIOS structure header.
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
     * @brief 32-bit physical address of the error based on the addressing of
     * the bus to which the memory array is connected. If the address is
     * unknown, this field contains 0x80000000.
     */
    dmi_dword_t array_addr;

    /**
     * @brief 32-bit physical address of the error relative to the start of
     * the failing memory device, in bytes. If the address is unknown, this
     * field contains 0x80000000.
     */
    dmi_dword_t device_addr;

    /**
     * @brief Range, in bytes, within which the error can be determined, when
     * an error address is given. If the range is unknown, this field contains
     * 0x80000000.
     */
    dmi_dword_t resolution;
};

typedef struct dmi_memory_error_32_data dmi_memory_error_32_data_t;

/**
 * @brief 32-bit memory error information entity specification.
 */
extern const dmi_entity_spec_t dmi_memory_error_32_spec;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_memory_error_t *dmi_memory_error_32_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

__END_DECLS

#endif // !OPENDMI_ENTITY_MEMORY_ERROR_32_H
