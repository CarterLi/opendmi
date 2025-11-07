//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_HARDWARE_SECURITY_H
#define OPENDMI_TABLE_HARDWARE_SECURITY_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Hardware security status values.
 */
typedef enum dmi_hardware_security_status
{
    DMI_HARDWARE_SECURITY_STATUS_DISABLED        = 0x00, ///< Disabled
    DMI_HARDWARE_SECURITY_STATUS_ENABLED         = 0x01, ///< Enabled
    DMI_HARDWARE_SECURITY_STATUS_NOT_IMPLEMENTED = 0x02, ///< Not implemented
    DMI_HARDWARE_SECURITY_STATUS_UNKNOWN         = 0x03, ///< Unknown
} dmi_hardware_security_status_t;

/**
 * @brief Hardware security settings.
 */
DMI_PACKED_STRUCT(dmi_hardware_security_settings)
{
    dmi_byte_t raw_value;

    DMI_PACKED_STRUCT()
    {
        /**
         * @brief front panel reset status.
         */
        dmi_hardware_security_status_t front_panel_reset : 2;

        /**
         * @brief Administrator password status.
         */
        dmi_hardware_security_status_t admin_password : 2;

        /**
         * @brief Keyboard password status.
         */
        dmi_hardware_security_status_t keyboard_password : 2;

        /**
         * @brief Power-on password status.
         */
        dmi_hardware_security_status_t poweron_password : 2;
    };
};

/**
 * @brief Hardware security table (type 24).
 */
DMI_PACKED_STRUCT(dmi_hardware_security_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Hardware security settings.
     */
    struct dmi_hardware_security_settings settings;
};

/**
 * @brief Hardware security table specification.
 */
extern const dmi_table_spec_t dmi_hardware_security_table;

__BEGIN_DECLS

const char *dmi_hardware_security_status_name(enum dmi_hardware_security_status value);

__END_DECLS

#endif // !OPENDMI_TABLE_HARDWARE_SECURITY_H
