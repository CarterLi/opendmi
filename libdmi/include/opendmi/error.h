//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ERROR_H
#define OPENDMI_ERROR_H

#pragma once

#include <opendmi/types.h>

/**
 * @brief DMI error codes
 */
typedef enum dmi_error
{
    DMI_OK,                         ///< Success
    DMI_ERROR_INVALID_ARGUMENT,     ///< Invalid argument
    DMI_ERROR_INVALID_STATE,        ///< Invalid state
    DMI_ERROR_UNKNOWN_EPS_ANCHOR,   ///< Unknown entry point structure anchor
    DMI_ERROR_INVALID_EPS_LENGTH,   ///< Invalid entry point structure length
    DMI_ERROR_INVALID_EPS_CHECKSUM, ///< Invalid entry point structure checksum
    DMI_ERROR_INVALID_TABLE_ADDR,   ///< Invalid table address
    DMI_ERROR_INVALID_TABLE_LENGTH, ///< Invalid table length
    DMI_ERROR_INVALID_TABLE_TYPE,   ///< Invalid table type
    DMI_ERROR_ENTRY_NOT_FOUND,      ///< Entry not found
    DMI_ERROR_NO_MORE_ENTRIES,      ///< No more entries
    DMI_ERROR_OUT_OF_MEMORY,        ///< Out of memory
    DMI_ERROR_SERVICE_UNAVAILABLE,  ///< Service unavailable
    DMI_ERROR_INTERNAL,             ///< Internal error
    __DMI_ERROR_COUNT
} dmi_error_t;

__BEGIN_DECLS

const char *dmi_error_message(dmi_error_t error);

__END_DECLS

#endif // !OPENDMI_ERROR_H
