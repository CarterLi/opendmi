//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <opendmi/context.h>
#include <opendmi/table.h>
#include <opendmi/utils.h>

/**
 * @internal
 */
static bool dmi_table_decode_length(dmi_table_t *table);

/**
 * @internal
 */
static bool dmi_table_decode_strings(dmi_table_t *table);

dmi_table_t *dmi_table_decode(dmi_context_t *context, const void *data)
{
    dmi_table_t *table = nullptr;

    if (context == nullptr)
        return nullptr;

    if (data == nullptr) {
        dmi_error_raise_ex(context, DMI_ERROR_NULL_ARGUMENT, "data");
        return nullptr;
    }

    dmi_header_t *header = dmi_cast(header, data);
    dmi_type_t    type   = dmi_value(header->type);
    size_t        length = dmi_value(header->length);
    dmi_handle_t  handle = dmi_value(header->handle);

    dmi_log_debug(context, "%p: Handle 0x%04x, length %zu, type %d (%s)",
                  data, (unsigned)handle, length, (int)header->type,
                  dmi_type_name(context, type));

    // Check table length
    if (length < sizeof(dmi_header_t))
    {
        dmi_error_raise_ex(context, DMI_ERROR_INVALID_TABLE_LENGTH, "%zu", length);
        return nullptr;
    }

    // Allocate new table descriptor
    table = dmi_alloc(context, sizeof(dmi_table_t));
    if (table == nullptr)
        return nullptr;

    // Decode table header
    table->context     = context;
    table->type        = type;
    table->body_length = length;
    table->handle      = handle;
    table->spec        = dmi_type_spec(context, table->type);
    table->data        = data;

    // Decode table data
    bool success = false;
    do {
        // Decode strings
        if (!dmi_table_decode_length(table))
            break;
        if (!dmi_table_decode_strings(table))
            break;

        // Decode information
        if ((table->spec != nullptr) and (table->spec->handlers.decode != nullptr)) {
            table->info = table->spec->handlers.decode(table, &table->level);
            if (!table->info)
                break;
        }

        success = true;
    } while (false);

    if (!success) {
        dmi_table_destroy(table);
        return nullptr;
    }

    return table;
}

dmi_handle_t dmi_table_handle(const dmi_table_t *table)
{
    if (table == nullptr)
        return DMI_HANDLE_INVALID;

    return table->handle;
}

dmi_type_t dmi_table_type(const dmi_table_t *table)
{
    if (table == nullptr)
        return DMI_TYPE_INVALID;

    return table->type;
}

const char *dmi_table_name(const dmi_table_t *table)
{
    if (table == nullptr)
        return nullptr;

    return dmi_type_name(table->context, table->type);
}

const void *dmi_table_data(const dmi_table_t *table, dmi_type_t type)
{
    if (table == nullptr)
        return nullptr;

    if ((type != DMI_TYPE_INVALID) and (table->type != type)) {
        dmi_error_raise(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    return table->data;
}

const void *dmi_table_info(const dmi_table_t *table, dmi_type_t type)
{
    if (table == nullptr)
        return nullptr;

    if ((type != DMI_TYPE_INVALID) and (table->type != type)) {
        dmi_error_raise(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    return table->info;
}

const char *dmi_table_string(const dmi_table_t *table, dmi_string_t num)
{
    if (table == nullptr)
        return nullptr;

    if (num > table->string_count) {
        dmi_error_raise_ex(table->context, DMI_ERROR_STRING_NOT_FOUND,
                           "Handle 0x%04x, index %u", table->handle, num);
        return nullptr;
    }

    return num > 0 ? table->strings[num - 1] : nullptr;
}

void dmi_table_destroy(dmi_table_t *table)
{
    if (table == nullptr)
        return;

    if ((table->spec != nullptr) and (table->info != nullptr)) {
        if (table->spec->handlers.free)
            table->spec->handlers.free(table->info);
        else
            dmi_free(table->info);
    }

    dmi_free(table->strings);
    dmi_free(table);
}

static bool dmi_table_decode_length(dmi_table_t *table)
{
    assert(table != nullptr);
    assert(table->data != nullptr);

    const char *data  = dmi_cast(data, table->data);
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
    assert(table != nullptr);
    assert(table->data != nullptr);

    const char *data  = dmi_cast(data, table->data);
    const char *start = data + table->body_length;
    const char *ptr   = start;
    size_t      index = 0;

    // Allocate strings index
    table->strings = dmi_alloc_array(table->context, sizeof(const char *), table->string_count + 1);
    if (table->strings == nullptr)
        return false;

    // Fetch string pointers
    if (table->string_count > 0) {
        while (true) {
            if (*ptr != 0) {
                table->strings[index++] = ptr;

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
    }

    // Terminate strings index
    table->strings[index] = nullptr;

    return true;
}
