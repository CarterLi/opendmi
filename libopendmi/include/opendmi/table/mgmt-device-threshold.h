//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MGMT_DEVICE_THRESHOLD_H
#define OPENDMI_TABLE_MGMT_DEVICE_THRESHOLD_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_MGMT_DEVICE_THRESHOLD_DATA_T
#define DMI_MGMT_DEVICE_THRESHOLD_DATA_T
typedef struct dmi_mgmt_device_threshold_data dmi_mgmt_device_threshold_data_t;
#endif // !DMI_MGMT_DEVICE_THRESHOLD_DATA_T

/**
 * @brief Management device threshold data table (type 36).
 *
 * The information in this structure defines threshold information for a
 * component (probe or cooling-unit) contained within a management device.
 *
 * For each threshold field present in the structure:
 *
 * - The threshold units (millivolts, milliamps, 1/10th degrees C, or RPMs)
 *   are as defined by the associated probe or cooling-unit component structure.
 *
 * - If the value is unavailable, the field is set to `0x8000`.
 */
DMI_PACKED_STRUCT(dmi_mgmt_device_threshold_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Lower non-critical threshold for this component.
     */
    dmi_word_t lower_non_critical;

    /**
     * @brief Upper non-critical threshold for this component.
     */
    dmi_word_t upper_non_critical;

    /**
     * @brief Lower critical threshold for this component.
     */
    dmi_word_t lower_critical;

    /**
     * @brief Upper critical threshold for this component.
     */
    dmi_word_t upper_critical;

    /**
     * @brief Lower non-recoverable threshold for this component.
     */
    dmi_word_t lower_non_recoverable;

    /**
     * @brief Upper non-recoverable threshold for this component.
     */
    dmi_word_t upper_non_recoverable;
};

#ifndef DMI_MGMT_DEVICE_THRESHOLD_T
#define DMI_MGMT_DEVICE_THRESHOLD_T
typedef struct dmi_mgmt_device_threshold dmi_mgmt_device_threshold_t;
#endif // !DMI_MGMT_DEVICE_THRESHOLD_T

struct dmi_mgmt_device_threshold
{
    /**
     * @brief Lower non-critical threshold for this component.
     */
    short lower_non_critical;

    /**
     * @brief Upper non-critical threshold for this component.
     */
    short upper_non_critical;

    /**
     * @brief Lower critical threshold for this component.
     */
    short lower_critical;

    /**
     * @brief Upper critical threshold for this component.
     */
    short upper_critical;

    /**
     * @brief Lower non-recoverable threshold for this component.
     */
    short lower_non_recoverable;

    /**
     * @brief Upper non-recoverable threshold for this component.
     */
    short upper_non_recoverable;
};

/**
 * @brief Management device threshold data table specification.
 */
extern const dmi_table_spec_t dmi_mgmt_device_threshold_table;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_mgmt_device_threshold_t *dmi_mgmt_device_threshold_decode(const dmi_table_t *table, dmi_version_t *plevel);

/**
 * @internal
 */
void dmi_mgmt_device_threshold_free(dmi_mgmt_device_threshold_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_MGMT_DEVICE_THRESHOLD_H
