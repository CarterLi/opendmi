//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>

#include <opendmi/registry.h>
#include <opendmi/context.h>
#include <opendmi/table.h>
#include <opendmi/log.h>
#include <opendmi/utils.h>

/**
 * @internal
 */
static bool dmi_registry_put(dmi_registry_t *registry, dmi_table_t *table);

dmi_registry_t *dmi_registry_create(dmi_context_t *context, size_t capacity)
{
    dmi_registry_t *registry = nullptr;

    dmi_log_debug(context, "Creating registry...");

    if (!capacity)
        capacity = DMI_REGISTRY_CAPACITY;

    registry = dmi_alloc(context, sizeof(*registry));
    if (registry == nullptr)
        return nullptr;

    registry->context  = context;
    registry->capacity = capacity;

    bool success = false;
    do {
        registry->index = dmi_alloc_array(context, sizeof(dmi_registry_entry_t *), capacity);
        if (!registry->index)
            break;

        success = true;
    } while (false);

    if (!success) {
        dmi_registry_destroy(registry);
        return nullptr;
    }

    return registry;
}

dmi_table_t *dmi_registry_get(dmi_registry_t *registry, dmi_handle_t handle, dmi_type_t type)
{
    dmi_registry_entry_t *entry = nullptr;

    if (registry == nullptr)
        return nullptr;

    if ((handle == DMI_HANDLE_INVALID) or (handle == DMI_HANDLE_UNSUPPORTED)) {
        dmi_error_raise_ex(registry->context, DMI_ERROR_INVALID_ARGUMENT, "handle: 0x%04x", handle);
        return nullptr;
    }

    entry = registry->index[(size_t)handle % registry->capacity];

    while (entry) {
        if (entry->table->handle == handle)
            break;
        entry = entry->next;
    }

    if (!entry) {
        dmi_error_raise_ex(registry->context, DMI_ERROR_TABLE_NOT_FOUND, "0x%04x", handle);
        return nullptr;
    }

    if ((type != DMI_TYPE_INVALID) and (entry->table->type != type)) {
        dmi_error_raise_ex(registry->context, DMI_ERROR_INVALID_TABLE_TYPE, "0x%04x", handle);
        return nullptr;
    }

    return entry->table;
}

dmi_table_t *dmi_registry_get_any(
        dmi_registry_t *registry,
        dmi_handle_t    handle,
        dmi_type_t     *type)
{
    dmi_table_t *table;

    if (registry == nullptr)
        return nullptr;

    table = dmi_registry_get(registry, handle, DMI_TYPE_INVALID);
    if (table == nullptr)
        return nullptr;

    if (type != nullptr) {
        while (*type != DMI_TYPE_INVALID) {
            if (table->type == *type)
                break;
            type++;
        }

        if (*type == DMI_TYPE_INVALID) {
            dmi_error_raise_ex(registry->context, DMI_ERROR_INVALID_TABLE_TYPE, "0x%04x", handle);
            return nullptr;
        }
    }

    return table;
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
                dmi_free(entry);

                entry = next;
            }
        }
    
        dmi_free(registry->index);
    }

    dmi_free(registry);
}

bool dmi_registry_build(dmi_registry_t *registry)
{
    bool success = false;
    size_t index = 0;
    dmi_context_t *context = registry->context;
    const dmi_data_t *ptr = context->table_data;

    dmi_log_debug(context, "Scanning SMBIOS structures...");

    // Scan table area
    while ((context->table_count == 0) or (index < context->table_count)) {
        dmi_table_t *table = nullptr;

        // Check table address
        if ((size_t)(ptr - context->table_data) > context->table_area_size) {
            dmi_error_raise(context, DMI_ERROR_INVALID_TABLE_ADDR);
            goto exit;
        }

        // Decode table
        table = dmi_table_decode(context, ptr);
        if (table == nullptr) {
            dmi_error_raise_ex(context, DMI_ERROR_TABLE_DECODE,
                               "0x%04x (%s)", table->handle, table->spec->name);
            goto exit;
        }

        if (table->type == DMI_TYPE_END_OF_TABLE) {
            dmi_table_destroy(table);
            break;
        }

        // Add table to registry
        if (!dmi_registry_put(registry, table)) {
            dmi_error_raise_ex(context, DMI_ERROR_TABLE_REGISTER,
                               "0x%04x (%s)", table->handle, table->spec->name);
            dmi_table_destroy(table);
            goto exit;
        }
    
        // Update table pointer and index
        ptr += table->total_length;
        index++;
    }

    // Set table count
    registry->count = index + 1;
    dmi_log_debug(context, "Found %zu tables", registry->count);

    success = true;

exit:
    return success;
}

bool dmi_registry_link(dmi_registry_t *registry)
{
    dmi_registry_entry_t *entry;

    dmi_log_debug(registry->context, "Linking SMBIOS structures...");

    for (entry = registry->head; entry; entry = entry->seq_next) {
        dmi_table_t *table = entry->table;

        if (!table->spec or !table->spec->handlers.link)
            continue;

        dmi_log_debug(registry->context, "%p: Handle 0x%04x, length %d, type %d (%s)",
                      table->data,
                      (unsigned)table->handle,
                      (int)table->body_length,
                      (int)table->type,
                      dmi_type_name(registry->context, table->type));

        if (!table->spec->handlers.link(table)) {
            dmi_error_raise_ex(table->context, DMI_ERROR_TABLE_LINK,
                               "0x%04x (%s)", table->handle, table->spec->name);
            return false;
        }
    }

    return true;
}

static bool dmi_registry_put(dmi_registry_t *registry, dmi_table_t *table)
{
    size_t hash;
    dmi_registry_entry_t *entry;
    dmi_registry_entry_t *last;

    // Allocate new entry
    entry = dmi_alloc(registry->context, sizeof(dmi_registry_entry_t));
    if (entry == nullptr)
        return false;

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
            if (last->table->data == table->data) {
                dmi_free(entry);
                dmi_error_raise_ex(registry->context, DMI_ERROR_DUPLICATE_ENTRY,
                                   "%p (0x%04x)", table->data, table->handle);
                return false;
            }

            if (last->table->handle == table->handle) {
                dmi_error_raise_ex(registry->context, DMI_ERROR_DUPLICATE_HANDLE,
                                   "0x%04x", table->handle);
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
