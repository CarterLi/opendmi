//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_SYSTEM_RESET_H
#define OPENDMI_TABLE_SYSTEM_RESET_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_SYSTEM_RESET_DATA_T
#define DMI_SYSTEM_RESET_DATA_T
typedef struct dmi_system_reset_data dmi_system_reset_data_t;
#endif // !DMI_SYSTEM_RESET_DATA_T

#ifndef DMI_SYSTEM_RESET_T
#define DMI_SYSTEM_RESET_T
typedef struct dmi_system_reset dmi_system_reset_t;
#endif // !DMI_SYSTEM_RESET_T

/**
 * @brief System reset table (type 23).
 */
DMI_PACKED_STRUCT(dmi_system_reset_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Identifies the system-reset capabilities for the system.
     */
    dmi_byte_t capabilities;

    /**
     * @brief Number of automatic system resets since the last intentional
     * reset. A value of `0xFFFF` indicates unknown.
     */
    dmi_word_t reset_count;

    /**
     * @brief Number of consecutive times the system reset is attempted. A value
     * of `0xFFFF` indicates unknown.
     */
    dmi_word_t reset_limit;

    /**
     * @brief Number of minutes to use for the watchdog timer. If the timer is
     * not reset within this interval, the system reset timeout begins. A value
     * of `0xFFFF` indicates unknown.
     */
    dmi_word_t timer_inverval;

    /**
     * @brief Number of minutes before the reboot is initiated. It is used
     * after a system power cycle, system reset (local or remote), and automatic
     * system reset. A value of `0xFFFF` indicates unknown.
     */
    dmi_word_t timeout;
};

/**
 * @brief System reset table specification.
 */
extern const dmi_table_spec_t dmi_system_reset_table;

#endif // !OPENDMI_TABLE_SYSTEM_RESET_H
