//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_POWER_CONTROLS_H
#define OPENDMI_ENTITY_POWER_CONTROLS_H

#pragma once

#include <opendmi/entity.h>

/**
 * @brief System power controls structure (type 25).
 *
 * This structure describes the attributes for controlling the main power
 * supply to the system.
 *
 * Software that interprets this structure uses the month, day, hour, minute,
 * and second values to determine the number of seconds until the next power-on
 * of the system. The presence of this structure implies that a timed power-on
 * facility is available for the system.
 */
DMI_PACKED_STRUCT(dmi_power_controls_data)
{
    /**
     * @brief SMBIOS structure header.
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

typedef struct dmi_power_controls_data dmi_power_controls_data_t;

struct dmi_power_controls
{
    /**
     * @brief The month on which the next scheduled power-on is to occur, in
     * the range `1` to `12`.
     */
    unsigned short poweron_month;

    /**
     * @brief The day-of-month on which the next scheduled power-on is to
     * occur, in the range `1` to `31`.
     */
    unsigned short poweron_day;

    /**
     * @brief The hour on which the next scheduled power-on is to occur, in
     * the range `0` to `23`.
     */
    unsigned short poweron_hour;

    /**
     * @brief The minute on which the next scheduled power-on is to occur, in
     * the range `0` to `59`.
     */
    unsigned short poweron_minute;

    /**
     * @brief The second on which the next scheduled power-on is to occur, in
     * the range `0` to `59`.
     */
    unsigned short poweron_second;
};

typedef struct dmi_power_controls dmi_power_controls_t;

/**
 * @brief System power controls entity specification.
 */
extern const dmi_entity_spec_t dmi_power_controls_spec;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_power_controls_t *dmi_power_controls_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
void dmi_power_controls_free(dmi_power_controls_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_POWER_CONTROLS_H
