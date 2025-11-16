//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_BASEBOARD_H
#define OPENDMI_TABLE_BASEBOARD_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_BASEBOARD_DATA_T
#define DMI_BASEBOARD_DATA_T
typedef struct dmi_baseboard_data dmi_baseboard_data_t;
#endif // !DMI_BASEBOARD_DATA_T

#ifndef DMI_BASEBOARD_T
#define DMI_BASEBOARD_T
typedef struct dmi_baseboard dmi_baseboard_t;
#endif // !DMI_BASEBOARD_T

/**
 * @brief Baseboard type identifiers.
 */
typedef enum dmi_baseboard_type
{
    DMI_BASEBOARD_TYPE_UNKNOWN                  = 0x01, /**< Unknown */
    DMI_BASEBOARD_TYPE_OTHER                    = 0x02, /**< Other */
    DMI_BASEBOARD_TYPE_SERVER_BLADE             = 0x03, /**< Server blade */
    DMI_BASEBOARD_TYPE_CONNECTIVITY_SWITCH      = 0x04, /**< Connectivity switch */
    DMI_BASEBOARD_TYPE_SYSTEM_MANAGEMENT_MODULE = 0x05, /**< System management module */
    DMI_BASEBOARD_TYPE_PROCESSOR_MODULE         = 0x06, /**< Processor module */
    DMI_BASEBOARD_TYPE_IO_MODULE                = 0x07, /**< IO module */
    DMI_BASEBOARD_TYPE_MEMORY_MODULE            = 0x08, /**< Memory module */
    DMI_BASEBOARD_TYPE_DAUGHTERBOARD            = 0x09, /**< Daughterboard */
    DMI_BASEBOARD_TYPE_MOTHERBOARD              = 0x0A, /**< Motherboard */
    DMI_BASEBOARD_TYPE_PROCESSOR_MEMORY_MODULE  = 0x0B, /**< Processor/memory module */
    DMI_BASEBOARD_TYPE_PROCESSOR_IO_MODULE      = 0x0C, /**< Processor/IO module */
    DMI_BASEBOARD_TYPE_INTERCONNECT_BOARD       = 0x0D, /**< Interconnect board */
} dmi_baseboard_type_t;

/**
 * @brief Baseboard feature flags.
 */
DMI_PACKED_STRUCT(dmi_baseboard_features)
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
};

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
DMI_PACKED_STRUCT(dmi_baseboard_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Manufacturer name.
     */
    dmi_string_t vendor;

    /**
     * @brief Product name.
     */
    dmi_string_t product;

    /**
     * @brief Product version.
     */
    dmi_string_t version;

    /**
     * @brief Serial number.
     */
    dmi_string_t serial_number;

    /**
     * @brief Asset tag.
     */
    dmi_string_t asset_tag;

    /**
     * @brief Collection of flags that identify features of this baseboard.
     */
    struct dmi_baseboard_features features;

    /**
     * @brief Number of a null-terminated string that describes this board's
     * location within the chassis referenced by the chassis handle (described
     * below in this table).
     */
    dmi_string_t location;

    /**
     * @brief Handle, or instance number, associated with the chassis in which
     * this board resides.
     */
    dmi_handle_t chassis_handle;

    /**
     * @brief Type of board.
     */
    enum dmi_baseboard_type type;

    /**
     * @brief Number (0 to 255) of contained object handles that follow.
     */
    dmi_byte_t children_count;

    /**
     * @brief List of handles of other structures (for example, baseboard,
     * processor, port, system slots, memory device) that are contained by
     * this baseboard.
     */
    dmi_handle_t children_handles[];
};

struct dmi_baseboard
{
    char *vendor;
    char *product;
    char *version;
    char *serial_number;
    char *asset_tag;
    struct dmi_baseboard_features features;
    char *location;
};

/**
 * @brief Baseboard or module information table specification.
 */
extern const struct dmi_table_spec dmi_baseboard_table;

__BEGIN_DECLS

const char *dmi_baseboard_type_name(enum dmi_baseboard_type value);

__END_DECLS

#endif // !OPENDMI_TABLE_BASEBOARD_H
