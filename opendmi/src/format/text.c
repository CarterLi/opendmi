//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/format/text.h>

typedef struct dmi_xml_session
{
    dmi_context_t *context;
    FILE *stream;
} dmi_text_session_t;

static void *dmi_text_initialize(dmi_context_t *context, FILE *stream);
static bool  dmi_text_dump_start(void *asession);
static bool  dmi_text_entry(void *asession);
static bool  dmi_text_table_start(void *asession);
static bool  dmi_text_table_attr(void *asession);
static bool  dmi_text_table_data(void *asession);
static bool  dmi_text_table_strings(void *asession);
static bool  dmi_text_table_end(void *asession);
static bool  dmi_text_dump_end(void *asession);
static void  dmi_text_finalize(void *asession);

const dmi_format_t dmi_text_format =
{
    .code = "text",
    .name = "Plain text",
    .handlers = {
        .initialize    = dmi_text_initialize,
        .dump_start    = dmi_text_dump_start,
        .entry         = dmi_text_entry,
        .table_start   = dmi_text_table_start,
        .table_attr    = dmi_text_table_attr,
        .table_data    = dmi_text_table_data,
        .table_strings = dmi_text_table_strings,
        .table_end     = dmi_text_table_end,
        .dump_end      = dmi_text_dump_end,
        .finalize      = dmi_text_finalize
    }
};

static void *dmi_text_initialize(dmi_context_t *context, FILE *stream)
{
    (void)context;
    (void)stream;

    return nullptr;
}

static bool  dmi_text_dump_start(void *asession)
{
    (void)asession;

    return true;
}

static bool  dmi_text_entry(void *asession)
{
    (void)asession;

    return true;
}

static bool  dmi_text_table_start(void *asession)
{
    (void)asession;

    return true;
}

static bool  dmi_text_table_attr(void *asession)
{
    (void)asession;

    return true;
}

static bool  dmi_text_table_data(void *asession)
{
    (void)asession;

    return true;
}

static bool  dmi_text_table_strings(void *asession)
{
    (void)asession;

    return true;
}

static bool  dmi_text_table_end(void *asession)
{
    (void)asession;

    return true;
}

static bool  dmi_text_dump_end(void *asession)
{
    (void)asession;

    return true;
}

static void dmi_text_finalize(void *asession)
{
    (void)asession;
}
