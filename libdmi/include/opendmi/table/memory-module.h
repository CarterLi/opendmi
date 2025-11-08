//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_MODULE_H
#define OPENDMI_TABLE_MEMORY_MODULE_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_MEMORY_MODULE_DATA_T
#define DMI_MEMORY_MODULE_DATA_T
typedef struct dmi_memory_module_data dmi_memory_module_data_t;
#endif // !DMI_MEMORY_MODULE_DATA_T

#ifndef DMI_MEMORY_MODULE_T
#define DMI_MEMORY_MODULE_T
typedef struct dmi_memory_module dmi_memory_module_t;
#endif // !DMI_MEMORY_MODULE_T

struct dmi_memory_module_data
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief String number for reference designation. Example: "J202".
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

    dmi_word_t current_type;

    dmi_byte_t installed_size;

    dmi_byte_t enabled_size;

    dmi_byte_t error_status;
};

/**
 * @brief Memory module information table specification.
 */
extern const dmi_table_spec_t dmi_memory_module_table;

#endif // !OPENDMI_TABLE_MEMORY_MODULE_H
