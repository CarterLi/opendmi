//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <sys/mman.h>

#include <string.h>
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/entry.h>
#include <opendmi/table.h>
#include <opendmi/utils.h>
#include <opendmi/backend/dump.h>

typedef struct dmi_dump_session dmi_dump_session_t;

struct dmi_dump_session
{
    dmi_data_t *data;
    size_t data_size;
};

static bool dmi_dump_open(dmi_context_t *context, const void *arg __attribute__((unused)));
static dmi_data_t *dmi_dump_read_entry(dmi_context_t *context, size_t *plength);
static dmi_data_t *dmi_dump_read_tables(dmi_context_t *context, size_t *plength);
static bool dmi_dump_close(dmi_context_t *context);

dmi_backend_t dmi_dump_backend =
{
    .name        = "Binary dump",
    .open        = dmi_dump_open,
    .read_entry  = dmi_dump_read_entry,
    .read_tables = dmi_dump_read_tables,
    .close       = dmi_dump_close
};

static bool dmi_dump_open(dmi_context_t *context, const void *arg __attribute__((unused)))
{
    if ((context == nullptr) || (arg == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    dmi_dump_session_t *session = malloc(sizeof(dmi_dump_session_t));
    if (session == nullptr) {
        dmi_set_error(context, DMI_ERROR_OUT_OF_MEMORY);
        return false;
    }
    memset(session, 0, sizeof(dmi_dump_session_t));

    session->data = dmi_file_map((const char *)arg, &session->data_size);
    if (!session->data)
        return false;
    if (session->data_size < DMI_ENTRY_MAX_SIZE + sizeof(dmi_header_t))
        return false;

    context->session = session;

    return true;
}

static dmi_data_t *dmi_dump_read_entry(dmi_context_t *context, size_t *plength)
{
    dmi_dump_session_t *session = dmi_cast(session, context->session);

    *plength = DMI_ENTRY_MAX_SIZE;

    return session->data;
}

static dmi_data_t *dmi_dump_read_tables(dmi_context_t *context, size_t *plength)
{
    dmi_dump_session_t *session = dmi_cast(session, context->session);

    *plength = session->data_size - DMI_ENTRY_MAX_SIZE;

    return session->data + DMI_ENTRY_MAX_SIZE;
}

static bool dmi_dump_close(dmi_context_t *context)
{
    dmi_dump_session_t *session = dmi_cast(session, context->session);

    if (session->data) {
        munmap(session->data, session->data_size);
        session->data = nullptr;
    }

    free(session);

    return true;
}
