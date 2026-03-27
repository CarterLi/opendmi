//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef DMI_ENTITY_INTEL_RSD_PCIE_H
#define DMI_ENTITY_INTEL_RSD_PCIE_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_intel_rsd_pcie dmi_intel_rsd_pcie_t;

/**
 * @brief Intel RSD PCIe information (type 192).
 */
struct dmi_intel_rsd_pcie
{
    /**
     * @brief PCI class code is used to identify the generic function of the
     * device.
     */
    uint8_t pci_class;

    /**
     * @brief The physical slot number of the slot connected to the PCIe port.
     * The slot number shall match the Slot ID field within the SMBIOS System
     * Slots (type 9) attribute structure for the slot this PCIe device is
     * located in.
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
     * @brief Current link speed.
     */
    uint32_t link_speed;

    /**
     * @brief Current link width (1, 2, 4, 8, 16, etc).
     */
    uint32_t link_width;
};

/**
 * @brief Intel RSD PCIe information entity specification.
 */
extern const dmi_entity_spec_t dmi_intel_rsd_pcie_spec;

#endif // !DMI_ENTITY_INTEL_RSD_PCIE_H
