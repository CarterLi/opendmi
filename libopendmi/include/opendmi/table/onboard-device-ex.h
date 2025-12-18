//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_ONBOARD_DEVICE_EX_H
#define OPENDMI_TABLE_ONBOARD_DEVICE_EX_H

#pragma once

#include <opendmi/table/common.h>
#include <opendmi/table/onboard-device.h>

#ifndef DMI_ONBOARD_DEVICE_EX_T
#define DMI_ONBOARD_DEVICE_EX_T
typedef struct dmi_onboard_device_ex dmi_onboard_device_ex_t;
#endif // !DMI_ONBOARD_DEVICE_EX_T

#ifndef DMI_ONBOARD_DEVICE_EX_DATA_T
#define DMI_ONBOARD_DEVICE_EX_DATA_T
typedef struct dmi_onboard_device_ex_data dmi_onboard_device_ex_data_t;
#endif // !DMI_ONBOARD_DEVICE_EX_DATA_T

/**
 * @brief Onboard devices extended information table (type 41).
 */
DMI_PACKED_STRUCT(dmi_onboard_device_ex_data)
{
    /**
     * @brief DMI structure header.
     */
    dmi_header_t header;

    /**
     * @brief String number of the onboard device reference designation.
     */
    dmi_string_t designator;

    /**
     * @brief Device type and status;
     */
    dmi_byte_t details;

    /**
     * @brief Device type instance. An unique value (within a given onboard
     * device type) used to indicate the order the device is designated by the
     * system.
     * 
     * For example, a system with two identical ethernet NICs may designate one
     * NIC (with higher Bus/Device/Function=15/0/0) as the first onboard NIC
     * (instance 1) and the other NIC (with lower Bus/Device/Function = 3/0/0)
     * as the second onboard NIC (instance 2).
     */
    dmi_byte_t instance;

    /**
     * @brief Device address.
     */
    dmi_pci_addr_data_t address;
};

/**
 * @brief Onboard devices extended information.
 */
struct dmi_onboard_device_ex
{
    /**
     * @brief Device reference designator.
     */
    const char *designator;

    /**
     * @brief Device type.
     */
    dmi_onboard_device_type_t type;

    /**
     * @brief Set to `true` if device is enabled.
     */
    bool is_enabled;

    /**
     * @brief Device type instance. An unique value (within a given onboard
     * device type) used to indicate the order the device is designated by the
     * system.
     * 
     * For example, a system with two identical ethernet NICs may designate one
     * NIC (with higher Bus/Device/Function=15/0/0) as the first onboard NIC
     * (instance 1) and the other NIC (with lower Bus/Device/Function = 3/0/0)
     * as the second onboard NIC (instance 2).
     */
    unsigned short instance;

    /**
     * @brief Device address.
     */
    dmi_pci_addr_t address;
};

/**
 * @brief Onboard devices additional information table specification.
 */
extern const dmi_table_spec_t dmi_onboard_device_ex_table;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_onboard_device_ex_t *dmi_onboard_device_ex_decode(const dmi_table_t *table, dmi_version_t *plevel);

/**
 * @internal
 */
void dmi_onboard_device_ex_free(dmi_onboard_device_ex_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_ONBOARD_DEVICE_EX_H
