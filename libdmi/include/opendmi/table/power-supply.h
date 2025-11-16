//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_POWER_SUPPLY_H
#define OPENDMI_TABLE_POWER_SUPPLY_H

#pragma once

#include <opendmi/table.h>
#include <opendmi/table/common.h>

/**
 * @brief Power supply types.
 */
typedef enum dmi_power_supply_type
{
    DMI_POWER_SUPPLY_TYPE_OTHER     = 0x01, ///< Other
    DMI_POWER_SUPPLY_TYPE_UNKNOWN   = 0x02, ///< Unknown
    DMI_POWER_SUPPLY_TYPE_LINEAR    = 0x03, ///< Linear
    DMI_POWER_SUPPLY_TYPE_SWITCHING = 0x04, ///< Switching
    DMI_POWER_SUPPLY_TYPE_BATTERY   = 0x05, ///< Battery
    DMI_POWER_SUPPLY_TYPE_UPS       = 0x06, ///< UPS
    DMI_POWER_SUPPLY_TYPE_CONVERTER = 0x07, ///< Converter
    DMI_POWER_SUPPLY_TYPE_REGULATOR = 0x08, ///< Regulator
} dmi_power_supply_type_t;

/**
 * @brief Input voltage range switching types.
 */
typedef enum dmi_range_switching_type
{
    DMI_RANGE_SWITCHING_TYPE_OTHER          = 0x01, ///< Other
    DMI_RANGE_SWITCHING_TYPE_UNKNOWN        = 0x02, ///< Unknown
    DMI_RANGE_SWITCHING_TYPE_MANUAL         = 0x03, ///< Manual
    DMI_RANGE_SWITCHING_TYPE_AUTO           = 0x04, ///< Auto-switch
    DMI_RANGE_SWITCHING_TYPE_WIDE           = 0x05, ///< Wide range
    DMI_RANGE_SWITCHING_TYPE_NOT_APPLICABLE = 0x06, ///< Not applicable
} dmi_range_switching_type_t;

/**
 * @brief Power supply characteristics.
 */
DMI_PACKED_UNION(dmi_power_supply_details)
{
    /**
     * @brief Raw value.
     */
    dmi_word_t _value;

    DMI_PACKED_STRUCT()
    {
        /**
         * @brief Power supply is hot-replaceable.
         */
        bool hot_swappable : 1;

        /**
         * @brief Power supply is present.
         */
        bool present : 1;

        /**
         * @brief Power supply is unplugged from the wall.
         */
        bool unplugged : 1;

        /**
         * @brief Input voltage range switching.
         */
        dmi_range_switching_type_t range_switching : 4;

        /**
         * @brief Status.
         */
        dmi_status_t status : 3;

        /**
         * @brief Power supply type.
         */
        dmi_power_supply_type_t type : 4;

        /**
         * @brief Reserved for future use, set to zero.
         */
        dmi_word_t reserved : 2;
    };
};

#ifndef DMI_POWER_SUPPLY_DETAILS_T
#define DMI_POWER_SUPPLY_DETAILS_T
typedef union dmi_power_supply_details dmi_power_supply_details_t;
#endif // !DMI_POWER_SUPPLY_DETAILS_T

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
    dmi_byte_t group;

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
    dmi_word_t max_capacity;

    /**
     * @brief Power supply characteristics.
     */
    dmi_word_t characteristics;

    /**
     * @brief Handle, or instance number, of a voltage probe (type 26)
     * monitoring this power supply’s input voltage.
     */
    dmi_handle_t voltage_probe_handle;

    /**
     * @brief Handle, or instance number, of a cooling device (type 27)
     * associated with this power supply.
     */
    dmi_handle_t cooling_device_handle;

    /**
     * @brief Handle, or instance number, of the electrical current probe
     * (type 29) monitoring this power supply's input current.
     */
    dmi_handle_t current_probe_handle;
};

#ifndef DMI_POWER_SUPPLY_DATA_T
#define DMI_POWER_SUPPLY_DATA_T
typedef struct dmi_power_supply_data dmi_power_supply_data_t;
#endif // !DMI_POWER_SUPPLY_DATA_T

struct dmi_power_supply
{
    /**
     * @brief Power unit group to which this power supply is associated.
     *
     * Specifying the same power unit group value for more than one system
     * power supply structure indicates a redundant power supply configuration.
     * The field's value is `0` if the power supply is not a member of a
     * redundant power unit. Non-zero values imply redundancy and that at least
     * one other power supply will be enumerated with the same value.
     */
    unsigned short group;

    /**
     * @brief The location of the power supply. Examples: "in the back, on the
     * left-hand side" or "Left supply bay".
     */
    const char *location;

    /**
     * @brief Power supply device name. Example: "DR-36".
     */
    const char *name;

    /**
     * @brief Power supply manufacturer name.
     */
    const char *manufacturer;

    /**
     * @brief Serial number.
     */
    const char *serial_number;

    /**
     * @brief Asset tag number.
     */
    const char *asset_tag;

    /**
     * @brief OEM part order number.
     */
    const char *part_number;

    /**
     * @brief Power supply revision string. Example: "2.30".
     */
    const char *revision;

    /**
     * @brief Maximum sustained power output in Watts. Set to `SHRT_MIN` if
     * unknown. Note that the units specified by DMTF for this field are
     * milliwatts.
     */
    short max_capacity;

    /**
     * @brief Power supply is hot-replaceable.
     */
    bool hot_swappable;

    /**
     * @brief Power supply is present.
     */
    bool present;

    /**
     * @brief Power supply is unplugged from the wall.
     */
    bool unplugged;

    /**
     * @brief Input voltage range switching.
     */
    dmi_range_switching_type_t range_switching;

    /**
     * @brief Status.
     */
    dmi_status_t status;

    /**
     * @brief Power supply type.
     */
    dmi_power_supply_type_t type;

    /**
     * @brief Handle, or instance number, of a voltage probe (type 26)
     * monitoring this power supply’s input voltage.
     */
    dmi_handle_t voltage_probe_handle;

    /**
     * @brief Handle, or instance number, of a cooling device (type 27)
     * associated with this power supply.
     */
    dmi_handle_t cooling_device_handle;

    /**
     * @brief Handle, or instance number, of the electrical current probe
     * (type 29) monitoring this power supply's input current.
     */
    dmi_handle_t current_probe_handle;
};

#ifndef DMI_POWER_SUPPLY_T
#define DMI_POWER_SUPPLY_T
typedef struct dmi_power_supply dmi_power_supply_t;
#endif // !DMI_POWER_SUPPLY_T

/**
 * @brief System power supply table specification.
 */
extern const dmi_table_spec_t dmi_power_supply_table;

__BEGIN_DECLS

const char *dmi_power_supply_type_name(dmi_power_supply_type_t value);
const char *dmi_range_switching_type_name(dmi_range_switching_type_t value);

dmi_power_supply_t *dmi_power_supply_decode(const dmi_table_t *table);
void dmi_power_supply_destroy(dmi_power_supply_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_POWER_SUPPLY_H
