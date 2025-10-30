//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MGMT_DEVICE_H
#define OPENDMI_TABLE_MGMT_DEVICE_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Management device table specification.
 */
extern const dmi_table_spec_t dmi_mgmt_device_table;

/**
 * @brief Manangement device component table specification.
 */
extern const dmi_table_spec_t dmi_mgmt_device_component_table;

/**
 * @brief Management device threshold data table specification.
 */
extern const dmi_table_spec_t dmi_mgmt_device_threshold_table;

#endif // !OPENDMI_TABLE_MGMT_DEVICE_H
