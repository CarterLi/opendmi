//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MGMT_DEVICE_COMPONENT_H
#define OPENDMI_TABLE_MGMT_DEVICE_COMPONENT_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_MGMT_DEVICE_COMPONENT_DATA_T
#define DMI_MGMT_DEVICE_COMPONENT_DATA_T
typedef struct dmi_mgmt_device_component_data dmi_mgmt_device_component_data_t;
#endif // !DMI_MGMT_DEVICE_COMPONENT_DATA_T

/**
 * @brief Management device component table (type 35).
 */
DMI_PACKED_STRUCT(dmi_mgmt_device_component_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Number of the string that contains additional descriptive
     * information about the component.
     */
    dmi_string_t description;

    /**
     * @brief Handle, or instance number, of the management device that
     * contains this component.
     */
    dmi_handle_t device;

    /**
     * @brief Handle, or instance number, of the probe or cooling device that
     * defines this component.
     */
    dmi_handle_t component;

    /**
     * @brief Handle, or instance number, associated with the device
     * thresholds.
     */
    dmi_handle_t threshold;
};

/**
 * @brief Manangement device component table specification.
 */
extern const dmi_table_spec_t dmi_mgmt_device_component_table;

#endif // !OPENDMI_TABLE_MGMT_DEVICE_COMPONENT_H
