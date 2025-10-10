//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_REGISTRY_H
#define OPENDMI_REGISTRY_H

#pragma once

#include <opendmi/types.h>

#ifndef DMI_REGISTRY_T
#define DMI_REGISTRY_T
typedef struct dmi_registry dmi_registry_t;
#endif // !DMI_REGISTRY_T

#ifndef DMI_REGISTRY_ENTRY_T
#define DMI_REGISTRY_ENTRY_T
typedef struct dmi_registry_entry dmi_registry_entry_t;
#endif // !DMI_REGISTRY_ENTRY_T

struct dmi_registry
{
    size_t capacity;
    size_t count;
    dmi_registry_entry_t *index;
    dmi_registry_entry_t *root;
};

struct dmi_registry_entry
{
    dmi_table_t *table;
    dmi_registry_entry_t *pred;
    dmi_registry_entry_t *succ;
    dmi_registry_entry_t *next;
};

__BEGIN_DECLS

/**
 * @brief Create DMI registry.
 */
dmi_registry_t *dmi_registry_create(void);

/**
 * @brief Put table into DMI registry.
 */
void dmi_registry_put(dmi_registry_t *registry, dmi_table_t *table);

/**
 * @brief Get table from DMI registry.
 */
dmi_table_t *dmi_registry_get(dmi_registry_t *registry, dmi_handle_t handle);

/**
 * @brief Destroy DMI registry.
 */
void dmi_registry_destroy(dmi_registry_t *registry);

__END_DECLS

#endif // !OPENDMI_REGISTRY_H
