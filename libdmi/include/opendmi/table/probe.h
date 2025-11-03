//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_PROBE_H
#define OPENDMI_TABLE_PROBE_H

#pragma once

#include <opendmi/table.h>
#include <opendmi/table/common.h>

/**
 * @brief Probe locations.
 */
typedef enum dmi_probe_location
{
    DMI_PROBE_LOCATION_OTHER              = 0x01, ///< Other
    DMI_PROBE_LOCATION_UNKNOWN            = 0x02, ///< Unknown
    DMI_PROBE_LOCATION_PROCESSOR          = 0x03, ///< Processor
    DMI_PROBE_LOCATION_DISK               = 0x04, ///< Disk
    DMI_PROBE_LOCATION_PERIPHERAL_BAY     = 0x05, ///< Peripheral bay
    DMI_PROBE_LOCATION_SYSTEM_MGMT_MODULE = 0x06, ///< System management module
    DMI_PROBE_LOCATION_MOTHERBOARD        = 0x07, ///< Motherboard
    DMI_PROBE_LOCATION_MEMORY_MODULE      = 0x08, ///< Memory module
    DMI_PROBE_LOCATION_PROCESSOR_MODULE   = 0x09, ///< Processor module
    DMI_PROBE_LOCATION_POWER_UNIT         = 0x0A, ///< Power unit
    DMI_PROBE_LOCATION_ADDIN_CARD         = 0x0B, ///< Add-in card
    DMI_PROBE_LOCATION_FRONT_PANEL_BOARD  = 0x0C, ///< Front panel board
    DMI_PROBE_LOCATION_BACK_PANEL_BOARD   = 0x0D, ///< Back panel board
    DMI_PROBE_LOCATION_POWER_SYSTEM_BOARD = 0x0E, ///< Power system board
    DMI_PROBE_LOCATION_DRIVE_BACK_PLANE   = 0x0F, ///< Drive back plane
} dmi_probe_location_t;

/**
 * @brief Probe table.
 */
DMI_PACKED_STRUCT(dmi_probe_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    DMI_PACKED_STRUCT() {
        /**
         * @brief Physical location.
         */
        dmi_probe_location_t location : 5;

        /**
         * @brief Status.
         */
        dmi_status_t status : 3;
    };

    /**
     * @brief Maximum value readable by this probe. If the value is unknown,
     * the field is set to `0x8000`.
     */
    uint16_t max_value;

    /**
     * @brief Minimum value readable by this probe. If the value is unknown,
     * the field is set to `0x8000`.
     */
    uint16_t min_value;

    /**
     * @brief Resolution for the probe's reading. If the value is unknown,
     * the field is set to `0x8000`.
     */
    uint16_t resolution;

    /**
     * @brief Tolerance for reading from this probe. If the value is unknown,
     * the field is set to `0x8000`.
     */
    uint16_t tolerance;

    /**
     * @brief Accuracy for reading from this probe. If the value is unknown,
     * the field is set to `0x8000`.
     */
    uint16_t accuracy;

    /**
     * @brief OEM- or firmware vendor-specific information.
     */
    uint32_t oem_defined;

    /**
     * @brief Nominal value for the probe’s reading. If the value is unknown,
     * the field is set to `0x8000`. This field is present in the structure
     * only if the structure’s Length is larger than `0x14`.
     */
    uint16_t nom_value;
};

/**
 * @brief Voltage probe table specification.
 */
extern const dmi_table_spec_t dmi_voltage_probe_table;

/**
 * @brief Temperature probe table specification.
 */
extern const dmi_table_spec_t dmi_temperature_probe_table;

/**
 * @brief Electrical current probe table specification.
 */
extern const dmi_table_spec_t dmi_current_probe_table;

__BEGIN_DECLS

const char *dmi_probe_location_name(dmi_probe_location_t value);

__END_DECLS

#endif // !OPENDMI_TABLE_PROBE_H
