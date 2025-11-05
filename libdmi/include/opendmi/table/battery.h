//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_BATTERY_H
#define OPENDMI_TABLE_BATTERY_H

#pragma once

#include <opendmi/table.h>

typedef enum dmi_battery_chemistry
{
    DMI_BATTERY_CHEMISTRY_OTHER     = 0x01, ///< Other
    DMI_BATTERY_CHEMISTRY_UNKNOWN   = 0x02, ///< Unknown
    DMI_BATTERY_CHEMISTRY_LEAD_ACID = 0x03, ///< Lead acid
    DMI_BATTERY_CHEMISTRY_NI_CD     = 0x04, ///< Nickel cadmium
    DMI_BATTERY_CHEMISTRY_NI_MH     = 0x05, ///< Nickel metal hyrdide
    DMI_BATTERY_CHEMISTRY_LI_ION    = 0x06, ///< Lithium-ion
    DMI_BATTERY_CHEMISTRY_ZN_AIR    = 0x07, ///< Zinc air
    DMI_BATTERY_CHEMISTRY_LI_PO     = 0x08, ///< Lithium polymer
} dmi_battery_chemistry_t;

/**
 * @brief Portable battery table.
 * 
 * This structure describes the attributes of the portable battery or batteries
 * for the system. The structure contains the static attributes for the group.
 * Each structure describes attributes for a single battery pack.
 */
DMI_PACKED_STRUCT(dmi_battery_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Number of the string that identifies the location of the battery.
     * Example: "in the back, on the left-hand side".
     * 
     * @since SMBIOS 2.1
     */
    dmi_string_t location;

    /**
     * @brief Number of the string that names the company that manufactured the
     * battery.
     * 
     * @since SMBIOS 2.1
     */
    dmi_string_t manufacturer;

    /**
     * @brief Number of the string that identifies the date on which the
     * battery was manufactured.
     * 
     * @note
     * SMBIOS 2.2+ implementations that use a smart battery set this field to
     * `0` (no string) to indicate that the SBDS manufacture date field
     * contains the information.
     * 
     * @since SMBIOS 2.1
     */
    dmi_string_t manufacture_date;

    /**
     * @brief Number of the string that contains the serial number for the
     * battery.
     * 
     * @note
     * SMBIOS 2.2+ implementations that use a smart battery set this field to
     * `0` (no string) to indicate that the SBDS serial number field contains
     * the information.
     * 
     * @since SMBIOS 2.1
     */
    dmi_string_t serial_number;

    /**
     * @brief Number of the string that names the battery device. Example:
     * "DR-36".
     * 
     * @since SMBIOS 2.1
     */
    dmi_string_t name;

    /**
     * @brief The battery chemistry.
     * 
     * @note
     * SMBIOS 2.2+ implementations that use a smart battery set this field to
     * `0x02` (Unknown) to indicate that the SBDS Device Chemistry field
     * contains the information.
     * 
     * @since SMBIOS 2.1
     */
    dmi_battery_chemistry_t chemistry : 8;

    /**
     * @brief Design capacity of the battery in mWatt-hours. If the value is
     * unknown, the field contains `0`.
     * 
     * @note
     * For SMBIOS 2.2+ implementations, this value is multiplied by the design
     * capacity multiplier to produce the actual value.
     * 
     * @since SMBIOS 2.1
     */
    dmi_word_t design_capacity;

    /**
     * @brief Design voltage of the battery in mVolts. If the value is unknown,
     * the field contains `0`.
     * 
     * @since SMBIOS 2.1
     */
    dmi_word_t design_voltage;

    /**
     * @brief Number of the string that contains the Smart Battery Data
     * Specification version number supported by this battery. If the battery
     * does not support the function, no string is supplied.
     * 
     * @since SMBIOS 2.1
     */
    dmi_byte_t sbds_version;

    /**
     * @brief Maximum error (as a percentage in the range 0 to 100) in the
     * Watt-hour data reported by the battery, indicating an upper bound on how
     * much additional energy the battery might have above the energy it
     * reports having. If the value is unknown, the field contains `0xFF`.
     * 
     * @since SMBIOS 2.1
     */
    dmi_byte_t max_error;

    /**
     * @brief 16-bit value that identifies the battery’s serial number.
     * 
     * This value, when combined with the manufacturer, device name, and
     * manufacture date, uniquely identifies the battery. The serial number
     * field must be set to `0` (no string) for this field to be valid.
     * 
     * @since SMBIOS 2.2
     */
    uint16_t sbds_serial_number;

    /**
     * @brief Date the cell pack was manufactured, in packed format.
     * 
     * @since SMBIOS 2.2
     */
    dmi_word_t sbds_manufacture_date;

    /**
     * @brief Number of the string that identifies the battery chemistry (for
     * example, "PbAc"). The device chemistry field must be set to `0x02`
     * (Unknown) for this field to be valid.
     * 
     * @since SMBIOS 2.2
     */
    dmi_string_t sbds_device_chemistry;

    /**
     * @brief Multiplication factor of the Design Capacity value, which
     * assures that the mWatt hours value does not overflow for SBDS
     * implementations.
     * 
     * The multiplier default is `1`, SBDS implementations use the value
     * `10` to correspond to the data as returned from the SBDS Function
     * `0x18`.
     *
     * @since SMBIOS 2.2
     */
    dmi_byte_t design_capacity_factor;

    /**
     * @brief Contains OEM- or firmware vendor-specific information.
     * 
     * @since SMBIOS 2.2
     */
    dmi_dword_t oem_defined;
};

/**
 * @brief Portable battery table specification.
 */
extern const dmi_table_spec_t dmi_battery_table;

__BEGIN_DECLS

const char *dmi_battery_chemistry_name(dmi_battery_chemistry_t value);

__END_DECLS

#endif // !OPENDMI_TABLE_BATTERY_H
