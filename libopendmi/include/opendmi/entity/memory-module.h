//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MEMORY_MODULE_H
#define OPENDMI_ENTITY_MEMORY_MODULE_H

#pragma once

#include <opendmi/name.h>
#include <opendmi/entity.h>

#ifndef DMI_MEMORY_MODULE_T
#define DMI_MEMORY_MODULE_T
typedef struct dmi_memory_module dmi_memory_module_t;
#endif // !DMI_MEMORY_MODULE_T

#ifndef DMI_MEMORY_MODULE_DATA_T
#define DMI_MEMORY_MODULE_DATA_T
typedef struct dmi_memory_module_data dmi_memory_module_data_t;
#endif // !DMI_MEMORY_MODULE_DATA_T

#ifndef DMI_MEMORY_MODULE_TYPE_T
#define DMI_MEMORY_MODULE_TYPE_T
typedef union dmi_memory_module_type dmi_memory_module_type_t;
#endif // !DMI_MEMORY_MODULE_TYPE_T

#ifndef DMI_MEMORY_MODULE_ERROR_T
#define DMI_MEMORY_MODULE_ERROR_T
typedef union dmi_memory_module_error dmi_memory_module_error_t;
#endif // !DMI_MEMORY_MODULE_ERROR_T

/**
 * @brief Memory module type details.
 */
DMI_PACKED_UNION(dmi_memory_module_type)
{
    /**
     * @brief Raw value.
     */
    dmi_word_t _value;

    DMI_PACKED_STRUCT()
    {
        bool is_other      : 1; ///< Other
        bool is_unknown    : 1; ///< Unknown
        bool is_standard   : 1; ///< Standard
        bool is_fast_page  : 1; ///< Fast page mode
        bool is_edo        : 1; ///< EDO
        bool has_parity    : 1; ///< Parity
        bool has_ecc       : 1; ///< ECC
        bool is_simm       : 1; ///< SIMM
        bool is_dimm       : 1; ///< DIMM
        bool is_burst_edo  : 1; ///< Burst EDO
        bool is_sdram      : 1; ///< SDRAM

        dmi_word_t reserved : 5;
    };
};

/**
 * @brief Memory module error status.
 */
DMI_PACKED_UNION(dmi_memory_module_error)
{
    dmi_byte_t _value;

    DMI_PACKED_STRUCT()
    {
        /**
         * @brief Uncorrectable errors received for the module, if set. All or
         * a portion of the module has been disabled. This bit is only reset on
         * power-on.
         */
        bool has_uncorrectable : 1;

        /**
         * @brief Correctable errors received for the module, if set. This bit
         * is reset only during a system reset.
         */
        bool has_correctable : 1;

        /**
         * @brief If set, the error status information should be obtained from
         * the event log; bits 1and 0 are reserved.
         */
        bool has_event_log : 1;

        /**
         * @brief Reserved, set to zero.
         */
        dmi_byte_t reserved : 5;
    };
};

/**
 * @brief Memory module information structure (type 6, obsolete).
 */
struct dmi_memory_module_data
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief String number for socket reference designation. Example: "J202".
     */
    dmi_string_t socket;

    /**
     * @brief Each nibble indicates a bank (RAS#) connection. 0x0F means no
     * connection.
     * 
     * Example: If banks 1 & 3 (RAS# 1 & 3) were connected to a SIMM socket
     * the byte for that socket would be 13h. If only bank 2 (RAS 2) were
     * connected, the byte for that socket would be 0x2F.
     */
    dmi_byte_t bank_connections;

    /**
     * @brief Speed of the memory module, in ns (for example, 70 for a 70ns
     * module). If the speed is unknown, the field is set to 0.
     */
    dmi_byte_t current_speed;

    /**
     * @brief The physical characteristics of the memory modules that are
     * supported by (and currently installed in) the system.
     */
    dmi_word_t current_type;

    /**
     * @brief The size of the memory module that is installed in the socket.
     */
    dmi_byte_t installed_size;

    /**
     * @brief The amount of memory currently enabled for the system’s use from
     * the module.
     */
    dmi_byte_t enabled_size;

    /**
     * @brief Error status.
     */
    dmi_byte_t error_status;
};

struct dmi_memory_module
{
    /**
     * @brief Socket reference designator. Example: "202".
     */
    const char *socket;

    /**
     * @brief Each nibble indicates a bank (RAS#) connection. 0x0F means no
     * connection.
     * 
     * Example: If banks 1 & 3 (RAS# 1 & 3) were connected to a SIMM socket
     * the values for that socket would be { 1, 3 }. If only bank 2 (RAS# 2)
     * were connected, the values for that socket would be { USHRT_MAX, 2 }.
     */
    unsigned short bank_connections[2];

    /**
     * @brief Speed of the memory module, in ns (for example, 70 for a 70ns
     * module). If the speed is unknown, the field is set to 0.
     */
    unsigned short current_speed;

    /**
     * @brief The physical characteristics of the memory modules that are
     * supported by (and currently installed in) the system.
     */
    dmi_memory_module_type_t current_type;

    /**
     * @brief The size of the memory module that is installed in the socket.
     */
    dmi_size_t installed_size;

    /**
     * @brief Set to `true` if the installed size is determinable.
     */
    bool has_installed_size;

    /**
     * @brief The amount of memory currently enabled for the system’s use from
     * the module.
     */
    dmi_size_t enabled_size;

    /**
     * @brief Set to `true` if the enabled size is not determinable.
     */
    bool has_enabled_size;

    /**
     * @brief Set to `true`, if a module is known to be installed in a connector,
     * but all memory in the module has been disabled due to error.
     */
    bool is_disabled;

    /**
     * @brief Number of bank connections per module.
     */
    unsigned short bank_count;

    /**
     * @brief Error status.
     */
    dmi_memory_module_error_t error_status;
};

extern const dmi_name_set_t dmi_memory_module_type_names;

/**
 * @brief Memory module information entity specification.
 */
extern const dmi_entity_spec_t dmi_memory_module_spec;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_memory_module_t *dmi_memory_module_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
void dmi_memory_module_free(dmi_memory_module_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_MEMORY_MODULE_H
