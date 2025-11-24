//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TABLE_SYSTEM_CONFIG_H
#define OPENDMI_TABLE_SYSTEM_CONFIG_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_SYSTEM_CONFIG_OPTS_T
#define DMI_SYSTEM_CONFIG_OPTS_T
typedef struct dmi_system_config_opts dmi_system_config_opts_t;
#endif // !DMI_SYSTEM_CONFIG_OPTIONS_T

#ifndef DMI_SYSTEM_CONFIG_OPTS_DATA_T
#define DMI_SYSTEM_CONFIG_OPTS_DATA_T
typedef struct dmi_system_config_opts_data dmi_system_config_opts_data_t;
#endif // !DMI_SYSTEM_CONFIG_OPTIONS_DATA_T

/**
 * @brief System configuration options table (type 12).
 */
DMI_PACKED_STRUCT(dmi_system_config_opts_data)
{
    /**
     * @brief DMI table header.
     */
    dmi_header_t header;

    /**
     * @brief Number of strings.
     */
    dmi_byte_t count;
};

/**
 * @brief System configuration options.
 */
struct dmi_system_config_opts
{
    /**
     * @brief Number of options.
     */
    size_t option_count;

    /**
     * @brief Option names.
     */
    const char **options;
};

/**
 * @brief System configuration options table specification.
 */
extern const dmi_table_spec_t dmi_system_config_opts_table;

__BEGIN_DECLS

dmi_system_config_opts_t *dmi_system_config_opts_decode(const dmi_table_t *table);
void dmi_system_config_opts_free(dmi_system_config_opts_t *info);

__END_DECLS

#endif // !OPENDMI_TABLE_SYSTEM_CONFIG_H
