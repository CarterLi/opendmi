//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_REGISTRY_H
#define OPENDMI_REGISTRY_H

#pragma once

#include <opendmi/filter.h>

/**
 * @brief Default DMI registry capacity.
 */
#define DMI_REGISTRY_CAPACITY 64

typedef struct dmi_registry       dmi_registry_t;
typedef struct dmi_registry_entry dmi_registry_entry_t;
typedef struct dmi_registry_iter  dmi_registry_iter_t;

/**
 * @brief Registry status flags.
 */
enum dmi_context_status
{
    DMI_REGISTRY_STATUS_SCANNED   = (1 << 0),
    DMI_REGISTRY_STATUS_TRUNCATED = (1 << 1),
    DMI_REGISTRY_STATUS_DECODED   = (1 << 2),
    DMI_REGISTRY_STATUS_LINKED    = (1 << 3)
};

/**
 * @brief Registry descriptor.
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

    /**
     * @brief Status flags.
     */
    unsigned int status;
};

/**
 * @brief Registry entry descriptor.
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

/**
 * @brief Registry iterator.
 */
struct dmi_registry_iter
{
    /**
     * @brief Registry handle.
     */
    dmi_registry_t *registry;

    /**
     * @brief Filter descriptor.
     */
    dmi_filter_t *filter;

    /**
     * @brief Current position.
     */
    dmi_registry_entry_t *position;

    /**
     * @brief Done flag.
     */
    bool is_done;
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
bool dmi_registry_scan(dmi_registry_t *registry);

/**
 * @internal
 */
bool dmi_registry_decode(dmi_registry_t *registry);

/**
 * @internal
 */
bool dmi_registry_link(dmi_registry_t *registry);

/**
 * @brief Get entity from registry.
 *
 * @param[in] registry Registry handle.
 *
 * @param[in] handle   Entity handle. Should be set to `DMI_HANDLE_INVALID` if
 *                     the handle is unknown. In this case `type` is mandatory.
 *
 * @param[in] type     Expected structure type. Should be set to
 *                     `DMI_TYPE_INVALID` if the type is unknown. If there is
 *                     more than one entity of the given type and handle is not
 *                     specified, the first one is returned.
 *
 * @param[in] optional Set to true if missing entity is not an error.
 *
 * @returns Non-owning pointer to the entity, `nullptr` if not found.
 */
dmi_entity_t *dmi_registry_get(
        dmi_registry_t *registry,
        dmi_handle_t    handle,
        dmi_type_t      type,
        bool            optional);

/**
 * @brief Get entity from registry, that matches any of the expected types.
 *
 * @param[in] registry Registry handle.
 *
 * @param[in] handle   Entity handle. In constrast to `dmi_registry_get()`,
 *                     should be always valid.
 *
 * @param[in] types    Array of expected structure types, terminated by
 *                     `DMI_TYPE_INVALID`. May be set to `nullptr` to disable
 *                     type checks.
 *
 * @param[in] optional Set to true if missing entity is not an error.
 *
 * @returns Non-owning pointer to the entity, `nullptr` if not found.
 */
dmi_entity_t *dmi_registry_get_any(
        dmi_registry_t   *registry,
        dmi_handle_t      handle,
        const dmi_type_t *type,
        bool              optional);

/**
 * @brief Get registry status flags.
 *
 * @param[in] registry Registry handle.
 * @return Status flags
 */
unsigned dmi_registry_status(const dmi_registry_t *registry);

/**
 * @brief Destroy registry.
 *
 * @param[in] registry Registry handle.
 */
void dmi_registry_destroy(dmi_registry_t *registry);

bool dmi_registry_iter_init(
        dmi_registry_iter_t *iter,
        dmi_registry_t *registry,
        dmi_filter_t *filter);

bool dmi_registry_iter_has_next(dmi_registry_iter_t *iter);

dmi_entity_t *dmi_registry_iter_next(dmi_registry_iter_t *iter);

__END_DECLS

#endif // !OPENDMI_REGISTRY_H
