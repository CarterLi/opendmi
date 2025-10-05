//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_DMI_H
#define OPENDMI_DMI_H

#pragma once

#include <sys/cdefs.h>
#include <stdint.h>

/**
 * @brief DMI structure handle, a unique 16-bit number in the range 0 to
 * 0xFFFE (for version 2.0) or 0 to 0xFEFF (for version 2.1 and later). The
 * handle numbers are not required to be contiguous. For version 2.1 and
 * later, handle values in the range 0xFF00 to 0xFFFF are reserved for use
 * by DMI/SMBIOS specification.
 *
 * The UEFI Platform Initialization Specification reserves handle number
 * 0xFFFE for its EFI_SMBIOS_PROTOCOL.Add() function to mean "assign an unused
 * handle number automatically." This number is not used for any other purpose
 * by the SMBIOS specification.
 */
typedef uint16_t dmi_handle_t;

/**
 * @brief DMI structure types identifiers. Types 0 through 127 (7Fh) are
 * reserved for and defined by this specification. Types 128 through 256 (0x80
 * to 0xFF) are available for system- and OEM-specific information.
 */
enum dmi_type
{
    DMI_TYPE_FIRMWARE                  = 0,
    DMI_TYPE_SYSTEM                    = 1,
    DMI_TYPE_BASEBOARD                 = 2,
    DMI_TYPE_SYSTEM_CHASSIS            = 3,
    DMI_TYPE_PROCESSOR                 = 4,
    DMI_TYPE_MEMORY_CONTROLLER         = 5,
    DMI_TYPE_MEMORY_MODULE             = 6,
    DMI_TYPE_CACHE                     = 7,
    DMI_TYPE_PORT_CONNECTOR            = 8,
    DMI_TYPE_SYSTEM_SLOTS              = 9,
    DMI_TYPE_ONBOARD_DEVICE            = 10,
    DMI_TYPE_OEM_STRINGS               = 11,
    DMI_TYPE_SYSTEM_CONFIG_OPTIONS     = 12,
    DMI_TYPE_FIRMWARE_LANGUAGE         = 13,
    DMI_TYPE_GROUP_ASSOC               = 14,
    DMI_TYPE_SYSTEM_EVENT_LOG          = 15,
    DMI_TYPE_MEMORY_ARRAY              = 16,
    DMI_TYPE_MEMORY_DEVICE             = 17,
    DMI_TYPE_MEMORY_ERROR_32           = 18,
    DMI_TYPE_MEMORY_ARRAY_MAPPED_ADDR  = 19,
    DMI_TYPE_MEMORY_DEVICE_MAPPED_ADDR = 20,
    DMI_TYPE_POINTING_DEVICE           = 21,
    DMI_TYPE_PORTABLE_BATTERY          = 22,
    DMI_TYPE_SYSTEM_RESET              = 23,
    DMI_TYPE_HARDWARE_SECURITY         = 24,
    DMI_TYPE_SYSTEM_POWER_CONTROLS     = 25,
    DMI_TYPE_VOLTAGE_PROBE             = 26,
    DMI_TYPE_COOLING_DEVICE            = 27,
    DMI_TYPE_TEMPERATURE_PROBE         = 28,
    DMI_TYPE_CURRENT_PROBE             = 29,
    DMI_TYPE_OOB_REMOTE_ACCESS         = 30,
    DMI_TYPE_BIS_ENTRY_POINT           = 31,
    DMI_TYPE_SYSTEM_BOOT               = 32,
    DMI_TYPE_MEMORY_ERROR_64           = 33,
    DMI_TYPE_MGMT_DEVICE               = 34,
    DMI_TYPE_MGMT_DEVICE_COMPONENT     = 35,
    DMI_TYPE_MGMT_DEVICE_THRESHOLD     = 36,
    DMI_TYPE_MEMORY_CHANNEL            = 37,
    DMI_TYPE_IPMI_DEVICE               = 38,
    DMI_TYPE_SYSTEM_POWER_SUPPLY       = 39,
    DMI_TYPE_ADDITIONAL_INFO           = 40,
    DMI_TYPE_ONBOARD_DEVICE_EX         = 41,
    DMI_TYPE_MGMT_CONTROLLER_HOST_IF   = 42,
    DMI_TYPE_TPM_DEVICE                = 43,
    DMI_TYPE_PROCESSOR_EX              = 44,
    DMI_TYPE_FIRMWARE_INVENTORY        = 45,
    DMI_TYPE_STRING_PROPERTY           = 46,
    DMI_TYPE_INACTIVE                  = 126,
    DMI_TYPE_END_OF_TABLE              = 127
};

/**
 * @brief DMI structure header.
 */
struct dmi_header
{
    /**
     * @brief Specifies the type of structure. Types 0 through 127 (7Fh) are
     * reserved for and defined by this specification. Types 128 through 256
     * (0x80 to 0xFF) are available for system- and OEM-specific information.
     */
    uint8_t type;

    /**
     * @brief Specifies the length of the formatted area of the structure,
     * starting at the Type field. The length of the structure’s string-set is
     * not included.
     */
    uint8_t length;

    /**
     * @brief Specifies the structure’s handle.
     *
     * If the system configuration changes, a previously assigned handle might
     * no longer exist. However, after a handle has been assigned by the
     * platform firmware, the firmware cannot re-assign that handle number to
     * another structure.
     *
     * Unless otherwise specified, when referring to another structure’s
     * handle, the value 0x0FFFF is used to indicate that the referenced handle
     * is not applicable or does not exist.
     *
     * @see dmi_handle_t
     */
    dmi_handle_t handle;
} __attribute__((packed));

__BEGIN_DECLS

const char *dmi_type_name(enum dmi_type id);

__END_DECLS

#endif // !OPENDMI_DMI_H
