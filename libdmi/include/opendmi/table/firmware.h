//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_FIRMWARE_H
#define OPENDMI_TABLE_FIRMWARE_H

#pragma once

#include <opendmi/table.h>

union dmi_firmware_features
{
    uint64_t raw_value;

    struct {
        unsigned int reserved : 2;
        bool unknown : 1;
        bool features_not_supported : 1;
        bool isa_supported : 1;
        bool mca_supported : 1;
        bool eisa_supported : 1;
        bool pci_supported : 1;
        bool pcmcia_supported : 1;
        bool pnp_supported : 1;
        bool apm_supported : 1;
        bool upgradeable : 1;
        bool shadowing_allowed : 1;
        bool vesa_supported : 1;
        bool escd_supported : 1;
        bool boot_cd : 1;
        bool boot_selectable : 1;
        bool socketed : 1;
        bool boot_pcmcia : 1;
        bool edd_supported : 1;
    } __attribute__((packed));
} __attribute__((packed));


/**
 * @brief Platform firmware information table (type 0).
 */
struct dmi_firmware_table
{
    /**
     * @brief DMI structure header.
     */
    dmi_table_header_t header;

    /**
     * @brief String number of the firmware vendor’s name.
     *
     * @since SMBIOS 2.0
     */
    dmi_string_t vendor;

    /**
     * @brief String number of the Firmware Version. This value is a free-form
     * string that may contain Core and OEM version information.
     *
     * @since SMBIOS 2.0
     */
    dmi_string_t version;

    /**
     * @brief Segment location of BIOS starting address (for example, 0xE800).
     * When not applicable, such as on UEFI-based systems, this value is set
     * to 0000h.
     *
     * @note
     * The size of the runtime BIOS image can be computed by subtracting the
     * starting address segment from 0x10000 and multiplying the result by 16.
     *
     * @since SMBIOS 2.0
     */
    uint16_t bios_segment;

    /**
     * @brief String number of the firmware release date. The date string, if
     * supplied, is in either mm/dd/yy or mm/dd/yyyy format. If the year
     * portion of the string is two digits, the year is assumed to be 19yy.
     *
     * @note
     * The mm/dd/yyyy format is required for SMBIOS version 2.3 and later.
     *
     * @since SMBIOS 2.0
     */
    dmi_string_t release_date;

    /**
     * @brief Size (n) where 64 KiB * (n+1) is the size of the physical device
     * containing the platform firmware, in bytes. 0xFF - size is 16MiB or
     * greater, see Extended Firmware ROM Size for actual size.
     *
     * @since SMBIOS 2.0
     */
    uint8_t rom_size;
} __attribute__((packed));

/**
 * @brief Platform firmware information table specification.
 */
extern const struct dmi_table_spec dmi_firmware_table_spec;

#endif // !OPENDMI_TABLE_FIRMWARE_H
