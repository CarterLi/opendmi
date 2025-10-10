//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_COOLER_H
#define OPENDMI_TABLE_COOLER_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Cooling device types.
 */
typedef enum dmi_cooler_type
{
    DMI_COOLER_TYPE_OTHER                    = 0x01, ///< Other
    DMI_COOLER_TYPE_UNKNOWN                  = 0x02, ///< Unknown
    DMI_COOLER_TYPE_FAN                      = 0x03, ///< Fan
    DMI_COOLER_TYPE_CENTRIFUGAL_BLOWER       = 0x04, ///< Centrifugal blower
    DMI_COOLER_TYPE_CHIP_FAN                 = 0x05, ///< Chip fan
    DMI_COOLER_TYPE_CABINET_FAN              = 0x06, ///< Cabinet fan
    DMI_COOLER_TYPE_POWER_SUPPLY_FAN         = 0x07, ///< Power supply fan
    DMI_COOLER_TYPE_HEAT_PIPE                = 0x08, ///< Heat pipe
    DMI_COOLER_TYPE_INTEGRATED_REFRIGERATION = 0x09, ///< Integrated refrigeration
    DMI_COOLER_TYPE_ACTIVE_COOLING           = 0x10, ///< Active cooling
    DMI_COOLER_TYPE_PASSIVE_COOLING          = 0x11, ///< Passive cooling
    __DMI_COOLER_TYPE_COUNT
} dmi_cooler_type_t;

/**
 * @brief Cooling device status values.
 */
typedef enum dmi_cooler_status
{
    DMI_COOLER_STATUS_OTHER           = 0x01, ///< Other
    DMI_COOLER_STATUS_UNKNOWN         = 0x02, ///< Unknown
    DMI_COOLER_STATUS_OK              = 0x03, ///< OK
    DMI_COOLER_STATUS_NON_CRITICAL    = 0x04, ///< Non-critical
    DMI_COOLER_STATUS_CRITICAL        = 0x05, ///< Critical
    DMI_COOLER_STATUS_NON_RECOVERABLE = 0x06, ///< Non-recoverable
    __DMI_COOLER_STATUS_COUNT
} dmi_cooler_status_t;

/**
 * @brief Cooling device table.
 * 
 * This structure describes the attributes for a cooling device in the system.
 * Each structure describes a single cooling device.
 * 
 * @since SMBIOS 2.2
 */
struct dmi_cooler_table
{
    /**
     * @brief DMI table header.
     */
    dmi_table_header_t header;

    /**
     * @brief Handle, or instance number, of the temperature probe monitoring
     * this cooling device.
     * 
     * @since SMBIOS 2.2
     */
    dmi_handle_t temp_probe;

    struct
    {
        /**
         * @brief Cooling device type.
         * 
         * @since SMBIOS 2.2
         */
        dmi_cooler_type_t type : 5;

        /**
         * @brief Cooling device status.
         * 
         * @since SMBIOS 2.2
         */
        dmi_cooler_status_t status : 3;
    } __attribute__((packed));

    /**
     * @brief Cooling unit group to which this cooling device is associated.
     * 
     * Having multiple cooling devices in the same cooling unit implies a
     * redundant configuration. The value is `0x00` if the cooling device is
     * not a member of a redundant cooling unit. Non-zero values imply
     * redundancy and that at least one other cooling device will be enumerated
     * with the same value.
     * 
     * @since SMBIOS 2.2
     */
    uint8_t group;

    /**
     * @brief OEM- or firmware vendor-specific information.
     * 
     * @since SMBIOS 2.2
     */
    uint32_t oem_defined;

    /**
     * @brief Nominal value for the cooling device’s rotational speed, in
     * revolutions-per-minute (rpm). If the value is unknown or the cooling
     * device is non-rotating, the field is set to `0x8000`.
     * 
     * @note
     * This field is present in the structure only if the structure’s length is
     * larger than `0x0C`.
     * 
     * @since SMBIOS 2.2
     */
    uint16_t nom_speed;

    /**
     * @brief Number of the string that contains additional descriptive
     * information about the cooling device or its location.
     * 
     * @note
     * This field is present in the structure only if the structure's length is
     * `0x0F` or larger.
     * 
     * @since SMBIOS 2.7
     */
    dmi_string_t description;
} __attribute__((packed));

__BEGIN_DECLS

const char *dmi_cooler_type_name(dmi_cooler_type_t value);
const char *dmi_cooler_status_name(dmi_cooler_status_t value);

__END_DECLS

#endif // !OPENDMI_TABLE_COOLER_H
