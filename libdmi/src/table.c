//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <errno.h>

#include <opendmi/table.h>

struct dmi_table *dmi_table_open(void *ptr)
{
    struct dmi_table *table;

    // Check arguments
    if (!ptr) {
        errno = EINVAL;
        return nullptr;
    }

    // Allocate new table descriptor
    table = malloc(sizeof(*table));
    if (!table) {
        errno = ENOMEM;
        return nullptr;
    }

    table->header = (struct dmi_table_header *)ptr;

    return table;
}

dmi_handle_t dmi_table_handle(struct dmi_table *table)
{
    if (!table) {
        errno = EINVAL;
        return DMI_HANDLE_INVALID;
    }

    return table->header->handle;
}

const char *dmi_table_string(struct dmi_table *table, dmi_string_t num)
{
    if (!table) {
        errno = EINVAL;
        return nullptr;
    }

    if (!num || (num > table->string_count)) {
        errno = ENOENT;
        return nullptr;
    }

    return table->strings[num - 1];
}

void dmi_table_close(struct dmi_table *table)
{
    free(table);
}
