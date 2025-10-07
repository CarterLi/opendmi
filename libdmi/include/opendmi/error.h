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
    DMI_ERROR_INVALID_EPS_LENGTH,   ///< Invalid entry point structure length
    DMI_ERROR_INVALID_EPS_CHECKSUM, ///< Invalid entry point structure checksum
    DMI_ERROR_HANDLE_NOT_FOUND,     ///< Handle not found
    DMI_ERROR_OUT_OF_MEMORY,        ///< Out of memory
    __DMI_ERROR_COUNT
} dmi_error_t;

__BEGIN_DECLS

const char *dmi_error_message(dmi_error_t error);

__END_DECLS

#endif // !OPENDMI_ERROR_H
