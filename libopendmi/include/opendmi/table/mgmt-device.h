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
 * @brief Management device types.
 */
typedef enum dmi_mgmt_device_type
{
    DMI_MGMT_DEVICE_TYPE_OTHER           = 0x01, ///< Other
    DMI_MGMT_DEVICE_TYPE_UNKNOWN         = 0x02, ///< Unknown
    DMI_MGMT_DEVICE_TYPE_NATIONAL_LM75   = 0x03, ///< National Semiconductor LM75
    DMI_MGMT_DEVICE_TYPE_NATIONAL_LM78   = 0x04, ///< National Semiconductor LM78
    DMI_MGMT_DEVICE_TYPE_NATIONAL_LM79   = 0x05, ///< National Semiconductor LM79
    DMI_MGMT_DEVICE_TYPE_NATIONAL_LM80   = 0x06, ///< National Semiconductor LM80
    DMI_MGMT_DEVICE_TYPE_NATIONAL_LM81   = 0x07, ///< National Semiconductor LM81
    DMI_MGMT_DEVICE_TYPE_ANALOG_ADM9240  = 0x08, ///< Analog Devices ADM9240
    DMI_MGMT_DEVICE_TYPE_DALLAS_DS1780   = 0x09, ///< Dallas Semiconductor DS1780
    DMI_MGMT_DEVICE_TYPE_MAXIM_1617      = 0x0A, ///< Maxim 1617
    DMI_MGMT_DEVICE_TYPE_GENESYS_GL518SM = 0x0B, ///< Genesys GL518SM
    DMI_MGMT_DEVICE_TYPE_WINBOND_W83781D = 0x0C, ///< Winbond W83781D
    DMI_MGMT_DEVICE_TYPE_HOLTEK_HT82H791 = 0x0D, ///< Holtek HT82H791
} dmi_mgmt_device_type_t;

/**
 * @brief Management device address types.
 */
typedef enum dmi_mgmt_device_addr_type
{
    DMI_MGMT_DEVICE_ADDR_TYPE_OTHER   = 0x01, ///< Other
    DMI_MGMT_DEVICE_ADDR_TYPE_UNKNOWN = 0x02, ///< Unknown
    DMI_MGMT_DEVICE_ADDR_TYPE_PORT    = 0x03, ///< I/O port
    DMI_MGMT_DEVICE_ADDR_TYPE_MEMORY  = 0x04, ///< Memory
    DMI_MGMT_DEVICE_ADDR_TYPE_SMBUS   = 0x05, ///< SMBus
} dmi_mgmt_device_addr_type_t;

/**
 * @brief Management device table (type 34).
 */
DMI_PACKED_STRUCT(dmi_mgmt_device_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Number of the string that contains additional descriptive
     * information about the device or its location.
     */
    dmi_string_t description;

    /**
     * @brief Type of the device.
     */
    dmi_byte_t type;

    /**
     * @brief Address of the device.
     */
    dmi_dword_t addr;

    /**
     * @brief Type of addressing used to access the device.
     */
    dmi_byte_t addr_type;
};

#ifndef DMI_MGMT_DEVICE_DATA_T
#define DMI_MGMT_DEVICE_DATA_T
typedef struct dmi_mgmt_device_data dmi_mgmt_device_data_t;
#endif // !DMI_MGMT_DEVICE_DATA_T

struct dmi_mgmt_device
{
    /**
     * @brief String that contains additional descriptive information about the
     * device or its location.
     */
    const char *description;

    /**
     * @brief Type of the device.
     */
    dmi_mgmt_device_type_t type;

    /**
     * @brief Address of the device.
     */
    uint32_t addr;

    /**
     * @brief Type of addressing used to access the device.
     */
    dmi_mgmt_device_addr_type_t addr_type;
};

#ifndef DMI_MGMT_DEVICE_T
#define DMI_MGMT_DEVICE_T
typedef struct dmi_mgmt_device dmi_mgmt_device_t;
#endif // !DMI_MGMT_DEVICE_T

/**
 * @brief Management device table specification.
 */
extern const dmi_table_spec_t dmi_mgmt_device_table;

__BEGIN_DECLS

const char *dmi_mgmt_device_type_name(enum dmi_mgmt_device_type value);
const char *dmi_mgmt_device_addr_type_name(enum dmi_mgmt_device_addr_type value);

/**
 * @internal
 */
dmi_mgmt_device_t *dmi_mgmt_device_decode(const dmi_table_t *table);

/**
 * @internal
 */
void dmi_mgmt_device_free(dmi_mgmt_device_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_MGMT_DEVICE_H
