//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_SYSTEM_POWER_H
#define OPENDMI_TABLE_SYSTEM_POWER_H

#pragma once

#include <opendmi/table.h>
#include <opendmi/table/common.h>

/**
 * @brief Power supply types.
 */
enum dmi_power_supply_type
{
    DMI_POWER_SUPPLY_TYPE_OTHER     = 0x01, ///< Other
    DMI_POWER_SUPPLY_TYPE_UNKNOWN   = 0x02, ///< Unknown
    DMI_POWER_SUPPLY_TYPE_LINEAR    = 0x03, ///< Linear
    DMI_POWER_SUPPLY_TYPE_SWITCHING = 0x04, ///< Switching
    DMI_POWER_SUPPLY_TYPE_BATTERY   = 0x05, ///< Battery
    DMI_POWER_SUPPLY_TYPE_UPS       = 0x06, ///< UPS
    DMI_POWER_SUPPLY_TYPE_CONVERTER = 0x07, ///< Converter
    DMI_POWER_SUPPLY_TYPE_REGULATOR = 0x08, ///< Regulator
};

/**
 * @brief System power supply table (type 39).
 */
DMI_PACKED_STRUCT(dmi_power_supply_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Power unit group to which this power supply is associated.
     *
     * Specifying the same power unit group value for more than one system
     * power supply structure indicates a redundant power supply configuration.
     * The field's value is 0x00 if the power supply is not a member of a
     * redundant power unit. Non-zero values imply redundancy and that at least
     * one other power supply will be enumerated with the same value.
     */
    dmi_byte_t power_unit_group;

    /**
     * @brief Number of the string that identifies the location of the power
     * supply. Examples: "in the back, on the left-hand side" or "Left supply
     * bay".
     */
    dmi_string_t location;

    /**
     * @brief Number of the string that names the power supply device. Example:
     * "DR-36".
     */
    dmi_string_t name;

    /**
     * @brief Number of the string that names the company that manufactured the
     * supply.
     */
    dmi_string_t manufacturer;

    /**
     * @brief Number of the string that contains the serial number for the
     * power supply.
     */
    dmi_string_t serial_number;

    /**
     * @brief Number of the string that contains the asset tag number.
     */
    dmi_string_t asset_tag;

    /**
     * @brief Number of the string that contains the OEM part order number.
     */
    dmi_string_t part_number;

    /**
     * @brief Power supply revision string. Example: "2.30".
     */
    dmi_string_t revision;

    /**
     * @brief Maximum sustained power output in Watts. Set to 0x8000 if
     * unknown. Note that the units specified by DMTF for this field are
     * milliwatts.
     */
    dmi_word_t maximum_capacity;

    dmi_word_t characteristics;

    /**
     * @brief Handle, or instance number, of a voltage probe (type 26)
     * monitoring this power supply’s input voltage.
     */
    dmi_handle_t input_voltage_probe;

    /**
     * @brief Handle, or instance number, of a cooling device (type 27)
     * associated with this power supply.
     */
    dmi_handle_t cooling_device;

    /**
     * @brief Handle, or instance number, of the electrical current probe
     * (type 29) monitoring this power supply's input current.
     */
    dmi_handle_t input_current_probe;
};

/**
 * @brief System power controls table specification.
 */
extern const dmi_table_spec_t dmi_system_power_controls_table;

/**
 * @brief System power supply table specification.
 */
extern const dmi_table_spec_t dmi_system_power_supply_table;

__BEGIN_DECLS

const char *dmi_power_supply_type_name(enum dmi_power_supply_type value);

__END_DECLS

#endif // !OPENDMI_TABLE_SYSTEM_POWER_H
