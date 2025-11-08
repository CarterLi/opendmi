//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_POWER_CONTROLS_H
#define OPENDMI_TABLE_POWER_CONTROLS_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_POWER_CONTROLS_DATA_T
#define DMI_POWER_CONTROLS_DATA_T
typedef struct dmi_power_controls_data dmi_power_controls_data_t;
#endif // !DMI_POWER_CONTROLS_DATA_T

#ifndef DMI_POWER_CONTROLS_T
#define DMI_POWER_CONTROLS_T
typedef struct dmi_power_controls dmi_power_controls_t;
#endif // !DMI_POWER_CONTROLS_T

/**
 * @brief System power controls table (type 25).
 */
DMI_PACKED_STRUCT(dmi_power_controls_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief BCD value of the month on which the next scheduled power-on is to
     * occur, in the range `0x01` to `0x12`.
     */
    dmi_byte_t poweron_month;

    /**
     * @brief BCD value of the day-of-month on which the next scheduled
     * power-on is to occur, in the range `0x01` to `0x31`.
     */
    dmi_byte_t poweron_day;

    /**
     * @brief BCD value of the hour on which the next scheduled power-on is to
     * occur, in the range `0x00` to `0x23`.
     */
    dmi_byte_t poweron_hour;

    /**
     * @brief BCD value of the minute on which the next scheduled power-on is
     * to occur, in the range `0x00` to `0x59`.
     */
    dmi_byte_t poweron_minute;

    /**
     * @brief BCD value of the second on which the next scheduled power-on is
     * to occur, in the range `0x00` to `0x59`.
     */
    dmi_byte_t poweron_second;
};

/**
 * @brief System power controls table specification.
 */
extern const dmi_table_spec_t dmi_power_controls_table;

#endif // !OPENDMI_TABLE_POWER_CONTROLS_H
