//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_IPMI_DEVICE_H
#define OPENDMI_TABLE_IPMI_DEVICE_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_IPMI_DEVICE_DATA_T
#define DMI_IPMI_DEVICE_DATA_T
typedef struct dmi_ipmi_device_data dmi_ipmi_device_data_t;
#endif // !DMI_IPMI_DEVICE_DATA_T

#ifndef DMI_IPMI_DEVICE_T
#define DMI_IPMI_DEVICE_T
typedef struct dmi_ipmi_device dmi_ipmi_device_t;
#endif // !DMI_IPMI_DEVICE_T

enum dmi_bmc_interface
{
    DMI_BMC_INTERFACE_UNKNOWN = 0x00, ///< Unknown
    DMI_BMC_INTERFACE_KCS     = 0x01, ///< KCS: Keyboard Controller Style
    DMI_BMC_INTERFACE_SMIC    = 0x02, ///< SMIC: Server Management Interface Chip
    DMI_BMC_INTERFACE_BT      = 0x03, ///< BT: Block Transfer
    DMI_BMC_INTERFACE_SSIF    = 0x04, ///< SSIF: SMBus System Interface
};

/**
 * @brief IPMI device information table (type 38).
 * 
 * The information in this structure defines the attributes of an Intelligent
 * Platform Management Interface (IPMI) Baseboard Management Controller (BMC).
 * See the Intelligent Platform Management Interface (IPMI) Interface
 * Specification for full documentation of IPMI and additional information on
 * the use of this structure.
 * 
 * The type 42 structure can also be used to describe a physical management
 * controller host interface and one or more protocols that share that
 * interface. If IPMI is not shared with other protocols, either the type 38
 * or the type 42 structures can be used. Providing Type 38 is recommended for
 * backward compatibility.
 */
DMI_PACKED_STRUCT(dmi_ipmi_device_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Baseboard Management Controller (BMC) interface type.
     */
    dmi_byte_t interface_type;

    /**
     * @brief IPMI specification revision, in BCD format, to which the BMC was
     * designed. Bits 7:4 hold the most significant digit of the revision,
     * while bits 3:0 hold the least significant bits. Example: A value of 0x10
     * indicates revision 1.0.
     */
    dmi_byte_t ipmi_revision;

    /**
     * @brief Target address on the I2C bus of this BMC.
     */
    uint8_t i2c_target_addr;

    /**
     * @brief Bus ID of the NV storage device If no storage device exists for
     * this BMC, the field is set to 0xFF.
     */
    uint8_t nv_storage_addr;

    /**
     * @brief Base address (either memory-mapped or I/O) of the BMC. If the
     * least-significant bit of the field is a 1, the address is in I/O space.
     * Otherwise, the address is memory-mapped. See the IPMI Interface
     * Specification for usage details.
     */
    dmi_qword_t base_addr;

    DMI_PACKED_STRUCT()
    {
        dmi_byte_t interrupt_info : 4;
        dmi_byte_t base_addr_modifier : 4;
    };

    /**
     * @brief Interrupt number for IPMI System Interface. Zero means that IPMI
     * interrupt is unspecified or unsupported.
     */
    dmi_byte_t interrupt_number;
};

/**
 * @brief IPMI device information table specification.
 */
extern const dmi_table_spec_t dmi_ipmi_device_table;

#endif // !OPENDMI_TABLE_IPMI_DEVICE_H
