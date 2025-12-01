//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_SYSTEM_RESET_H
#define OPENDMI_TABLE_SYSTEM_RESET_H

#pragma once

#include <opendmi/table.h>

/**
 * @brief System boot options.
 */
typedef enum dmi_boot_option
{
    DMI_BOOT_OPTION_RESERVED         = 0x00, ///< Reserved, do not use
    DMI_BOOT_OPTION_OPERATING_SYSTEM = 0x01, ///< Operating system
    DMI_BOOT_OPTION_SYSTEM_UTILS     = 0x02, ///< System utilities
    DMI_BOOT_OPTION_AVOID_REBOOT     = 0x03, ///< Do not reboot
} dmi_boot_option_t;

/**
 * @brief System reset capabilities.
 */
DMI_PACKED_UNION(dmi_system_reset_caps)
{
    /**
     * @brief Raw value;
     */
    dmi_byte_t _value;

    DMI_PACKED_STRUCT()
    {
        /**
         * @brief Status. Identifies whether (`true`) or not (`false`) the
         * system reset is enabled by the user.
         */
        bool status : 1;

        /**
         * @brief Boot option. Indicates one of the following actions to be
         * taken after a watchdog reset.
         */
        dmi_boot_option_t boot_on_watchdog : 2;

        /**
         * @brief Boot option on limit. Identifies one of the following system
         * actions to be taken when the reset limit is reached.
         */
        dmi_boot_option_t boot_on_limit : 2;

        /**
         * @brief System contains a watchdog timer: either `true` or `false`.
         */
        bool watchdog_present : 1;

        /**
         * @brief Reserved for future assignment by this specification, set to
         * zero.
         */
        dmi_byte_t reserved : 2;
    };
};

#ifndef DMI_SYSTEM_RESET_CAPS_T
#define DMI_SYSTEM_RESET_CAPS_T
typedef union dmi_system_reset_caps dmi_system_reset_caps_t;
#endif // !DMI_SYSTEM_RESET_CAPS_T

/**
 * @brief System reset table (type 23).
 */
DMI_PACKED_STRUCT(dmi_system_reset_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Identifies the system-reset capabilities for the system.
     */
    dmi_byte_t capabilities;

    /**
     * @brief Number of automatic system resets since the last intentional
     * reset. A value of `0xFFFF` indicates unknown.
     */
    dmi_word_t reset_count;

    /**
     * @brief Number of consecutive times the system reset is attempted. A value
     * of `0xFFFF` indicates unknown.
     */
    dmi_word_t reset_limit;

    /**
     * @brief Number of minutes to use for the watchdog timer. If the timer is
     * not reset within this interval, the system reset timeout begins. A value
     * of `0xFFFF` indicates unknown.
     */
    dmi_word_t timer_inverval;

    /**
     * @brief Number of minutes before the reboot is initiated. It is used
     * after a system power cycle, system reset (local or remote), and automatic
     * system reset. A value of `0xFFFF` indicates unknown.
     */
    dmi_word_t timeout;
};

#ifndef DMI_SYSTEM_RESET_DATA_T
#define DMI_SYSTEM_RESET_DATA_T
typedef struct dmi_system_reset_data dmi_system_reset_data_t;
#endif // !DMI_SYSTEM_RESET_DATA_T

struct dmi_system_reset
{
    /**
     * @brief Status. Identifies whether (`true`) or not (`false`) the
     * system reset is enabled by the user.
     */
    bool status;

    /**
     * @brief Boot option. Indicates one of the following actions to be
     * taken after a watchdog reset.
     */
    dmi_boot_option_t boot_on_watchdog;

    /**
     * @brief Boot option on limit. Identifies one of the following system
     * actions to be taken when the reset limit is reached.
     */
    dmi_boot_option_t boot_on_limit;

    /**
     * @brief System contains a watchdog timer: either `true` or `false`.
     */
    bool watchdog_present;

    /**
     * @brief Number of automatic system resets since the last intentional
     * reset. A value of `USHRT_MAX` indicates unknown.
     */
    unsigned short reset_count;

    /**
     * @brief Number of consecutive times the system reset is attempted. A
     * value of `USHRT_MAX` indicates unknown.
     */
    unsigned short reset_limit;

    /**
     * @brief Number of minutes to use for the watchdog timer. If the timer is
     * not reset within this interval, the system reset timeout begins. A value
     * of `USHRT_MAX` indicates unknown.
     */
    unsigned short timer_interval;

    /**
     * @brief Number of minutes before the reboot is initiated. It is used
     * after a system power cycle, system reset (local or remote), and
     * automatic system reset. A value of `USHRT_MAX` indicates unknown.
     */
    unsigned short timeout;
};

#ifndef DMI_SYSTEM_RESET_T
#define DMI_SYSTEM_RESET_T
typedef struct dmi_system_reset dmi_system_reset_t;
#endif // !DMI_SYSTEM_RESET_T

/**
 * @brief System reset table specification.
 */
extern const dmi_table_spec_t dmi_system_reset_table;

__BEGIN_DECLS

const char *dmi_boot_option_name(dmi_boot_option_t value);

/**
 * @internal
 */
dmi_system_reset_t *dmi_system_reset_decode(const dmi_table_t *table);

/**
 * @internal
 */
void dmi_system_reset_free(dmi_system_reset_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_SYSTEM_RESET_H
