//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_FIRMWARE_INVENTORY_H
#define OPENDMI_TABLE_FIRMWARE_INVENTORY_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Version number formats.
 */
enum dmi_version_format
{
    /**
     * @brief The format is a free-form string that is implementation specific.
     * Example: "1.45.455b66-rev4".
     */
    DMI_VERSION_FORMAT_FREE = 0x00,

    /**
     * @brief The format is "MAJOR.MINOR", where MAJOR and MINOR are decimal
     * string representations of the numeric values of the major/minor version
     * numbers. Example: "1.45"
     */
    DMI_VERSION_FORMAT_SEMANTIC = 0x01,

    /**
     * @brief The format is a C-style hexadecimal string representation of the
     * 32-bit numeric value of the version, in the format of `"0xhhhhhhhh"`.
     * Each `h` represents a hexadecimal digit (0-f). Example: `"0x0001002d"`.
     */
    DMI_VERSION_FORMAT_HEX_32 = 0x02,

    /**
     * @brief The format is a C-style hexadecimal string representation of the
     * 64-bit numeric value of the version, in the format of `"0xhhhhhhhhhhhhhhhh"`.
     * Each `h` represents a hexadecimal digit (0-f). Example: `"0x000000010000002d"`.
     */
    DMI_VERSION_FORMAT_HEX_64 = 0x03
};

/**
 * @enum Firmware identifier formats.
 */
enum dmi_firmware_ident_format
{
    /**
     * @brief The format is a free-form string that is implementation specific.
     * Example: "35EQP72B".
     */
    DMI_FIRMWARE_IDENT_FORMAT_FREE = 0x01,

    /**
     * @brief The format is a string representation of the UEFI ESRT FwClass
     * GUID or the UEFI Firmware Management Protocol ImageTypeId, as defined
     * by the UEFI specification. To represent the GUID, the string is
     * formatted using the 36-character UUID string format specified in
     * RFC4122: `"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"`. Each `x` represents
     * a hexadecimal digit (0-F). Example: `"1624a9df-5e13-47fc-874a-df3aff143089"`.
     */
    DMI_FIRMWARE_IDENT_FORMAT_GUID = 0x02
};

/**
 * @brief Firmware inventory states.
 */
enum dmi_firmware_inventory_state
{
    /**
     * @brief Other.
     */
    DMI_FIRMWARE_INVENTORY_STATE_OTHER = 0x01,

    /**
     * @brief Unknown.
     */
    DMI_FIRMWARE_INVENTORY_STATE_UNKNOWN = 0x02,

    /**
     * @brief Disabled: this firmware component is disabled.
     */
    DMI_FIRMWARE_INVENTORY_STATE_DISABLED = 0x03,

    /**
     * @brief Enabled: this firmware component is enabled.
     */
    DMI_FIRMWARE_INVENTORY_STATE_ENABLED = 0x04,

    /**
     * @brief Absent: this firmware component is either not present or not
     * detected.
     */
    DMI_FIRMWARE_INVENTORY_STATE_ABSENT = 0x05,

    /**
     * @brief Standby offline: this firmware is enabled but awaits an external
     * action to activate it.
     */
    DMI_FIRMWARE_INVENTORY_STATE_STANDBY_OFFLINE = 0x06,

    /**
     * @brief Standby spare: this firmware is part of a redundancy set and
     * awaits a failover or other external action to activate it.
     */
    DMI_FIRMWARE_INVENTORY_STATE_STANDBY_SPARE = 0x07,

    /**
     * @brief Unavailable offline: this firmware component is present but
     * cannot be used.
     */
    DMI_FIRMWARE_INVENTORY_STATE_UNAVAIL_OFFLINE = 0x08
};

/**
 * @brief Firmware inventory information table (type 45).
 */
DMI_PACKED_STRUCT(dmi_firmware_inventory_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief String number of the firmware component name. Example: "BMC
     * Firmware".
     */
    dmi_string_t component_name;

    /**
     * @brief String number of the firmware version of this firmware. The
     * format of this value is defined by the fersion format.
     */
    dmi_string_t version;

    /**
     * @brief Version number format.
     */
    dmi_byte_t version_format;

    /**
     * @brief String number of the firmware identifier of this firmware. The
     * format of this value is defined by the firmware identifier format.
     */
    dmi_string_t ident;

    /**
     * @brief Firmware identifier format.
     */
    dmi_byte_t ident_format;

    /**
     * @brief String number of the firmware release date. The date string, if
     * supplied, follows the date-time values format, as defined in DSP0266.
     * Example: "2021-05-15T04:14:33+06:00", or when the time is unknown or not
     * specified: "2021-05-15T00:00:00Z".
     */
    dmi_string_t release_date;

    /**
     * @brief String number of the manufacturer or producer of this firmware.
     */
    dmi_string_t manufacturer;

    /**
     * @brief String number of the lowest version to which this firmware can
     * be rolled back to. The format of this value is defined by the version
     * format.
     */
    dmi_string_t lowest_version;

    /**
     * @brief Size of the firmware image that is currently programmed in the
     * device, in bytes. If the firmware image size is unknown, the field is
     * set to `0xFFFFFFFFFFFFFFFF`.
     */
    dmi_qword_t image_size;

    /**
     * @brief Firmware characteristics information.
     */
    dmi_word_t characteristics;

    /**
     * @brief Firmware state information.
     */
    dmi_byte_t state;

    /**
     * @brief Defines how many associated component handles are associated with
     * this firmware.
     */
    dmi_byte_t component_count;

    /**
     * @brief Lists the SMBIOS structure handles that are associated with this
     * firmware, if any. Value of number of associated components field (n)
     * defines the count.
     * 
     * @note
     * This list may contain zero or more handles to any SMBIOS structure that
     * represents a device with a firmware component. For example, this may
     * include:
     * 
     * * Type 9 handle (for describing the firmware of a device in a slot).
     * * Type 17 handle (for describing the firmware of a memory device).
     * * Type 41 handle (for describing the firmware of an onboard device).
     * * Type 43 handle (for describing the firmware of a TPM device).
     */
    dmi_handle_t components[];
};

/**
 * @brief Firmware inventory information table specification.
 */
extern const dmi_table_spec_t dmi_firmware_inventory_table;

#endif // !OPENDMI_TABLE_FIRMWARE_INVENTORY_H
