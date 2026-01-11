//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_COMMON_H
#define OPENDMI_ENTITY_COMMON_H

#pragma once

#include <opendmi/utils/name.h>
#include <opendmi/attribute.h>

typedef struct dmi_pci_addr      dmi_pci_addr_t;
typedef struct dmi_pci_addr_data dmi_pci_addr_data_t;

/**
 * @brief Status types.
 */
typedef enum dmi_status
{
    DMI_STATUS_UNSPEC          = 0x00, ///< Unspecified
    DMI_STATUS_OTHER           = 0x01, ///< Other
    DMI_STATUS_UNKNOWN         = 0x02, ///< Unknown
    DMI_STATUS_OK              = 0x03, ///< OK
    DMI_STATUS_NON_CRITICAL    = 0x04, ///< Non-critical
    DMI_STATUS_CRITICAL        = 0x05, ///< Critical
    DMI_STATUS_NON_RECOVERABLE = 0x06, ///< Non-recoverable
    __DMI_STATUS_COUNT
} dmi_status_t;

/**
 * @brief Error correction types.
 */
typedef enum dmi_error_correct_type
{
    DMI_ERROR_CORRECT_TYPE_UNSPEC      = 0x00, ///< Unspecified
    DMI_ERROR_CORRECT_TYPE_OTHER       = 0x01, ///< Other
    DMI_ERROR_CORRECT_TYPE_UNKNOWN     = 0x02, ///< Unknown
    DMI_ERROR_CORRECT_TYPE_NONE        = 0x03, ///< None
    DMI_ERROR_CORRECT_TYPE_PARITY      = 0x04, ///< Parity
    DMI_ERROR_CORRECT_TYPE_SINGLE_BIT  = 0x05, ///< Single-bit ECC
    DMI_ERROR_CORRECT_TYPE_MULTI_BIT   = 0x06, ///< Multi-bit ECC
    DMI_ERROR_CORRECT_TYPE_CRC         = 0x07, ///< CRC
    __DMI_ERROR_CORRECT_TYPE_COUNT
} dmi_error_correct_type_t;

dmi_packed_struct(dmi_pci_addr_data)
{
    /**
     * @brief Segment group number. The value is 0 for a single-segment topology.
     */
    dmi_word_t segment_group;

    /**
     * @brief Bus number. Set to `0xFF` if not applicable.
     */
    dmi_byte_t bus_number;

    /**
     * @brief Function number. Set to `0x07` if not applicable.
     */
    dmi_byte_t function_number : 3;

    /**
     * @brief Device number. Set to `0x1F` if not applicable.
     */
    dmi_byte_t device_number : 5;
};

struct dmi_pci_addr
{
    /**
     * @brief Segment group. The value is 0 for a single-segment topology.
     */
    uint16_t segment_group;

    /**
     * @brief Bus number. Set to `UINT8_MAX` if not applicable.
     */
    uint8_t bus_number;

    /**
     * @brief Device number. Set to `UINT8_MAX` if not applicable.
     */
    uint8_t device_number;

    /**
     * @brief Function number. Set to `UINT8_MAX` if not applicable.
     */
    uint8_t function_number;
};

extern const dmi_name_set_t dmi_status_names;
extern const dmi_name_set_t dmi_error_correct_type_names;

extern const dmi_attribute_t dmi_pci_addr_attrs[];

__BEGIN_DECLS

const char *dmi_status_name(dmi_status_t value);
const char *dmi_error_correct_type_name(dmi_error_correct_type_t value);

/**
 * @internal
 */
void dmi_pci_addr_decode(dmi_pci_addr_t *addr, const dmi_pci_addr_data_t *data);

__END_DECLS

#endif // !OPENDMI_ENTITY_COMMON_H
