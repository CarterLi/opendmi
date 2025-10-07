#include <opendmi/error.h>
//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/error.h>
#include <opendmi/utils.h>

static const char *dmi_error_messages[__DMI_ERROR_COUNT] =
{
    [DMI_OK]                         = "Success",
    [DMI_ERROR_INVALID_ARGUMENT]     = "Invalid argument",
    [DMI_ERROR_INVALID_EPS_LENGTH]   = "Invalid entry point structure length",
    [DMI_ERROR_INVALID_EPS_CHECKSUM] = "Invalid entry point structure checksum",
    [DMI_ERROR_HANDLE_NOT_FOUND]     = "Handle not found",
    [DMI_ERROR_OUT_OF_MEMORY]        = "Out of memory"
};

const char *dmi_error_message(dmi_error_t error)
{
    return dmi_name(dmi_error_messages, error, __DMI_ERROR_COUNT);
}
