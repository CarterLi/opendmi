//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_CHASSIS_H
#define OPENDMI_TABLE_CHASSIS_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief System enclosure or chassis types.
 */
enum dmi_chassis_type
{
    DMI_CHASSIS_TYPE_OTHER               = 0x01, ///< Other
    DMI_CHASSIS_TYPE_UNKNOWN             = 0x02, ///< Unknown
    DMI_CHASSIS_TYPE_DESKTOP             = 0x03, ///< Desktop
    DMI_CHASSIS_TYPE_LOW_PROFILE_DESKTOP = 0x04, ///< Low-profile desktop
    DMI_CHASSIS_TYPE_PIZZA_BOX           = 0x05, ///< Pizza box
    DMI_CHASSIS_TYPE_MINI_TOWER          = 0x06, ///< Mini tower
    DMI_CHASSIS_TYPE_TOWER               = 0x07, ///< Tower
    DMI_CHASSIS_TYPE_PORTABLE            = 0x08, ///< Portable
    DMI_CHASSIS_TYPE_LAPTOP              = 0x09, ///< Laptop
    DMI_CHASSIS_TYPE_NOTEBOOK            = 0x0A, ///< Notebook
    DMI_CHASSIS_TYPE_HAND_HELD           = 0x0B, ///< Hand held
    DMI_CHASSIS_TYPE_DOCKING_STATION     = 0x0C, ///< Docking station
    DMI_CHASSIS_TYPE_ALL_IN_ONE          = 0x0D, ///< All-in-one
    DMI_CHASSIS_TYPE_SUB_NOTEBOOK        = 0x0E, ///< Sub-notebook
    DMI_CHASSIS_TYPE_SPACE_SAVING        = 0x0F, ///< Space-saving
    DMI_CHASSIS_TYPE_LUNCH_BOX           = 0x10, ///< Lunch box
    DMI_CHASSIS_TYPE_MAIN_SERVER         = 0x11, ///< Main server chassis
    DMI_CHASSIS_TYPE_EXPANSION           = 0x12, ///< Expansion chassis
    DMI_CHASSIS_TYPE_SUB_CHASSIS         = 0x13, ///< Sub-chassis
    DMI_CHASSIS_TYPE_BUS_EXPANSION       = 0x14, ///< Bus expansion chassis
    DMI_CHASSIS_TYPE_PERIPHERAL          = 0x15, ///< Peripheral chassis
    DMI_CHASSIS_TYPE_RAID                = 0x16, ///< RAID chassis
    DMI_CHASSIS_TYPE_RACK_MOUNT          = 0x17, ///< Rack-mount chassis
    DMI_CHASSIS_TYPE_SEALED_CASE_PC      = 0x18, ///< Sealed-case PC
    DMI_CHASSIS_TYPE_MULTI_SYSTEM        = 0x19, ///< Multi-system chassis
    DMI_CHASSIS_TYPE_COMPACT_PCI         = 0x1A, ///< Compact PCI
    DMI_CHASSIS_TYPE_ADVANCED_TCA        = 0x1B, ///< Advanced TCA
    DMI_CHASSIS_TYPE_BLADE               = 0x1C, ///< Blade
    DMI_CHASSIS_TYPE_BLADE_ENCLOSURE     = 0x1D, ///< Blade enclosure
    DMI_CHASSIS_TYPE_TABLET              = 0x1E, ///< Tablet
    DMI_CHASSIS_TYPE_CONVERTIBLE         = 0x1F, ///< Convertible
    DMI_CHASSIS_TYPE_DETACHABLE          = 0x20, ///< Detachable
    DMI_CHASSIS_TYPE_IOT_GATEWAY         = 0x21, ///< IoT gateway
    DMI_CHASSIS_TYPE_EMBEDDED_PC         = 0x22, ///< Embedded PC
    DMI_CHASSIS_TYPE_MINI_PC             = 0x23, ///< Mini PC
    DMI_CHASSIS_TYPE_STICK_PC            = 0x24, ///< Stick PC
};

/**
 * @brief System enclosure or chassis states.
 */
enum dmi_chassis_state
{
    DMI_CHASSIS_STATE_OTHER           = 0x01, ///< Other
    DMI_CHASSIS_STATE_UNKNOWN         = 0x02, ///< Unknown
    DMI_CHASSIS_STATE_SAFE            = 0x03, ///< Safe
    DMI_CHASSIS_STATE_WARNING         = 0x04, ///< Warning
    DMI_CHASSIS_STATE_CRITICAL        = 0x05, ///< Critical
    DMI_CHASSIS_STATE_NON_RECOVERABLE = 0x06, ///< Non-recoverable
};

/**
 * @brief System enclosure or chassis table (type 3).
 * 
 * The information in this structure defines attributes of the system’s
 * mechanical enclosure(s). For example, if a system included a separate
 * enclosure for its peripheral devices, two structures would be returned: one
 * for the main system enclosure and the second for the peripheral device
 * enclosure.
 * 
 * The additions to this structure in version 2.1 of SMBIOS
 * specification support the population of the CIM_Chassis class.
 * 
 * @since SMBIOS 2.0
 */
struct dmi_chassis_data
{
    /**
     * @brief Manufacturer name.
     * @since SMBIOS 2.0
     */
    dmi_string_t manufacturer;

    /**
     * @since SMBIOS 2.0
     */
    dmi_byte_t type;

    /**
     * @since SMBIOS 2.0
     */
    dmi_string_t version;

    /**
     * @since SMBIOS 2.0
     */
    dmi_string_t serial_number;

    /**
     * @since SMBIOS 2.0
     */
    dmi_string_t asset_tag;

    /**
     * @since SMBIOS 2.1
     */
    dmi_byte_t bootup_state;

    /**
     * @since SMBIOS 2.1
     */
    dmi_byte_t power_supply_state;

    /**
     * @since SMBIOS 2.1
     */
    dmi_byte_t thermal_state;

    /**
     * @since SMBIOS 2.1
     */
    dmi_byte_t security_status;

    /**
     * @since SMBIOS 2.3
     */
    dmi_dword_t oem_defined;

    /**
     * @since SMBIOS 2.3
     */
    dmi_byte_t height;

    /**
     * @since SMBIOS 2.3
     */
    dmi_byte_t power_cord_count;

    /**
     * @since SMBIOS 2.3
     */
    dmi_byte_t children_count;

    /**
     * @since SMBIOS 2.3
     */
    dmi_byte_t child_size;
};

/**
 * @brief System enclosure or chasis table specification.
 */
extern const struct dmi_table_spec dmi_chassis_table;

__BEGIN_DECLS

const char *dmi_chassis_type_name(enum dmi_chassis_type value);
const char *dmi_chassis_state_name(enum dmi_chassis_state value);

__END_DECLS

#endif // !OPENDMI_TABLE_CHASSIS_H
