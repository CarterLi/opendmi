//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_POINTING_DEVICE_H
#define OPENDMI_ENTITY_POINTING_DEVICE_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_pointing_device_data dmi_pointing_device_data_t;
typedef struct dmi_pointing_device      dmi_pointing_device_t;

/**
 * @brief Pointing device types.
 */
typedef enum dmi_pointing_device_type
{
    DMI_POINTING_DEVICE_TYPE_UNSPEC         = 0x00, ///< Unspecified
    DMI_POINTING_DEVICE_TYPE_OTHER          = 0x01, ///< Other
    DMI_POINTING_DEVICE_TYPE_UNKNOWN        = 0x02, ///< Unknown
    DMI_POINTING_DEVICE_TYPE_MOUSE          = 0x03, ///< Mouse
    DMI_POINTING_DEVICE_TYPE_TRACK_BALL     = 0x04, ///< Track ball
    DMI_POINTING_DEVICE_TYPE_TRACK_POINT    = 0x05, ///< Track point
    DMI_POINTING_DEVICE_TYPE_GLIDE_POINT    = 0x06, ///< Glide point
    DMI_POINTING_DEVICE_TYPE_TOUCH_PAD      = 0x07, ///< Touch pad
    DMI_POINTING_DEVICE_TYPE_TOUCH_SCREEN   = 0x08, ///< Touch screen
    DMI_POINTING_DEVICE_TYPE_OPTICAL_SENSOR = 0x09, ///< Optical sensor
    __DMI_POINTING_DEVICE_TYPE_COUNT
} dmi_pointing_device_type_t;

/**
 * @brief Pointing device interfaces.
 */
typedef enum dmi_pointing_device_interface
{
    DMI_POINTING_DEVICE_INTERFACE_UNSPEC        = 0x00, ///< Unspecified
    DMI_POINTING_DEVICE_INTERFACE_OTHER         = 0x01, ///< Other
    DMI_POINTING_DEVICE_INTERFACE_UNKNOWN       = 0x02, ///< Unknown
    DMI_POINTING_DEVICE_INTERFACE_SERIAL        = 0x03, ///< Serial
    DMI_POINTING_DEVICE_INTERFACE_PS2           = 0x04, ///< PS/2
    DMI_POINTING_DEVICE_INTERFACE_INFRARED      = 0x05, ///< Infrared
    DMI_POINTING_DEVICE_INTERFACE_HP_HIL        = 0x06, ///< HP-HIL
    DMI_POINTING_DEVICE_INTERFACE_BUS_MOUSE     = 0x07, ///< Bus mouse
    DMI_POINTING_DEVICE_INTERFACE_ADB           = 0x08, ///< ADB (Apple Desktop Bus)
    DMI_POINTING_DEVICE_INTERFACE_BUS_MOUSE_DB9 = 0xA0, ///< Bus mouse DB-9
    DMI_POINTING_DEVICE_INTERFACE_BUS_MOUSE_DIN = 0xA1, ///< Bus mouse micro-DIN
    DMI_POINTING_DEVICE_INTERFACE_USB           = 0xA2, ///< USB
    DMI_POINTING_DEVICE_INTERFACE_I2C           = 0xA3, ///< I2C
    DMI_POINTING_DEVICE_INTERFACE_SPI           = 0xA4, ///< SPI
    __DMI_POINTING_DEVICE_INTERFACE_COUNT
} dmi_pointing_device_interface_t;

/**
 * @brief Built-in pointing device structure (type 21).
 */
dmi_packed_struct(dmi_pointing_device_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Type of pointing device.
     */
    dmi_byte_t type;

    /**
     * @brief Interface type for the pointing device.
     */
    dmi_byte_t interface;

    /**
     * @brief Number of buttons on the pointing device. If the device has
     * three buttons, the field value is 0x03.
     */
    dmi_byte_t button_count;
};

struct dmi_pointing_device
{
    /**
     * @brief Type of pointing device.
     */
    dmi_pointing_device_type_t type;

    /**
     * @brief Interface type for the pointing device.
     */
    dmi_pointing_device_interface_t interface;

    /**
     * @brief Number of buttons on the pointing device. If the device has
     * three buttons, the field value is 0x03.
     */
    int button_count;
};

/**
 * @brief Pointing device entity specification.
 * @since SMBIOS 2.1
 */
extern const dmi_entity_spec_t dmi_pointing_device_spec;

__BEGIN_DECLS

const char *dmi_pointing_device_type_name(dmi_pointing_device_type_t value);
const char *dmi_pointing_device_interface_name(dmi_pointing_device_interface_t value);

__END_DECLS

#endif // !OPENDMI_ENTITY_POINTING_DEVICE_H
