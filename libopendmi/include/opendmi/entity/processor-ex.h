//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_PROCESSOR_EX_H
#define OPENDMI_ENTITY_PROCESSOR_EX_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_processor_ex_data               dmi_processor_ex_data_t;
typedef struct dmi_processor_specific_block        dmi_processor_specific_block_t;
typedef struct dmi_processor_aarch64_data          dmi_processor_aarch64_data_t;
typedef union  dmi_processor_aarch64_data_revision dmi_processor_aarch64_data_revision_t;

typedef enum dmi_processor_arch
{
    DMI_PROCESSOR_ARCH_RESERVED     = 0x00,
    DMI_PROCESSOR_ARCH_IA32         = 0x01, ///< IA32 (x86)
    DMI_PROCESSOR_ARCH_AMD64        = 0x02, ///< x64 (x86-64, Intel64, AMD64, EM64T)
    DMI_PROCESSOR_ARCH_ITANIUM      = 0x03, ///< Intel Itanium architecture
    DMI_PROCESSOR_ARCH_AARCH32      = 0x04, ///< 32-bit ARM (Aarch32)
    DMI_PROCESSOR_ARCH_AARCH64      = 0x05, ///< 64-bit ARM (Aarch64)
    DMI_PROCESSOR_ARCH_RV32         = 0x06, ///< 32-bit RISC-V (RV32)
    DMI_PROCESSOR_ARCH_RV64         = 0x07, ///< 64-bit RISC-V (RV64)
    DMI_PROCESSOR_ARCH_RV128        = 0x08, ///< 128-bit RISC-V (RV128)
    DMI_PROCESSOR_ARCH_LOONG_ARCH32 = 0x09, ///< 32-bit LoongArch (LoongArch32)
    DMI_PROCESSOR_ARCH_LOONG_ARCH64 = 0x0A, ///< 64-bit LoongArch (LoongArch64)
} dmi_processor_arch_t;

/**
 * @brief The Processor-specific Block is the standard container of
 * processor-specific data.
 */
dmi_packed_struct(dmi_processor_specific_block)
{
    /**
     * @brief Length of processor-specific data.
     */
    dmi_byte_t length;

    /**
     * @brief The processor architecture delineated by this
     * processor-specific block.
     */
    dmi_byte_t arch;

    /**
     * @brief Raw processor-specific data.
     */
    dmi_byte_t __data[];
};

/**
 * @brief Processor Additional Information (type 44).
 */
dmi_packed_struct(dmi_processor_ex_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Handle, or instance number, associated with the Processor
     * structure (SMBIOS type 4) which the Processor Additional Information
     * describes.
     */
    dmi_handle_t referenced_handle;

    /**
     * @brief Processor-specific block.
     */
    dmi_processor_specific_block_t block;
};

typedef enum dmi_processor_aarch64_data_subtype
{
    DMI_PROCESSOR_AARCH64_DATA_SUBTYPE_AARCH64          = 0x00, ///< AArch64 Architecture data
    DMI_PROCESSOR_AARCH64_DATA_SUBTYPE_VENDOR_SPECIFIC  = 0x01, ///< Vendor specific data
} dmi_processor_aarch64_data_subtype_t;

/**
 * @brief Revision of the 64-bit Arm (Aarch64) Processor Specific Data.
 */
dmi_packed_union(dmi_processor_aarch64_data_revision)
{
    /**
     * @brief Raw value.
     */
    dmi_word_t __value;

    dmi_packed_struct()
    {
        /**
         * @brief Bits 7:0 Minor revision.
         */
        dmi_byte_t minor;

        /**
         * @brief Bits 15:8 Major revision.
         */
        dmi_byte_t major;
    };
};

/**
 * @brief The 64-bit ARM (Aarch64) processor-specific data.
 */
dmi_packed_struct(dmi_processor_aarch64_data)
{
    /**
     * @brief Revision of the 64-bit Arm (Aarch64) Processor Specific Data.
     */
    dmi_processor_aarch64_data_revision_t revision;

    dmi_byte_t length;

    /**
     * @brief Reserved for future use. Must be zero.
     */
    dmi_byte_t __reserved;

    /**
     * @todo It's a way more complex field.
     */
    dmi_word_t vendor_id;

    dmi_byte_t subtype;

    /**
     * @brief Reserved for future use. Must be zero.
     */
    dmi_byte_t __reserved2;

    dmi_byte_t subtype_specific_data[];
};

dmi_packed_struct(dmi_processor_aarch64_arch_data)
{

};

/**
 * @brief Processor additional information entity specification.
 */
extern const dmi_entity_spec_t dmi_processor_ex_spec;

#endif // !OPENDMI_ENTITY_PROCESSOR_EX_H
