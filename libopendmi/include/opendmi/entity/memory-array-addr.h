//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MEMORY_ARRAY_ADDR_H
#define OPENDMI_ENTITY_MEMORY_ARRAY_ADDR_H

#pragma once

#include <opendmi/entity/memory-array.h>

typedef struct dmi_memory_array_addr_data dmi_memory_array_addr_data_t;
typedef struct dmi_memory_array_addr      dmi_memory_array_addr_t;

/**
 * @brief Memory array mapped address structure (type 19).
 * @since SMBIOS 2.1
 */
dmi_packed_struct(dmi_memory_array_addr_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Physical address, in kibibytes, of a range of memory mapped to
     * the specified physical memory array.
     *
     * When the field value is `0xFFFFFFFF`, the actual address is stored in
     * the extended starting address field. When this field contains a valid
     * address, ending address must also contain a valid address. When this
     * field contains `0xFFFFFFFF`, ending address must also contain
     * `0xFFFFFFFF`.
     *
     * @since SMBIOS 2.1
     */
    dmi_dword_t start_addr;

    /**
     * @brief Physical ending address of the last kibibyte of a range of
     * addresses mapped to the specified physical memory array.
     *
     * When the field value is `0xFFFFFFFF` and the starting address field
     * also contains FFFF FFFFh, the actual address is stored in the extended
     * ending address field. When this field contains a valid address, starting
     * address must also contain a valid address.
     *
     * @since SMBIOS 2.1
     */
    dmi_dword_t end_addr;

    /**
     * @brief Handle, or instance number, associated with the physical memory
     * array to which this address range is mapped. Multiple address ranges can
     * be mapped to a single physical memory array.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t array_handle;

    /**
     * @brief Number of memory devices that form a single row of memory for the
     * address partition defined by this structure.
     *
     * @since SMBIOS 2.1
     */
    dmi_byte_t partition_width;

    /**
     * @brief Physical address, in bytes, of a range of memory mapped to the
     * specified physical memory array.
     *
     * This field is valid when starting address contains the value
     * `0xFFFFFFFF`. If starting Address contains a value other than
     * `0xFFFFFFFF`, this field contains zeros. When this field contains a
     * valid address, extended ending address must also contain a valid
     * address.
     *
     * @since SMBIOS 2.7
     */
    dmi_qword_t start_addr_ex;

    /**
     * @brief Physical ending address, in bytes, of the last of a range of
     * addresses mapped to the specified physical memory array.
     *
     * This field is valid when both starting address and ending address
     * contain the value `0xFFFFFFFF`. If ending address contains a value other
     * than `0xFFFFFFFF`, this field contains zeros. When this field contains a
     * valid address, extended starting address must also contain a valid
     * address.
     *
     * @since SMBIOS 2.7
     */
    dmi_qword_t end_addr_ex;
};

struct dmi_memory_array_addr
{
    /**
     * @brief Physical address, in bytes, of a range of memory mapped to the
     * specified physical memory array.
     */
    dmi_size_t start_addr;

    /**
     * @brief Physical ending address, in bytes, of the last of a range of
     * addresses mapped to the specified physical memory array.
     */
    dmi_size_t end_addr;

    /**
     * @brief Address range size in bytes.
     */
    dmi_size_t range_size;

    /**
     * @brief Handle, or instance number, associated with the physical memory
     * array to which this address range is mapped. Multiple address ranges can
     * be mapped to a single physical memory array.
     */
    dmi_handle_t array_handle;

    /**
     * @brief Reference to the physical memory array to which this address
     * range is mapped. Multiple address ranges can be mapped to a single
     * physical memory array.
     */
    dmi_entity_t *array;

    /**
     * @brief Number of memory devices that form a single row of memory for the
     * address partition defined by this structure.
     */
    int partition_width;
};

/**
 * @brief Memory array mapped address entity specification.
 */
extern const dmi_entity_spec_t dmi_memory_array_addr_spec;

__BEGIN_DECLS

/**
 * @internal
 */
bool dmi_memory_array_addr_validate(const dmi_entity_t *entity);

/**
 * @internal
 */
dmi_memory_array_addr_t *dmi_memory_array_addr_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
bool dmi_memory_array_addr_link(dmi_entity_t *entity);

/**
 * @internal
 */
void dmi_memory_array_addr_free(dmi_memory_array_addr_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_MEMORY_ARRAY_ADDR_H
