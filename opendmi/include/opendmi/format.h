//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_H
#define OPENDMI_FORMAT_H

#pragma once

#include <stdio.h>

#include <opendmi/attribute.h>

#ifndef DMI_FORMAT_T
#define DMI_FORMAT_T
typedef struct dmi_format dmi_format_t;
#endif // !DMI_FORMAT_T

#ifndef DMI_FORMAT_OPS_T
#define DMI_FORMAT_OPS_T
typedef struct dmi_format_ops dmi_format_ops_t;
#endif // !DMI_FORMAT_OPS_T

struct dmi_format_ops
{
    void *(*initialize)(dmi_context_t *context, FILE *stream);

    bool (*dump_start)(void *asession);
    bool (*entry)(void *asession);
    bool (*table_start)(void *asession, const dmi_table_t *table);

    bool (*table_attrs_start)(void *asession, const dmi_table_t *table);

    bool (*table_attr)(
            void                  *asession,
            const dmi_table_t     *table,
            const dmi_attribute_t *attr,
            const void            *value);

    bool (*table_attrs_end)(void *asession, const dmi_table_t *table);

    bool (*table_data)(void *asession, const dmi_table_t *table);
    bool (*table_strings)(void *asession, const dmi_table_t *table);

    bool (*table_end)(void *asession, const dmi_table_t *table);
    bool (*dump_end)(void *asession);

    void (*finalize)(void *asession);
};

struct dmi_format
{
    const char *code;
    const char *name;
    const dmi_format_ops_t handlers;
};

__BEGIN_DECLS

const dmi_format_t *dmi_format_get(const char *code);

__END_DECLS

#endif // !OPENDMI_FORMAT_H
