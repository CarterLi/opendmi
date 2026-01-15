//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_EXTENSION_DELL_H
#define OPENDMI_EXTENSION_DELL_H

#pragma once

#include <opendmi/extension.h>

typedef enum dmi_dell_type
{
    DMI_TYPE_DELL_BIOS_FLAGS        = 177, ///< Dell: BIOS flags
    DMI_TYPE_DELL_REVISIONS         = 208, ///< Dell: Revisions and IDs
    DMI_TYPE_DELL_PARALLEL_PORT     = 209, ///< Dell: Parallel port
    DMI_TYPE_DELL_SERIAL_PORT       = 210, ///< Dell: Serial port
    DMI_TYPE_DELL_INFRARED_PORT     = 211, ///< Dell: Infrared port
    DMI_TYPE_DELL_INDEXED_IO        = 212, ///< Dell: Indexed IO
	DMI_TYPE_DELL_PROTECTED_AREA_1  = 214, ///< Dell: Protected area type 1
	DMI_TYPE_DELL_PROTECTED_AREA_2  = 215, ///< Dell: Protected area type 2
	DMI_TYPE_DELL_CALLING_IFACE     = 218  ///< Dell: Calling interface
} dmi_dell_type_t;

/**
 * @brief Dell DMI extension.
 */
extern const dmi_extension_t dmi_dell_ext;

#endif // !OPENDMI_EXTENSION_DELL_H
