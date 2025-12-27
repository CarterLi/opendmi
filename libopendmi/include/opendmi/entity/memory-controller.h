//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MEMORY_CONTROLLER_H
#define OPENDMI_ENTITY_MEMORY_CONTROLLER_H

#pragma once

#include <opendmi/entity/memory-module.h>

#ifndef DMI_MEMORY_CONTROLLER_T
#define DMI_MEMORY_CONTROLLER_T
typedef struct dmi_memory_controller dmi_memory_controller_t;
#endif // !DMI_MEMORY_CONTROLLER_T

#ifndef DMI_MEMORY_CONTROLLER_DATA_T
#define DMI_MEMORY_CONTROLLER_DATA_T
typedef struct dmi_memory_controller_data dmi_memory_controller_data_t;
#endif // !DMI_MEMORY_CONTROLLER_DATA_T

#ifndef DMI_MEMORY_CONTROLLER_EXTRA_T
#define DMI_MEMORY_CONTROLLER_EXTRA_T
typedef struct dmi_memory_controller_extra dmi_memory_controller_extra_t;
#endif // !DMI_MEMORY_CONTROLLER_EXTRA_T

#ifndef DMI_MEMORY_MODULE_SPEED_T
#define DMI_MEMORY_MODULE_SPEED_T
typedef union dmi_memory_module_speed dmi_memory_module_speed_t;
#endif // !DMI_MEMORY_MODULE_SPEED_T

#ifndef DMI_MEMORY_MODULE_VOLTAGE_T
#define DMI_MEMORY_MODULE_VOLTAGE_T
typedef union dmi_memory_module_voltage dmi_memory_module_voltage_t;
#endif // !DMI_MEMORY_MODULE_VOLTAGE_T

#ifndef DMI_ERROR_CORRECT_CAPS_T
#define DMI_ERROR_CORRECT_CAPS_T
typedef union dmi_error_correct_caps dmi_error_correct_caps_t;
#endif // !DMI_ERROR_CORRECT_CAPS_T

typedef enum dmi_error_detect_method
{
    DMI_ERROR_DETECT_METHOD_UNSPEC  = 0x00, ///< Unspecified
    DMI_ERROR_DETECT_METHOD_OTHER   = 0x01, ///< Other
    DMI_ERROR_DETECT_METHOD_UNKNOWN = 0x02, ///< Unknown
    DMI_ERROR_DETECT_METHOD_NONE    = 0x03, ///< None
    DMI_ERROR_DETECT_METHOD_PARITY  = 0x04, ///< 8-bit Parity
    DMI_ERROR_DETECT_METHOD_ECC_32  = 0x05, ///< 32-bit ECC
    DMI_ERROR_DETECT_METHOD_ECC_64  = 0x06, ///< 64-bit ECC
    DMI_ERROR_DETECT_METHOD_ECC_128 = 0x07, ///< 128-bit ECC
    DMI_ERROR_DETECT_METHOD_CRC     = 0x08, ///< CRC
    __DMI_ERROR_DETECT_METHOD_COUNT
} dmi_error_detect_method_t;

typedef enum dmi_memory_interleave
{
    DMI_MEMORY_INTERLEAVE_UNSPEC  = 0x00, ///< Unspecified
    DMI_MEMORY_INTERLEAVE_OTHER   = 0x01, ///< Other
    DMI_MEMORY_INTERLEAVE_UNKNOWN = 0x02, ///< Unknown
    DMI_MEMORY_INTERLEAVE_1WAY    = 0x03, ///< One-Way Interleave
    DMI_MEMORY_INTERLEAVE_2WAY    = 0x04, ///< Two-Way Interleave
    DMI_MEMORY_INTERLEAVE_4WAY    = 0x05, ///< Four-Way Interleave
    DMI_MEMORY_INTERLEAVE_8WAY    = 0x06, ///< Eight-Way Interleave
    DMI_MEMORY_INTERLEAVE_16WAY   = 0x07, ///< Sixteen-Way Interleave
    __DMI_MEMORY_INTERLEAVE_COUNT
} dmi_memory_interleave_t;

DMI_PACKED_UNION(dmi_error_correct_caps)
{
    /**
     * @brief Raw value.
     */
    dmi_byte_t _value;

    DMI_PACKED_STRUCT()
    {
        bool is_other      : 1; ///< Other
        bool is_unknown    : 1; ///< Unknown
        bool is_none       : 1; ///< None
        bool is_single_bit : 1; ///< Single-bit error correcting
        bool is_double_bit : 1; ///< Double-bit error correcting
        bool is_scrubbing  : 1; ///< Error scrubbing

        dmi_byte_t reserved      : 2; ///< Reserved
    };
};

/**
 * @brief The speed of the memory modules supported by the system.
 */
DMI_PACKED_UNION(dmi_memory_module_speed)
{
    /**
     * @brief Raw value.
     */
    dmi_word_t _value;

    DMI_PACKED_STRUCT()
    {
        bool       is_other   : 1;  ///< Other
        bool       is_unknown : 1;  ///< Unknown
        bool       is_70ns    : 1;  ///< 70 ns
        bool       is_60ns    : 1;  ///< 60 ns
        bool       is_50ns    : 1;  ///< 50 ns
        dmi_word_t reserved   : 11; ///< Reserved
    };
};

/**
 * @brief The required voltages for each of the memory module sockets
 * controlled by this controller. Setting of multiple bits indicates that the
 * sockets are configurable.
 */
DMI_PACKED_UNION(dmi_memory_module_voltage)
{
    /**
     * @brief Raw value.
     */
    dmi_byte_t _value;

    DMI_PACKED_STRUCT()
    {
        bool is_5v : 1;
        bool is_3v3 : 1;
        bool is_2v9 : 1;

        /**
         * @brief Reserved for future use.
         */
        dmi_byte_t reserved : 5;
    };
};

/**
 * @brief Memory controller information structure (type 5, obsolete).
 *
 * The information in this structure defines the attributes of the system's
 * memory controller(s) and the supported attributes of any memory-modules
 * present in the sockets controlled by this controller.
 *
 * @note
 * This structure, and its companion, memory module information (type 6), are
 * obsolete starting with version 2.1 of this specification; the physical
 * memory array (type 16) and memory device (type 17) structures should be used
 * instead. BIOS providers might choose to implement both memory description
 * types to allow existing DMI browsers to properly display the system’s memory
 * attributes.
 */
DMI_PACKED_STRUCT(dmi_memory_controller_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Error detecting method.
     */
    dmi_byte_t error_detection;

    /**
     * @brief Error correcting capabilities.
     */
    dmi_byte_t error_correction;

    /**
     * @brief Supported interleave.
     */
    dmi_byte_t supported_interleave;

    /**
     * @brief Current interleave.
     */
    dmi_byte_t current_interleave;

    /**
     * Size of the largest memory module supported (per slot), specified as
     * `n`, where `2**n` is the maximum size in MiB.
     *
     * The maximum amount of memory supported by this controller is that value
     * times the number of slots, as specified in offset `0Eh` of this
     * structure.
     */
    dmi_byte_t maximum_module_size;

    /**
     * @brief Supported memory module speeds.
     */
    dmi_word_t supported_speeds;

    /**
     * @brief Supported memory module types.
     */
    dmi_word_t supported_types;

    /**
     * @brief Required voltages for each of the memory module sockets
     * controlled by this controller.
     */
    dmi_byte_t required_voltages;

    /**
     * @brief Defines how many of the memory module Information blocks are
     * controlled by this controller.
     */
    dmi_byte_t slot_count;

    /**
     * @brief Lists memory information structure handles controlled by this
     * controller.
     */
    dmi_handle_t module_handles[];
};

/**
 * @since SMBIOS 2.1
 */
DMI_PACKED_STRUCT(dmi_memory_controller_extra)
{
    dmi_byte_t enabled_error_correction;
};

/**
 * @brief Memory controller information.
 */
struct dmi_memory_controller
{
    /**
     * @brief Error detectibg method.
     */
    dmi_error_detect_method_t error_detection;

    /**
     * @brief Error correcting capabilities.
     */
    dmi_error_correct_caps_t error_correction;

    /**
     * @brief Supported interleave.
     */
    dmi_memory_interleave_t supported_interleave;

    /**
     * @brief Current interleave.
     */
    dmi_memory_interleave_t current_interleave;

    /**
     * @brief Size of the largest memory module supported (per slot).
     */
    dmi_size_t maximum_module_size;

    /**
     * @brief Maximum memory size.
     */
    dmi_size_t maximum_memory_size;

    /**
     * @brief Supported memory module speeds.
     */
    dmi_memory_module_speed_t supported_speeds;

    /**
     * @brief Supported memory module types.
     */
    dmi_memory_module_type_t supported_types;

    /**
     * @brief Required voltages for each of the memory module sockets
     * controlled by this controller.
     */
    dmi_memory_module_voltage_t required_voltages;

    /**
     * @brief Memory module slots count.
     */
    size_t slot_count;

    dmi_handle_t *module_handles;

    dmi_entity_t *modules;

    dmi_error_correct_caps_t enabled_error_correction;
};

/**
 * @brief Memory controller information entity specification.
 */
extern const dmi_entity_spec_t dmi_memory_controller_spec;

__BEGIN_DECLS

const char *dmi_error_detect_method_name(dmi_error_detect_method_t value);
const char *dmi_memory_interleave_name(dmi_memory_interleave_t value);

/**
 * @internal
 */
dmi_memory_controller_t *dmi_memory_controller_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
void dmi_memory_controller_free(dmi_memory_controller_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_MEMORY_CONTROLLER_H
