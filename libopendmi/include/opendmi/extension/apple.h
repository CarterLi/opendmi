//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_EXTENSION_APPLE_H
#define OPENDMI_EXTENSION_APPLE_H

#pragma once

#include <opendmi/extension.h>

/**
 * @brief Apple SMBIOS structure type identifiers.
 */
enum dmi_apple_type
{
    DMI_TYPE_APPLE_FIRMWARE_VOLUME     = 128, ///< Apple: Firmware volume information
    DMI_TYPE_APPLE_MEMORY_SPD_DATA     = 130, ///< Apple: Memory SPD data
    DMI_TYPE_APPLE_PROCESSOR_TYPE      = 131, ///< Apple: Processor type information
    DMI_TYPE_APPLE_PROCESSOR_BUS_SPEED = 132, ///< Apple: Processor and bus speed information
    DMI_TYPE_APPLE_PLATFORM_FEATURE    = 133, ///< Apple: Platform feature information
    DMI_TYPE_APPLE_SMC_VERSION         = 134  ///< Apple: SMC version information
};

/**
 * @brief Apple DMI extension.
 */
extern const dmi_extension_t dmi_apple_ext;

#endif // !OPENDMI_EXTENSION_APPLE_H
