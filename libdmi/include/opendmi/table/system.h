//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_SYSTEM_H
#define OPENDMI_TABLE_SYSTEM_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_SYSTEM_DATA_T
#define DMI_SYSTEM_DATA_T
typedef struct dmi_system_data dmi_system_data_t;
#endif // !DMI_SYSTEM_DATA_T

#ifndef DMI_SYSTEM_T
#define DMI_SYSTEM_T
typedef struct dmi_system dmi_system_t;
#endif // !DMI_SYSTEM_T

/**
 * @brief System information table (type 1).
 */
DMI_PACKED_STRUCT(dmi_system_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Manufacturer name.
     */
    dmi_string_t manufacturer;

    /**
     * @brief Product name.
     */
    dmi_string_t product;

    /**
     * @brief Product version.
     */
    dmi_string_t version;

    /**
     * @brief Serial number.
     */
    dmi_string_t serial_number;

    /**
     * @brief UUID number.
     */
    dmi_byte_t uuid[16];

    /**
     * @brief Identifies the event that caused the system to power up.
     */
    dmi_byte_t wakeup_type;

    /**
     * @brief SKU number.
     *
     * This text string identifies a particular computer configuration for
     * sale. It is sometimes also called a product ID or purchase order number.
     * This number is frequently found in existing fields, but there is no
     * standard format. Typically for a given system board from a given OEM,
     * there are tens of unique processor, memory, hard drive, and optical
     * drive configurations.
     */
    dmi_string_t sku_number;

    /**
     * @brief Family name.
     *
     * This text string identifies the family to which a particular computer
     * belongs. A family refers to a set of computers that are similar but not
     * identical from a hardware or software point of view. Typically, a family
     * is composed of different computer models, which have different
     * configurations and pricing points. Computers in the same family often
     * have similar branding and cosmetic features.
     */
    dmi_string_t family;
};

/**
 * @brief System information table specification.
 */
extern const dmi_table_spec_t dmi_system_table;

#endif // !OPENDMI_TABLE_SYSTEM_H
