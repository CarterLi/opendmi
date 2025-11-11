//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_COMMON_H
#define OPENDMI_TABLE_COMMON_H

#pragma once

#include <opendmi/name.h>

/**
 * @brief Status types.
 */
typedef enum dmi_status
{
    DMI_STATUS_OTHER           = 0x01, ///< Other
    DMI_STATUS_UNKNOWN         = 0x02, ///< Unknown
    DMI_STATUS_OK              = 0x03, ///< OK
    DMI_STATUS_NON_CRITICAL    = 0x04, ///< Non-critical
    DMI_STATUS_CRITICAL        = 0x05, ///< Critical
    DMI_STATUS_NON_RECOVERABLE = 0x06, ///< Non-recoverable
} dmi_status_t;

/**
 * @brief Error correction types.
 */
typedef enum dmi_ecc_type
{
    DMI_ECC_TYPE_OTHER      = 0x01, ///< Other
    DMI_ECC_TYPE_UNKNOWN    = 0x02, ///< Unknown
    DMI_ECC_TYPE_NONE       = 0x03, ///< None
    DMI_ECC_TYPE_PARITY     = 0x04, ///< Parity
    DMI_ECC_TYPE_SINGLE_BIT = 0x05, ///< Single-bit ECC
    DMI_ECC_TYPE_MULTI_BIT  = 0x06, ///< Multi-bit ECC
    DMI_ECC_TYPE_CRC        = 0x07, ///< CRC
} dmi_ecc_type_t;

extern const dmi_name_t dmi_status_names[];
extern const dmi_name_t dmi_ecc_type_names[];

__BEGIN_DECLS

const char *dmi_status_name(enum dmi_status value);
const char *dmi_ecc_type_name(enum dmi_ecc_type value);

__END_DECLS

#endif // !OPENDMI_TABLE_COMMON_H
