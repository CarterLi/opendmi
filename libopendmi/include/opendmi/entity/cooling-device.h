//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_COOLING_DEVICE_H
#define OPENDMI_ENTITY_COOLING_DEVICE_H

#pragma once

#include <opendmi/entity.h>
#include <opendmi/entity/common.h>

typedef struct dmi_cooling_device      dmi_cooling_device_t;
typedef struct dmi_cooling_device_data dmi_cooling_device_data_t;

/**
 * @brief Cooling device types.
 */
typedef enum dmi_cooling_device_type
{
    DMI_COOLING_DEVICE_TYPE_UNSPEC                   = 0x00, ///< Unspecified
    DMI_COOLING_DEVICE_TYPE_OTHER                    = 0x01, ///< Other
    DMI_COOLING_DEVICE_TYPE_UNKNOWN                  = 0x02, ///< Unknown
    DMI_COOLING_DEVICE_TYPE_FAN                      = 0x03, ///< Fan
    DMI_COOLING_DEVICE_TYPE_CENTRIFUGAL_BLOWER       = 0x04, ///< Centrifugal blower
    DMI_COOLING_DEVICE_TYPE_CHIP_FAN                 = 0x05, ///< Chip fan
    DMI_COOLING_DEVICE_TYPE_CABINET_FAN              = 0x06, ///< Cabinet fan
    DMI_COOLING_DEVICE_TYPE_POWER_SUPPLY_FAN         = 0x07, ///< Power supply fan
    DMI_COOLING_DEVICE_TYPE_HEAT_PIPE                = 0x08, ///< Heat pipe
    DMI_COOLING_DEVICE_TYPE_INTEGRATED_REFRIGERATION = 0x09, ///< Integrated refrigeration
    DMI_COOLING_DEVICE_TYPE_ACTIVE_COOLING           = 0x10, ///< Active cooling
    DMI_COOLING_DEVICE_TYPE_PASSIVE_COOLING          = 0x11, ///< Passive cooling
    __DMI_COOLING_DEVICE_TYPE_COUNT
} dmi_cooling_device_type_t;

/**
 * @brief Cooling device type and status details.
 */
dmi_packed_union(dmi_cooling_device_details)
{
    /**
     * @brief Raw value.
     */
    dmi_byte_t _value;

    dmi_packed_struct()
    {
        /**
         * @brief Cooling device type.
         *
         * @since SMBIOS 2.2
         */
        dmi_byte_t type : 5;

        /**
         * @brief Cooling device status.
         *
         * @since SMBIOS 2.2
         */
        dmi_byte_t status : 3;
    };
};


typedef union dmi_cooling_device_details dmi_cooling_device_details_t;

/**
 * @brief Cooling device structure.
 *
 * This structure describes the attributes for a cooling device in the system.
 * Each structure describes a single cooling device.
 *
 * @since SMBIOS 2.2
 */
dmi_packed_struct(dmi_cooling_device_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Handle, or instance number, of the temperature probe monitoring
     * this cooling device.
     *
     * @since SMBIOS 2.2
     */
    dmi_handle_t probe_handle;

    /**
     * @brief Type and status details.
     */
    dmi_byte_t details;

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
    dmi_byte_t group;

    /**
     * @brief OEM- or firmware vendor-specific information.
     *
     * @since SMBIOS 2.2
     */
    dmi_dword_t oem_defined;

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
    dmi_word_t nominal_speed;

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
};

struct dmi_cooling_device
{
    /**
     * @brief Handle, or instance number, of the temperature probe monitoring
     * this cooling device.
     */
    dmi_handle_t probe_handle;

    /**
     * @brief Reference to the temperature probe monitoring this cooling device.
     */
    dmi_entity_t *probe;

    /**
     * @brief Cooling device type.
     */
    dmi_cooling_device_type_t type;

    /**
     * @brief Cooling device status.
     */
    dmi_status_t status;

    /**
     * @brief Cooling unit group to which this cooling device is associated.
     *
     * Having multiple cooling devices in the same cooling unit implies a
     * redundant configuration. The value is `0` if the cooling device is
     * not a member of a redundant cooling unit. Non-zero values imply
     * redundancy and that at least one other cooling device will be enumerated
     * with the same value.
     */
    short group;

    /**
     * @brief OEM- or firmware vendor-specific information.
     */
    uint32_t oem_defined;

    /**
     * @brief Nominal value for the cooling device’s rotational speed, in
     * revolutions-per-minute (rpm). If the value is unknown or the cooling
     * device is non-rotating, the field is set to `SHRT_MIN`
     */
    short nominal_speed;

    /**
     * @brief Additional descriptive information about the cooling device or
     * its location.
     */
    const char *description;
};

/**
 * @brief Cooling device entity specification.
 */
extern const dmi_entity_spec_t dmi_cooling_device_spec;

__BEGIN_DECLS

const char *dmi_cooling_device_type_name(dmi_cooling_device_type_t value);

/**
 * @internal
 */
dmi_cooling_device_t *dmi_cooling_device_decode(dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
bool dmi_cooling_device_link(dmi_entity_t *entity);

/**
 * @internal
 */
void dmi_cooling_device_free(dmi_cooling_device_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_COOLING_DEVICE_H
