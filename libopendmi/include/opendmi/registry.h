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
     * @brief Structure index capacity.
     */
    size_t capacity;

    /**
     * @brief Structure count.
     */
    size_t count;

    /**
     * @brief Structure index.
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
     * @brief Entity descriptor.
     */
    dmi_entity_t *entity;

    /**
     * @brief Pointer to next entry in the hash table cell.
     */
    dmi_registry_entry_t *next;

    /**
     * @brief Pointer to previous entry in entity sequence.
     */
    dmi_registry_entry_t *seq_prev;

    /**
     * @brief Pointer to next entry in entity sequence.
     */
    dmi_registry_entry_t *seq_next;
};

__BEGIN_DECLS

/**
 * @brief Create registry.
 *
 * @param[in] context  Context handle.
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
 * @brief Get entity from registry.
 *
 * @param[in] registry Registry handle.
 * @param[in] handle   Entity handle.
 * @param[in] type     Expected structure type.
 */
dmi_entity_t *dmi_registry_get(
        dmi_registry_t *registry,
        dmi_handle_t    handle,
        dmi_type_t      type);

dmi_entity_t *dmi_registry_get_any(
        dmi_registry_t *registry,
        dmi_handle_t    handle,
        dmi_type_t     *type);

/**
 * @brief Destroy registry.
 *
 * @param[in] registry Registry handle.
 */
void dmi_registry_destroy(dmi_registry_t *registry);

__END_DECLS

#endif // !OPENDMI_REGISTRY_H
