//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_COMMON_H
#define OPENDMI_TABLE_COMMON_H

#pragma once

#include <opendmi/types.h>

/**
 * @brief Error correction types.
 */
enum dmi_ecc_type
{
    DMI_ECC_TYPE_OTHER      = 0x01, ///< Other
    DMI_ECC_TYPE_UNKNOWN    = 0x02, ///< Unknown
    DMI_ECC_TYPE_NONE       = 0x03, ///< None
    DMI_ECC_TYPE_PARITY     = 0x04, ///< Parity
    DMI_ECC_TYPE_SINGLE_BIT = 0x05, ///< Single-bit ECC
    DMI_ECC_TYPE_MULTI_BIT  = 0x06, ///< Multi-bit ECC
    DMI_ECC_TYPE_CRC        = 0x07, ///< CRC
    __DMI_ECC_TYPE_COUNT
};

__BEGIN_DECLS

const char *dmi_ecc_type_name(enum dmi_ecc_type value);

__END_DECLS

#endif // !OPENDMI_TABLE_COMMON_H
