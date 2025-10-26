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
    __DMI_PROBE_LOCATION_COUNT
} dmi_probe_location_t;

/**
 * @brief Probe status values.
 */
typedef enum dmi_probe_status
{
    DMI_PROBE_STATUS_OTHER           = 0x01, //< Other
    DMI_PROBE_STATUS_UNKNOWN         = 0x02, //< Unknown
    DMI_PROBE_STATUS_OK              = 0x03, //< OK
    DMI_PROBE_STATUS_NON_CRITICAL    = 0x04, //< Non-critical
    DMI_PROBE_STATUS_CRITICAL        = 0x05, //< Critical
    DMI_PROBE_STATUS_NON_RECOVERABLE = 0x06, //< Non-recoverable
    __DMI_PROBE_STATUS_COUNT
} dmi_probe_status_t;

/**
 * @brief Probe table.
 */
struct dmi_probe_table
{
    /**
     * @brief DMI table header.
     */
    dmi_table_header_t header;

    struct {
        /**
         * @brief Physical location.
         */
        dmi_probe_location_t location : 5;

        /**
         * @brief Status.
         */
        dmi_probe_status_t status : 3;
    } __attribute((packed));

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
} __attribute__((packed));

__BEGIN_DECLS

const char *dmi_probe_location_name(dmi_probe_location_t value);
const char *dmi_probe_status_name(dmi_probe_status_t value);

__END_DECLS

#endif // !OPENDMI_TABLE_PROBE_H
