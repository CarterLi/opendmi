//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_CONTEXT_H
#define OPENDMI_CONTEXT_H

#pragma once

#include <opendmi/types.h>
#include <opendmi/error.h>
#include <opendmi/version.h>

/**
 * @brief DMI context descriptor.
 */
typedef struct dmi_context
{
    /**
     * @brief SMBIOS version number.
     */
    dmi_version_t smbios_version;

    /**
     * @brief SMBIOS entry point revision.
     */
    dmi_version_t entry_version;

    /**
     * @brief Pointer to SMBIOS entry point data.
     */
    void *entry_data;

    /**
     * @brief Total number of SMBIOS tables.
     */
    size_t table_count;

    /**
     * @brief Address of SMBIOS table area.
     */
    uintptr_t table_area_addr;

    /**
     * @brief Actual size of SMBIOS table area.
     */
    size_t table_area_size;

    /**
     * @brief Maximum size of SMBIOS table area.
     */
    size_t table_area_size_max;

    /**
     * @brief Pointer to SMBIOS table area data.
     */
    void *table_data;

    /**
     * @brief Maximum size of SMBIOS table.
     */
    size_t table_size_max;

    /**
     * @brief Last error code.
     */
    dmi_error_t last_error;
};

__BEGIN_DECLS

/**
 * @brief Set last DMI error code.
 *
 * @param context DMI context handle (may be `NULL`)
 * @param error Error code
 */
void dmi_set_error(dmi_context_t *context, dmi_error_t error);

/**
 * @brief Get last DMI error code.
 *
 * @param context DMI context handle (may be `NULL`)
 * @return Error code
 */
dmi_error_t dmi_get_error(const dmi_context_t *context);


__END_DECLS

#endif // !OPENDMI_CONTEXT_H
