//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_CONTEXT_H
#define OPENDMI_CONTEXT_H

#pragma once

#include <opendmi/types.h>
#include <opendmi/error.h>
#include <opendmi/log.h>
#include <opendmi/version.h>
#include <opendmi/backend.h>
#include <opendmi/extension.h>
#include <opendmi/registry.h>

/**
 * @brief DMI context descriptor.
 */
struct dmi_context
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
     * @brief Actual size of entry point data.
     */
    size_t entry_size;

    /**
     * @brief Total number of SMBIOS tables.
     */
    size_t table_count;

    /**
     * @brief Address of SMBIOS table area.
     */
    uint64_t table_area_addr;

    /**
     * @brief Actual size of SMBIOS table area.
     */
    size_t table_area_size;

    /**
     * @brief Maximum size of SMBIOS table area.
     */
    size_t table_area_max_size;

    /**
     * @brief Pointer to SMBIOS table area data.
     */
    dmi_data_t *table_data;

    /**
     * @brief Maximum size of SMBIOS table.
     */
    size_t table_max_size;

    /**
     * @brief Logger callback.
     */
    dmi_log_handler_t logger;

    /**
     * @brief Logging level.
     */
    dmi_log_level_t log_level;

    /**
     * @brief Backend handle.
     */
    dmi_backend_t *backend;

    /**
     * @brief Backend-specific data.
     */
    void *session;

    /**
     * @brief DMI table specifications map.
     */
    dmi_table_spec_t **type_map;

    /**
     * @brief Table registry.
     */
    dmi_registry_t *registry;

    /**
     * @brief Last error code.
     */
    dmi_error_t last_error;
};

__BEGIN_DECLS

/**
 * @brief Create DMI context.
 */
dmi_context_t *dmi_create(void);

/**
 * @brief Open DMI context.
 *
 * @param[in] context DMI context handle.
 * @return The function returns `true` on success and `false` otherwise.
 */
bool dmi_open(dmi_context_t *context);

/**
 * @brief Add DMI extension.
 */
bool dmi_add_extension(dmi_context_t *context, const dmi_extension_t *extension);

/**
 * @brief Load dump file into DMI context.
 *
 * @param[in] context DMI context handle.
 * @param[in] path Path to dump file.
 *
 * @return The function returns `true` on success and `false` otherwise.
 */
bool dmi_dump_load(dmi_context_t *context, const char *path);

/**
 * @brief Save DMI context to dump file.
 *
 * @param[in] context DMI context handle.
 * @param[in] path Path to dump file.
 *
 * @return The function returns `true` on success and `false` otherwise.
 */
bool dmi_dump_save(dmi_context_t *context, const char *path);

/**
 * @brief Get table type specification.
 */
const dmi_table_spec_t *dmi_type_spec(dmi_context_t *context, dmi_type_t type);

/**
 * @brief Get table type name.
 */
const char *dmi_type_name(dmi_context_t *context, dmi_type_t type);

/**
 * @brief Set logging handler.
 *
 * @param[in] context DMI context handle.
 * @param[in] logger Logging handler.
 *
 * @return The function returns `true` on success and `false` otherwise.
 */
bool dmi_set_logger(dmi_context_t *context, dmi_log_handler_t logger);

/**
 * @brief Set logging level.
 *
 * @param[in] context DMI context handle.
 * @param[in] level Logging level.
 *
 * @return The function returns `true` on success and `false` otherwise.
 */
bool dmi_set_log_level(dmi_context_t *context, dmi_log_level_t level);

/**
 * @brief Set last DMI error code.
 *
 * @param[in] context DMI context handle (may be `NULL`).
 * @param[in] error Error code.
 */
void dmi_set_error(dmi_context_t *context, dmi_error_t error);

/**
 * @brief Get last DMI error code.
 *
 * @param[in] context DMI context handle (may be `NULL`).
 * @return Error code.
 */
dmi_error_t dmi_get_error(const dmi_context_t *context);

/**
 * @brief Close DMI context.
 *
 * @param[in] context DMI context handle.
 * @return The function returns `true` on success and `false` otherwise.
 */
bool dmi_close(dmi_context_t *context);

/**
 * @brief Destroy DMI context.
 *
 * @param[in] context DMI context handle.
 */
void dmi_destroy(dmi_context_t *context);

__END_DECLS

#endif // !OPENDMI_CONTEXT_H
