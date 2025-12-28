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

typedef void *(*dmi_format_initialize_fn_t)(dmi_context_t *context, FILE *stream);

typedef bool (*dmi_format_dump_start_fn_t)(void *session);
typedef bool (*dmi_format_entry_fn_t)(void *session);
typedef bool (*dmi_format_table_start_fn_t)(void *session);

typedef bool (*dmi_format_entity_start_fn_t)(void *session, const dmi_entity_t *entity);
typedef bool (*dmi_format_entity_attrs_start_fn_t)(void *session, const dmi_entity_t *entity);

typedef bool (*dmi_format_entity_attr_fn_t)(
            void                  *session,
            const dmi_entity_t    *entity,
            const dmi_attribute_t *attr,
            const void            *value);

typedef bool (*dmi_format_entity_attrs_end_fn_t)(void *session, const dmi_entity_t *entity);
typedef bool (*dmi_format_entity_data_fn_t)(void *session, const dmi_entity_t *entity);
typedef bool (*dmi_format_entity_strings_fn_t)(void *session, const dmi_entity_t *entity);
typedef bool (*dmi_format_entity_end_fn_t)(void *session, const dmi_entity_t *entity);

typedef bool (*dmi_format_table_end_fn_t)(void *session);
typedef bool (*dmi_format_dump_end_fn_t)(void *session);

typedef void (*dmi_format_finalize_fn_t)(void *session);

struct dmi_format_ops
{
    dmi_format_initialize_fn_t initialize;

    dmi_format_dump_start_fn_t  dump_start;
    dmi_format_entry_fn_t       entry;
    dmi_format_table_start_fn_t table_start;

    dmi_format_entity_start_fn_t entity_start;

    dmi_format_entity_attrs_start_fn_t entity_attrs_start;
    dmi_format_entity_attr_fn_t        entity_attr;
    dmi_format_entity_attrs_end_fn_t   entity_attrs_end;

    dmi_format_entity_data_fn_t    entity_data;
    dmi_format_entity_strings_fn_t entity_strings;

    dmi_format_entity_end_fn_t entity_end;

    dmi_format_table_end_fn_t table_end;
    dmi_format_dump_end_fn_t  dump_end;

    dmi_format_finalize_fn_t finalize;
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
