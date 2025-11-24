//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_TPM_DEVICE_H
#define OPENDMI_TABLE_TPM_DEVICE_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_TPM_DEVICE_DATA_T
#define DMI_TPM_DEVICE_DATA_T
typedef struct dmi_tpm_device_data dmi_tpm_device_data_t;
#endif // !DMI_TPM_DEVICE_DATA_T

#ifndef DMI_TPM_DEVICE_T
#define DMI_TPM_DEVICE_T
typedef struct dmi_tpm_device dmi_tpm_device_t;
#endif // !DMI_TPM_DEVICE_T

/**
 * @brief TPM device table (type 43).
 */
DMI_PACKED_STRUCT(dmi_tpm_device_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Specified as four ASCII characters, as defined by TCG Vendor ID
     * (see CAP_VID in TCG Vendor ID Registry).
     */
    dmi_byte_t vendor_id[4];

    /**
     * @brief Major TPM version supported by the TPM device. For example, the
     * value is `0x01` for TPM v1.2 and is `0x02` for TPM v2.0.
     */
    dmi_byte_t spec_version_major;

    /**
     * @brief Minor TPM version supported by the TPM device. For example, the
     * value is `0x02` for TPM v1.2 and is `0x00` for TPM v2.0.
     */
    dmi_byte_t spec_version_minor;

    /**
     * @brief For major specification version 0x01, this field contains the
     * TPM_VERSION structure defined in the TPM Main Specification, Part 2,
     * Section 5.3. For major specification version 0x02, this field contains
     * the most significant 32 bits of a TPM vendor-specific value for firmware
     * version (see TPM_PT_FIRMWARE_VERSION_1 in TPM Structures specification).
     */
    dmi_dword_t firmware_version_1;

    /**
     * @brief For major specification version 0x01h, this field contains 0x00.
     * For major specification version 0x02, this field contains the least
     * significant 32 bits of a TPM vendor-specific value for firmware
     * version (see TPM_PT_FIRMWARE_VERSION_2 in TPM Structures specification).
     */
    dmi_dword_t firmware_version_2;

    /**
     * @brief String number of descriptive information of the TPM device.
     */
    dmi_string_t description;

    /**
     * @brief TPM device characteristics information.
     */
    dmi_qword_t characteristics;

    /**
     * @brief OEM- or firmware vendor-specific information.
     */
    dmi_dword_t oem_defined;
};

/**
 * @brief TPM device table specification.
 */
extern const dmi_table_spec_t dmi_tpm_device_table;

#endif // !OPENDMI_TABLE_TPM_DEVICE_H
