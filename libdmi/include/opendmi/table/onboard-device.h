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

#ifndef DMI_ONBOARD_DEVICE_DATA_T
#define DMI_ONBOARD_DEVICE_DATA_T
typedef struct dmi_onboard_device_data dmi_onboard_device_data_t;
#endif // !DMI_ONBOARD_DEVICE_DATA_T

#ifndef DMI_ONBOARD_DEVICE_T
#define DMI_ONBOARD_DEVICE_T
typedef struct dmi_onboard_device dmi_onboard_device_t;
#endif // !DMI_ONBOARD_DEVICE_T

/**
 * @brief Onboard device types.
 */
enum dmi_onboard_device_type
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
};

/**
 * @brief Onboard devices information table (type 10, obsolette).
 */
DMI_PACKED_STRUCT(dmi_onboard_device_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;
};

/**
 * @brief Onboard devices information table specification.
 */
extern const dmi_table_spec_t dmi_onboard_device_table;

/**
 * @brief Onboard devices additional information table specification.
 */
extern const dmi_table_spec_t dmi_onboard_device_ex_table;

__BEGIN_DECLS

const char *dmi_onboard_device_type_name(enum dmi_onboard_device_type value);

__END_DECLS

#endif // !OPENDMI_TABLE_ONBOARD_DEVICE_H
