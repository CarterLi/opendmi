//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_REGISTRY_H
#define OPENDMI_REGISTRY_H

#pragma once

#include <opendmi/types.h>

/**
 * @brief Default DMI registry capacity.
 */
#define DMI_REGISTRY_CAPACITY 64

#ifndef DMI_REGISTRY_T
#define DMI_REGISTRY_T
typedef struct dmi_registry dmi_registry_t;
#endif // !DMI_REGISTRY_T

#ifndef DMI_REGISTRY_ENTRY_T
#define DMI_REGISTRY_ENTRY_T
typedef struct dmi_registry_entry dmi_registry_entry_t;
#endif // !DMI_REGISTRY_ENTRY_T

/**
 * @brief DMI registry descriptor.
 */
struct dmi_registry
{
    /**
     * @brief DMI context handle.
     */
    dmi_context_t *context;

    /**
     * @brief Table index capacity.
     */
    size_t capacity;

    /**
     * @brief Table count.
     */
    size_t count;

    /**
     * @brief Table index.
     */
    dmi_registry_entry_t **index;

    /**
     * @brief Pointer to first entry in sequence.
     */
    dmi_registry_entry_t *head;

    /**
     * @brief Pointer to last entry in sequence.
     */
    dmi_registry_entry_t *tail;
};

/**
 * @brief DMI registry entry descriptor.
 */
struct dmi_registry_entry
{
    /**
     * @brief DMI table.
     */
    dmi_table_t *table;

    /**
     * @brief Pointer to next entry in the hash table cell.
     */
    dmi_registry_entry_t *next;

    /**
     * @brief Pointer to previous entry in table sequence.
     */
    dmi_registry_entry_t *seq_prev;

    /**
     * @brief Pointer to next entry in table sequence.
     */
    dmi_registry_entry_t *seq_next;
};

__BEGIN_DECLS

/**
 * @brief Create DMI registry.
 *
 * @param[in] context DMI context handle.
 * @param[in] capacity Registry hash-table capacity. Zero means default value
 *                     of `DMI_REGISTRY_CAPACITY`.
 */
dmi_registry_t *dmi_registry_create(dmi_context_t *context, size_t capacity);

/**
 * @internal
 */
bool dmi_registry_build(dmi_registry_t *registry);

/**
 * @internal
 */
bool dmi_registry_link(dmi_registry_t *registry);

/**
 * @brief Get table from DMI registry.
 *
 * @param[in] registry DMI registry handle.
 * @param[in] handle   DMI table identifier.
 * @param[in] type     Expected table type.
 */
dmi_table_t *dmi_registry_get(
        dmi_registry_t *registry,
        dmi_handle_t    handle,
        dmi_type_t      type);

dmi_table_t *dmi_registry_get_any(
        dmi_registry_t *registry,
        dmi_handle_t    handle,
        dmi_type_t     *type);

/**
 * @brief Destroy DMI registry.
 *
 * @param[in] registry DMI registry handle.
 */
void dmi_registry_destroy(dmi_registry_t *registry);

__END_DECLS

#endif // !OPENDMI_REGISTRY_H
