//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef DMI_ENTITY_INTEL_RSD_NETWORK_CARD_H
#define DMI_ENTITY_INTEL_RSD_NETWORK_CARD_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_intel_rsd_network_card dmi_intel_rsd_network_card_t;

struct dmi_intel_rsd_network_card
{
    /**
     * @brief PCI class code is used to identify the generic function of the
     * device.
     */
    uint8_t pci_class;

    /**
     * @brief Physical slot number of the slot connected to the PCIe port.
     */
    uint16_t pci_slot_number;

    /**
     * @brief Vendor identification number.
     */
    uint16_t vendor_id;

    /**
     * @brief Device identification number.
     */
    uint16_t device_id;

    /**
     * @brief Sub-vendor identifier used to differentiate specific model.
     */
    uint16_t sub_vendor_id;

    /**
     * @brief Sub-device identifier used to differentiate specific model.
     */
    uint16_t sub_device_id;

    /**
     * @brief Maximum speed in Mbps (for example 10000 for 10 Gbps, 40000 for
     * 40 Gbps).
     */
    uint32_t maximum_speed;

    /**
     * @brief Current speed in Mbps (for example 10000 for 10 Gbps, 40000 for
     * 40 Gbps).
     */
    uint32_t current_speed;

    /**
     * @brief Port index in the system. This value matches the value exposed by
     * the BIOS in the IPMI specification's device instance selector field
     * definition for `Get/Set System Boot Options` IPMI command (Boot options
     * parameter structure, Boot flags parameter 5 data 5).
     */
    uint16_t port_index;

    /**
     * @brief Network MAC address.
     */
    dmi_data_t mac_address[32];

    /**
     * @brief The string that identifies the version of the firmware installed
     * on the NIC.
     */
    const char *firmware_version;
};

/**
 * @brief Intel RSD network interface card information entity specification.
 */
extern const dmi_entity_spec_t dmi_intel_rsd_network_card_spec;

#endif // !DMI_ENTITY_INTEL_RSD_NETWORK_CARD_H
