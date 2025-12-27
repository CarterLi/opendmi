//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <assert.h>

#include <yaml.h>

#include <opendmi/context.h>
#include <opendmi/error.h>
#include <opendmi/utils.h>

#include <opendmi/format/yaml.h>

typedef struct dmi_yaml_session
{
    dmi_context_t *context;
    FILE *stream;
    yaml_emitter_t *emitter;
} dmi_yaml_session_t;

static void *dmi_yaml_initialize(dmi_context_t *context, FILE *stream);

static bool dmi_yaml_dump_start(void *asession);
static bool dmi_yaml_dump_end(void *asession);

static void dmi_yaml_finalize(void *asession);

const dmi_format_t dmi_yaml_format =
{
    .code     = "yaml",
    .name     = "YAML",
    .handlers = {
        .initialize = dmi_yaml_initialize,
        .dump_start = dmi_yaml_dump_start,
        .dump_end   = dmi_yaml_dump_end,
        .finalize   = dmi_yaml_finalize
    }
};

static void *dmi_yaml_initialize(dmi_context_t *context, FILE *stream)
{
    assert(context != nullptr);
    assert(stream != nullptr);

    bool success = false;
    bool initialized = false;
    dmi_yaml_session_t *session;

    session = dmi_alloc(context, sizeof(*session));
    if (session == nullptr) {
        dmi_error_raise(context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    do {
        session->emitter = dmi_alloc(context, sizeof(*session->emitter));
        if (session->emitter == nullptr)
            break;

        if (not yaml_emitter_initialize(session->emitter)) {
            dmi_error_raise_ex(context, DMI_ERROR_INTERNAL, "Unable to initialize YAML emitter");
            break;
        }
        initialized = true;

        yaml_emitter_set_output_file(session->emitter, stream);

        yaml_emitter_set_unicode(session->emitter, true);
        yaml_emitter_set_indent(session->emitter, 2);

        if (not yaml_emitter_open(session->emitter)) {
            dmi_error_raise_ex(context, DMI_ERROR_INTERNAL, "Unable to open YAML emitter");
            break;
        }

        success = true;
    } while (false);

    if (not success) {
        if (initialized)
            yaml_emitter_delete(session->emitter);
        dmi_free(session->emitter);
        return nullptr;
    }

    session->context = context;
    session->stream  = stream;

    return session;
}

static bool dmi_yaml_dump_start(void *asession)
{
    DMI_UNUSED(asession);

    return true;
}

static bool dmi_yaml_dump_end(void *asession)
{
    assert(asession != nullptr);

    dmi_yaml_session_t *session = dmi_cast(session, asession);

    if (not yaml_emitter_flush(session->emitter))
        return false;

    return true;
}

static void dmi_yaml_finalize(void *asession)
{
    assert(asession != nullptr);

    dmi_yaml_session_t *session = dmi_cast(session, asession);

    yaml_emitter_close(session->emitter);
    yaml_emitter_delete(session->emitter);

    dmi_free(session->emitter);
}
