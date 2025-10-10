//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_BASEBOARD_H
#define OPENDMI_TABLE_BASEBOARD_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief Baseboard type identifiers.
 */
enum dmi_baseboard_type
{
    DMI_BASEBOARD_UNKNOWN                  = 0x01, /**< Unknown */
    DMI_BASEBOARD_OTHER                    = 0x02, /**< Other */
    DMI_BASEBOARD_SERVER_BLADE             = 0x03, /**< Server blade */
    DMI_BASEBOARD_CONNECTIVITY_SWITCH      = 0x04, /**< Connectivity switch */
    DMI_BASEBOARD_SYSTEM_MANAGEMENT_MODULE = 0x05, /**< System management module */
    DMI_BASEBOARD_PROCESSOR_MODULE         = 0x06, /**< Processor module */
    DMI_BASEBOARD_IO_MODULE                = 0x07, /**< IO module */
    DMI_BASEBOARD_MEMORY_MODULE            = 0x08, /**< Memory module */
    DMI_BASEBOARD_DAUGHTERBOARD            = 0x09, /**< Daughterboard */
    DMI_BASEBOARD_MOTHERBOARD              = 0x0A, /**< Motherboard */
    DMI_BASEBOARD_PROCESSOR_MEMORY_MODULE  = 0x0B, /**< Processor/memory module */
    DMI_BASEBOARD_PROCESSOR_IO_MODULE      = 0x0C, /**< Processor/IO module */
    DMI_BASEBOARD_INTERCONNECT_BOARD       = 0x0D, /**< Interconnect board */
    __DMI_BASEBOARD_COUNT
};

/**
 * @brief Baseboard feature flags.
 */
struct dmi_baseboard_features
{
    /**
     * @brief Set to `true` if the board is a hosting board (for example, a
     * motherboard).
     */
    bool hosting_board : 1;

    /**
     * @brief Set to `true` if the board requires at least one daughter board
     * or auxiliary card to function properly.
     */
    bool require_daughter_board : 1;

    /**
     * @brief Set to `true` if the board is removable. It is designed to be
     * taken in and out of the chassis without impairing the function of the
     * chassis.
     */
    bool removable : 1;

    /**
     * @brief Set to `true` if the board is replaceable. It is possible to
     * replace (either as a field repair or as an upgrade) the board with a
     * physically different board. The board is inherently removable.
     */
    bool replaceable : 1;

    /**
     * @brief Set to `true` if the board is hot swappable; it is possible to
     * replace the board with a physically different but equivalent board while
     * power is applied to the board. The board is inherently replaceable and
     * removable.
     */
    bool hot_swappable : 1;

    /**
     * @brief Reserved for future definition by SMBIOS specification, set to 0.
     */
    uint8_t reserved : 3;
} __attribute__((packed));

/**
 * @brief Baseboard or module information table (type 2).
 * 
 * The information in this structure defines attributes of a system baseboard
 * (for example, a motherboard, planar, server blade, or other standard system
 * module).
 * 
 * @note
 * If more than one type 2 structure is provided by an SMBIOS implementation,
 * each structure shall include the Number of Contained Object Handles and
 * Contained Object Handles fields to specify which system elements are
 * contained on which boards. If a single type 2 structure is provided and the
 * contained object information is not present, or if no type 2 structure is
 * provided, all system elements identified by the SMBIOS implementation are
 * associated with a single motherboard.
 */
struct dmi_baseboard_table
{
    struct dmi_table_header header;
    dmi_string_t manufacturer;
    dmi_string_t product;
    dmi_string_t version;
    dmi_string_t serial_number;
    dmi_string_t asset_tag;
    struct dmi_baseboard_features features;
    dmi_string_t location;
    dmi_handle_t chassis_handle;
    enum dmi_baseboard_type type;
    uint8_t children_count;
    dmi_handle_t children_handles[0];
} __attribute__((packed));

struct dmi_baseboard
{
    char *manufacturer;
    char *product;
    char *version;
    char *serial_number;
    char *asset_tag;
    struct dmi_baseboard_features features;
    char *location;
};

__BEGIN_DECLS

const char *dmi_baseboard_type_name(enum dmi_baseboard_type value);

__END_DECLS

#endif // !OPENDMI_TABLE_BASEBOARD_H
