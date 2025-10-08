//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include <opendmi/context.h>
#include <opendmi/table.h>

/**
 * @internal
 */
static bool dmi_table_decode_length(dmi_table_t *table);

/**
 * @internal
 */
static bool dmi_table_decode_strings(dmi_table_t *table);

bool dmi_table_scan(dmi_context_t *context)
{
    if ((context == nullptr) || (context->table_data == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    size_t index = 0;
    const dmi_data_t *ptr = context->table_data;

    bool success = false;
    while ((context->table_count == 0) || (index < context->table_count)) {
        dmi_table_t *table = nullptr;

        // Check table address
        if ((size_t)(ptr - context->table_data) > context->table_area_size) {
            dmi_set_error(context, DMI_ERROR_INVALID_TABLE_ADDR);
            goto exit;
        }

        // Decode next table
        table = dmi_table_decode(context, ptr);
        if (table == nullptr) {
            if (dmi_get_error(context) == DMI_ERROR_NO_MORE_ENTRIES)
                break;
            goto exit;
        }

        // Update table pointer and index
        ptr += table->total_length;
        index++;
    }

    // Set table count
    context->table_count = index + 1;
    success = true;

exit:
    return success;
}

dmi_table_t *dmi_table_decode(dmi_context_t *context, const void *data)
{
    if ((context == nullptr) || (data == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }

    dmi_table_t        *table  = nullptr;
    dmi_table_header_t *header = (dmi_table_header_t *)data;

    // Check table type
    if (header->type == DMI_TYPE_END_OF_TABLE) {
        dmi_set_error(context, DMI_ERROR_NO_MORE_ENTRIES);
        return nullptr;
    }

    // Check table length
    if (header->length < sizeof(dmi_table_header_t))
    {
        if (header->length == 0)
            dmi_set_error(context, DMI_ERROR_NO_MORE_ENTRIES);
        else
            dmi_set_error(context, DMI_ERROR_INVALID_TABLE_LENGTH);

        return nullptr;
    }

    // Allocate new table descriptor
    table = malloc(sizeof(dmi_table_t));
    if (table == nullptr) {
        dmi_set_error(context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }
    memset(table, 0, sizeof(dmi_table_t));

    // Decode table header
    table->context     = context;
    table->type        = header->type;
    table->handle      = header->handle;
    table->data        = data;
    table->body_length = header->length;

    // Decode unformed section
    bool success = false;
    do {
        if (!dmi_table_decode_length(table))
            break;
        if (!dmi_table_decode_strings(table))
            break;

        success = true;
    } while (false);

    if (!success) {
        dmi_table_destroy(table);
        return nullptr;
    }

    return table;
}

dmi_handle_t dmi_table_handle(struct dmi_table *table)
{
    if (table == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return DMI_HANDLE_INVALID;
    }

    return table->handle;
}

const char *dmi_table_string(struct dmi_table *table, dmi_string_t num)
{
    if (table == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }

    if (!num || (num > table->string_count)) {
        dmi_set_error(table->context, DMI_ERROR_ENTRY_NOT_FOUND);
        return nullptr;
    }

    return table->strings[num - 1];
}

void dmi_table_destroy(struct dmi_table *table)
{
    if (table == nullptr)
        return;

    if (table->strings != nullptr)
        free(table->strings);
    free(table);
}

static bool dmi_table_decode_length(dmi_table_t *table)
{
    if (table == nullptr) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if (table->data == nullptr) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    const char *data  = (const char *)table->data;
    const char *start = data + table->body_length;
    const char *ptr   = start;
    size_t      count = 0;

    // Calculate table length and count strings
    while (true) {
        if (*ptr != 0) {
            count++;

            while (*ptr != 0) {
                ptr++;
            }
        }

        ptr++;

        if (*ptr == 0) {
            ptr++;
            break;
        }
    }

    table->extra_length = ptr - start;
    table->total_length = table->body_length + table->extra_length;
    table->string_count = count;

    return true;
}

static bool dmi_table_decode_strings(dmi_table_t *table)
{
    if (table == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if (table->data == nullptr) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    const char *data  = (const char *)table->data;
    const char *start = data + table->body_length;
    const char *ptr   = start;
    size_t      index = 0;

    // Allocate strings index
    table->strings = calloc(table->string_count + 1, sizeof(const char *));
    if (table->strings == nullptr) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return false;
    }

    // Fetch string pointers
    if (table->string_count > 0) {
        while (true) {
            if (*ptr != 0) {
                table->strings[index++] = ptr;

                while (*ptr != 0)
                {
                    ptr++;
                }
            }

            ptr++;

            if (*ptr == 0)
            {
                ptr++;
                break;
            }
        }
    }

    // Terminate strings index
    table->strings[index] = nullptr;

    return true;
}
