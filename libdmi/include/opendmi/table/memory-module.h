//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_MEMORY_MODULE_H
#define OPENDMI_TABLE_MEMORY_MODULE_H

#pragma once

#include <opendmi/table/memory.h>

struct dmi_memory_module_table
{
    /**
     * @brief DMI table header.
     */
    dmi_table_header_t header;

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
    uint8_t bank_connections;

    /**
     * @brief Speed of the memory module, in ns (for example, 70 for a 70ns
     * module). If the speed is unknown, the field is set to 0.
     */
    uint8_t current_speed;

    uint16_t current_type;

    uint8_t installed_size;

    uint8_t enabled_size;

    uint8_t error_status;
};

/**
 * @brief Memory module information table specification.
 */
extern const dmi_table_spec_t dmi_memory_module_table_spec;

#endif // !OPENDMI_TABLE_MEMORY_MODULE_H
