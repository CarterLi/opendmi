//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_DEVICE_H
#define OPENDMI_TABLE_MEMORY_DEVICE_H

#pragma once

#include <opendmi/table/memory.h>

/**
 * @brief Memory device table specification.
 */
extern const dmi_table_spec_t dmi_memory_device_table;

/**
 * @brief Memory device mapped address table specification.
 */
extern const dmi_table_spec_t dmi_memory_device_addr_table;

#endif // !OPENDMI_TABLE_MEMORY_DEVICE_H
