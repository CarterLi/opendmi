//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>

#include <opendmi/registry.h>
#include <opendmi/context.h>
#include <opendmi/table.h>

/**
 * @internal
 */
static bool dmi_registry_build(dmi_registry_t *registry);

/**
 * @internal
 */
static bool dmi_registry_put(dmi_registry_t *registry, dmi_table_t *table);

dmi_registry_t *dmi_registry_create(dmi_context_t *context, size_t capacity)
{
    dmi_registry_t *registry = nullptr;

    if (!capacity)
        capacity = DMI_REGISTRY_CAPACITY;

    registry = malloc(sizeof(*registry));
    if (registry == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    memset(registry, 0, sizeof(*registry));

    registry->context  = context;
    registry->capacity = capacity;

    bool success = false;
    do {
        registry->index = calloc(capacity, sizeof(dmi_registry_entry_t *));
        if (!registry->index) {
            dmi_set_error(registry->context, DMI_ERROR_OUT_OF_MEMORY);
            break;
        }

        success = dmi_registry_build(registry);
    } while (false);

    if (!success) {
        dmi_registry_destroy(registry);
        return nullptr;
    }

    return registry;
}

dmi_table_t *dmi_registry_get(dmi_registry_t *registry, dmi_handle_t handle)
{
    dmi_registry_entry_t *entry = nullptr;

    entry = registry->index[(size_t)handle % registry->capacity];

    while (entry) {
        if (entry->table->handle == handle)
            break;
        entry = entry->next;
    }

    if (!entry) {
        dmi_set_error(registry->context, DMI_ERROR_ENTRY_NOT_FOUND);
        return nullptr;
    }

    return entry->table;
}

void dmi_registry_destroy(dmi_registry_t *registry)
{
    if (!registry)
        return;

    if (registry->index) {
        struct dmi_registry_entry *entry, *next;

        for (size_t i = 0; i < registry->capacity; i++) {
            entry = registry->index[i];

            while (entry) {
                next = entry->next;

                dmi_table_destroy(entry->table);
                free(entry);

                entry = next;
            }
        }
    
        free(registry->index);
    }

    free(registry);
}

static bool dmi_registry_build(dmi_registry_t *registry)
{
    size_t index = 0;
    dmi_context_t *context = registry->context;
    const dmi_data_t *ptr = context->table_data;

    bool success = false;
    while ((context->table_count == 0) || (index < context->table_count)) {
        dmi_table_t *table = nullptr;

        // Check table address
        if ((size_t)(ptr - context->table_data) > context->table_area_size) {
            dmi_set_error(context, DMI_ERROR_INVALID_TABLE_ADDR);
            goto exit;
        }

        // Decode table
        table = dmi_table_decode(context, ptr);
        if (table == nullptr) {
            if (dmi_get_error(context) == DMI_ERROR_NO_MORE_ENTRIES)
                break;
            goto exit;
        }

        // Update table pointer and index
        ptr += table->total_length;
        index++;

        if (!dmi_registry_put(registry, table)) {
            dmi_table_destroy(table);
            goto exit;
        }
    }

    // Set table count
    registry->count = index + 1;
    success = true;

exit:
    return success;
}

static bool dmi_registry_put(dmi_registry_t *registry, dmi_table_t *table)
{
    size_t hash;
    dmi_registry_entry_t *entry;
    dmi_registry_entry_t *last;

    // Allocate new entry
    entry = malloc(sizeof(dmi_registry_entry_t));
    if (entry == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_OUT_OF_MEMORY);
        return false;
    }

    // Initialize entry
    memset(entry, 0, sizeof(dmi_registry_entry_t));
    entry->table = table;

    hash = (size_t)table->handle % registry->capacity;
    last = registry->index[hash];

    // Add entry to index
    if (last == nullptr) {
        registry->index[hash] = entry;
    } else {
        while (true) {
            if (last->table->handle == table->handle) {
                free(entry);
                dmi_set_error(nullptr, DMI_ERROR_DUPLICATE_ENTRY);
                return false;
            }

            if (!last->next)
                break;

            last = last->next;
        }

        last->next = entry;
    }

    entry->seq_prev = registry->tail;

    if (registry->tail)
        registry->tail->seq_next = entry;
    registry->tail = entry;

    if (!registry->head)
        registry->head = entry;

    return true;
}
