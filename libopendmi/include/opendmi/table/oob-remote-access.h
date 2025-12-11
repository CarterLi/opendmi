//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_OOB_REMOTE_ACCESS_H
#define OPENDMI_TABLE_OOB_REMOTE_ACCESS_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_OOB_REMOTE_ACCESS_T
#define DMI_OOB_REMOTE_ACCESS_T
typedef struct dmi_oob_remote_access dmi_oob_remote_access_t;
#endif // !DMI_OOB_REMOTE_ACCESS_T

#ifndef DMI_OOB_REMOTE_ACCESS_DATA_T
#define DMI_OOB_REMOTE_ACCESS_DATA_T
typedef struct dmi_oob_remote_access_data dmi_oob_remote_access_data_t;
#endif // !DMI_OOB_REMOTE_ACCESS_DATA_T

#ifndef DMI_OOB_CONNECTIONS_T
#define DMI_OOB_CONNECTIONS_T
typedef union dmi_oob_connections dmi_oob_connections_t;
#endif // !DMI_OOB_CONNECTIONS_T

/**
 * @brief Out-of-band remote access connections.
 */
DMI_PACKED_UNION(dmi_oob_connections)
{
    /**
     * @brief Raw value.
     */
    dmi_byte_t _value;

    DMI_PACKED_STRUCT()
    {
        /**
         * @brief Inbound connection enabled. Identifies whether (`true`) or
         * not (`false`) the facility is allowed to initiate outbound
         * connections to receive incoming connections for the purpose of
         * remote operations or problem management.
         */
        bool is_inbound_enabled : 1;

        /**
         * @brief Outbound connection enabled. Identifies whether (`true`) or
         * not (`false`) the facility is allowed to initiate outbound
         * connections to contact an alert management facility when critical
         * conditions occur.
         */
        bool is_outbound_enabled : 1;

        /**
         * @brief Reserved for future definition by this specification. Set to
         * all zeros.
         */
        dmi_byte_t reserved : 6;
    };
};

/**
 * @brief Out-of-band remote access table (type 30).
 * 
 * This structure describes the attributes and policy settings of a hardware
 * facility that may be used to gain remote access to a hardware system when
 * the operating system is not available due to power-down status, hardware
 * failures, or boot failures.
 * 
 * @since SMBIOS 2.2
 */
DMI_PACKED_STRUCT(dmi_oob_remote_access_data)
{
    /**
     * @brief DMI structure header.
     */
    dmi_header_t header;

    /**
     * @brief Number of the string that contains the manufacturer of the
     * out-of-band access facility.
     */
    dmi_string_t vendor;

    /**
     * @brief Current remote-access connections.
     */
    dmi_byte_t connections;
};

/**
 * @brief Out-of-band remote access.
 */
struct dmi_oob_remote_access
{
    /**
     * @brief The manufacturer of the out-of-band access facility.
     */
    const char *vendor;

    /**
     * @brief Current remote-access connections.
     */
    dmi_oob_connections_t connections;
};

/**
 * @brief Out-of-band remote access table specification.
 */
extern const dmi_table_spec_t dmi_oob_remote_access_table;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_oob_remote_access_t *dmi_oob_remote_access_decode(
        const dmi_table_t *table,
        dmi_version_t     *plevel);

/**
 * @internal
 */
void dmi_oob_remote_access_free(dmi_oob_remote_access_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_OOB_REMOTE_ACCESS_H
