//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_ONBOARD_DEVICE_H
#define OPENDMI_TABLE_ONBOARD_DEVICE_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Onboard device types.
 */
typedef enum dmi_onboard_device_type
{
    DMI_ONBOARD_DEVICE_TYPE_OTHER           = 0x01, ///< Other
    DMI_ONBOARD_DEVICE_TYPE_UNKNOWN         = 0x02, ///< Unknown
    DMI_ONBOARD_DEVICE_TYPE_VIDEO           = 0x03, ///< Video
    DMI_ONBOARD_DEVICE_TYPE_SCSI_CONTROLLER = 0x04, ///< SCSI Controller
    DMI_ONBOARD_DEVICE_TYPE_ETHERNET        = 0x05, ///< Ethernet
    DMI_ONBOARD_DEVICE_TYPE_TOKEN_RING      = 0x06, ///< Token Ring
    DMI_ONBOARD_DEVICE_TYPE_SOUND           = 0x07, ///< Sound
    DMI_ONBOARD_DEVICE_TYPE_PATA_CONTROLLER = 0x08, ///< PATA Controller
    DMI_ONBOARD_DEVICE_TYPE_SATA_CONTROLLER = 0x09, ///< SATA Controller
    DMI_ONBOARD_DEVICE_TYPE_SAS_CONTROLLER  = 0x0A, ///< SAS Controller
} dmi_onboard_device_type_t;

#ifndef DMI_ONBOARD_DEVICE_INSTANCE_DETAILS_T
#define DMI_ONBOARD_DEVICE_INSTANCE_DETAILS_T
typedef union dmi_onboard_device_instance_details dmi_onboard_device_instance_details_t;
#endif // !DMI_ONBOARD_DEVICE_INSTANCE_DETAILS_T

DMI_PACKED_UNION(dmi_onboard_device_instance_details)
{
    /**
     * @brief Raw value.
     */
    dmi_byte_t _value;

    DMI_PACKED_STRUCT()
    {
        /**
         * @brief Device type;
         */
        dmi_byte_t type : 7;

        /**
         * @brief Set to `true` if device is enabled.
         */
        bool is_enabled : 1;
    };
};

#ifndef DMI_ONBOARD_DEVICE_INSTANCE_DATA_T
#define DMI_ONBOARD_DEVICE_INSTANCE_DATA_T
typedef struct dmi_onboard_device_instance_data dmi_onboard_device_instance_data_t;
#endif // !DMI_ONBOARD_DEVICE_INSTANCE_DATA_T

DMI_PACKED_STRUCT(dmi_onboard_device_instance_data)
{
    /**
     * @brief Device type and status.
     */
    dmi_byte_t details;

    /**
     * @brief String number of device description.
     */
    dmi_string_t description;
};

#ifndef DMI_ONBOARD_DEVICE_DATA_T
#define DMI_ONBOARD_DEVICE_DATA_T
typedef struct dmi_onboard_device_data dmi_onboard_device_data_t;
#endif // !DMI_ONBOARD_DEVICE_DATA_T

/**
 * @brief Onboard devices information table (type 10, obsolette).
 *
 * The information in this structure defines the attributes of devices that are
 * onboard (soldered onto) a system element, usually the baseboard. In general,
 * an entry in this table implies that the firmware has some level of control
 * over the enabling of the associated device for use by the system.
 *
 * @note
 * Because this structure was originally defined with the Length implicitly
 * defining the number of devices present, no further fields can be added to
 * this structure without adversely affecting existing software’s ability to
 * properly parse the data. Thus, if additional fields are required for this
 * structure type, a brand-new structure must be defined to add a device
 * count field, carry over the existing fields, and add the new information.
 */
DMI_PACKED_STRUCT(dmi_onboard_device_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Device instances data.
     */
    dmi_onboard_device_instance_data_t instances[];
};

#ifndef DMI_ONBOARD_DEVICE_INSTANCE_T
#define DMI_ONBOARD_DEVICE_INSTANCE_T
typedef struct dmi_onboard_device_instance dmi_onboard_device_instance_t;
#endif // !DMI_ONBOARD_DEVICE_INSTANCE_T

struct dmi_onboard_device_instance
{
    /**
     * @brief Device type.
     */
    dmi_onboard_device_type_t type;

    /**
     * @brief Set to `true` if device is enabled.
     */
    bool is_enabled;

    /**
     * @brief Device description.
     */
    const char *description;
};

#ifndef DMI_ONBOARD_DEVICE_T
#define DMI_ONBOARD_DEVICE_T
typedef struct dmi_onboard_device dmi_onboard_device_t;
#endif // !DMI_ONBOARD_DEVICE_T

struct dmi_onboard_device
{
    /**
     * @brief Number of device instances.
     */
    size_t instance_count;

    /**
     * @brief Device instances.
     */
    dmi_onboard_device_instance_t *instances;
};

/**
 * @brief Onboard devices information table specification.
 */
extern const dmi_table_spec_t dmi_onboard_device_table;

__BEGIN_DECLS

const char *dmi_onboard_device_type_name(enum dmi_onboard_device_type value);

/**
 * @internal
 */
dmi_onboard_device_t *dmi_onboard_device_decode(const dmi_table_t *table);

/**
 * @internal
 */
void dmi_onboard_device_free(dmi_onboard_device_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_ONBOARD_DEVICE_H
