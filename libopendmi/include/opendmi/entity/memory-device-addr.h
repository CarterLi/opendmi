//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MEMORY_DEVICE_ADDR_H
#define OPENDMI_ENTITY_MEMORY_DEVICE_ADDR_H

#pragma once

#include <opendmi/entity.h>

/**
 * @brief Memory device mapped address structure (type 20).
 * @since SMBIOS 2.1
 */
DMI_PACKED_STRUCT(dmi_memory_device_addr_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Physical address, in kibibytes, of a range of memory mapped to
     * the referenced memory device.
     *
     * When the field value is FFFF FFFFh the actual address is stored in the
     * extended starting address field. When this field contains a valid
     * address, ending address must also contain a valid address. When this
     * field contains `0xFFFFFFFF`, ending address must also contain
     * `0xFFFFFFFF`.
     *
     * @since SMBIOS 2.1
     */
    dmi_dword_t start_addr;

    /**
     * @brief Physical ending address of the last kibibyte of a range of
     * addresses mapped to the referenced memory device.
     *
     * When the field value is `0xFFFFFFFF` the actual address is stored in the
     * extended ending address field. When this field contains a valid address,
     * starting address must also contain a valid address.
     *
     * @since SMBIOS 2.1
     */
    dmi_dword_t end_addr;

    /**
     * @brief Handle, or instance number, associated with the memory device
     * structure to which this address range is mapped Multiple address ranges
     * can be mapped to a single memory device.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t device_handle;

    /**
     * @brief Handle, or instance number, associated with the memory array
     * mapped address structure to which this device address range is mapped.
     * Multiple address ranges can be mapped to a single memory array mapped
     * address.
     *
     * @since SMBIOS 2.1
     */
    dmi_handle_t array_addr_handle;

    /**
     * @brief Position of the referenced memory device in a row of the address
     * partition. For example, if two 8-bit devices form a 16-bit row, this
     * field's value is either 1 or 2. The value 0 is reserved. If the position
     * is unknown, the field contains 0xFF.
     *
     * @since SMBIOS 2.1
     */
    dmi_byte_t partition_pos;

    /**
     * @brief Position of the referenced memory device in an interleave. The
     * value 0 indicates non-interleaved, 1 indicates first interleave
     * position, 2 the second interleave position, and so on. If the position
     * is unknown, the field contains `0xFF`.
     *
     * Examples: In a 2:1 interleave, the value 1 indicates the device in the
     * "even" position. In a 4:1 interleave, the value 1 indicates the first
     * of four possible positions.
     *
     * @since SMBIOS 2.1
     */
    dmi_byte_t interleave_pos;

    /**
     * @brief Maximum number of consecutive rows from the referenced memory
     * device that are accessed in a single interleaved transfer. If the device
     * is not part of an interleave, the field contains 0; if the interleave
     * configuration is unknown, the value is `0xFF`.
     *
     * Examples: If a device transfers two rows each time it is read, its
     * interleaved data depth is set to 2. If that device is 2:1 interleaved
     * and in interleave position 1, the rows mapped to that device are 1, 2,
     * 5, 6, 9, 10, and so on.
     *
     * @since SMBIOS 2.1
     */
    dmi_byte_t interleave_depth;

    /**
     * @brief Physical address, in bytes, of a range of memory mapped to the
     * referenced memory device.
     *
     * This field is valid when starting address contains the value
     * `0xFFFFFFFF`. If starting address contains a value other than
     * `0xFFFFFFFF`, this field contains zeros. When this field contains a
     * valid address, extended ending address must also contain a valid
     * address.
     *
     * @since SMBIOS 2.7
     */
    dmi_qword_t start_addr_ex;

    /**
     * @brief Physical ending address, in bytes, of the last of a range of
     * addresses mapped to the referenced memory device.
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

typedef struct dmi_memory_device_addr_data dmi_memory_device_addr_data_t;

struct dmi_memory_device_addr
{
    /**
     * @brief Physical address, in bytes, of a range of memory mapped to the
     * referenced memory device.
     */
    dmi_size_t start_addr;

    /**
     * @brief Physical ending address, in bytes, of the last of a range of
     * addresses mapped to the referenced memory device.
     */
    dmi_size_t end_addr;

    /**
     * @brief Address range size in bytes.
     */
    dmi_size_t range_size;

    /**
     * @brief Handle, or instance number, associated with the memory device
     * structure to which this address range is mapped Multiple address ranges
     * can be mapped to a single memory device.
     */
    dmi_handle_t device_handle;

    /**
     * @brief Reference to he memory device structure to which this address
     * range is mapped Multiple address ranges can be mapped to a single memory
     * device.
     */
    dmi_entity_t *device;

    /**
     * @brief Handle, or instance number, associated with the memory array
     * mapped address structure to which this device address range is mapped.
     * Multiple address ranges can be mapped to a single memory array mapped
     * address.
     */
    dmi_handle_t array_addr_handle;

    /**
     * @brief Reference to the memory array mapped address structure to which
     * this device address range is mapped. Multiple address ranges can be
     * mapped to a single memory array mapped address.
     */
    dmi_entity_t *array_addr;

    /**
     * @brief Position of the referenced memory device in a row of the address
     * partition. For example, if two 8-bit devices form a 16-bit row, this
     * field's value is either 1 or 2. The value 0 is reserved. If the position
     * is unknown, the field contains `USHRT_MAX`.
     */
    unsigned short partition_pos;

    /**
     * @brief Position of the referenced memory device in an interleave. The
     * value 0 indicates non-interleaved, 1 indicates first interleave
     * position, 2 the second interleave position, and so on. If the position
     * is unknown, the field contains `USHRT_MAX`.
     *
     * Examples: In a 2:1 interleave, the value 1 indicates the device in the
     * "even" position. In a 4:1 interleave, the value 1 indicates the first
     * of four possible positions.
     */
    unsigned short interleave_pos;

    /**
     * @brief Maximum number of consecutive rows from the referenced memory
     * device that are accessed in a single interleaved transfer. If the device
     * is not part of an interleave, the field contains 0; if the interleave
     * configuration is unknown, the value is `USHRT_MAX`.
     */
    unsigned short interleave_depth;
};

typedef struct dmi_memory_device_addr dmi_memory_device_addr_t;

/**
 * @brief Memory device mapped address entity specification.
 */
extern const dmi_entity_spec_t dmi_memory_device_addr_spec;

__BEGIN_DECLS

/**
 * @internal
 */
bool dmi_memory_device_addr_validate(const dmi_entity_t *entity);

/**
 * @internal
 */
dmi_memory_device_addr_t *dmi_memory_device_addr_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
bool dmi_memory_device_addr_link(dmi_entity_t *entity);

/**
 * @internal
 */
void dmi_memory_device_addr_free(dmi_memory_device_addr_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_MEMORY_DEVICE_ADDR_H
