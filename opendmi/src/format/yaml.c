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
static bool dmi_yaml_entry(void *asession);
static bool dmi_yaml_table_start(void *asession);
static bool dmi_yaml_entity_start(void *asession, const dmi_entity_t *entity);

static bool dmi_yaml_entity_attr(
        void                  *asession,
        const dmi_entity_t     *entity,
        const dmi_attribute_t *attr,
        const void            *data);

static bool dmi_yaml_entity_data(void *asession, const dmi_entity_t *entity);
static bool dmi_yaml_entity_strings(void *asession, const dmi_entity_t *entity);
static bool dmi_yaml_entity_end(void *asession, const dmi_entity_t *entity);
static bool dmi_yaml_table_end(void *asession);
static bool dmi_yaml_dump_end(void *asession);

static void dmi_yaml_finalize(void *asession);

static bool dmi_yaml_label(dmi_yaml_session_t *session, const char *value);
static bool dmi_yaml_scalar(dmi_yaml_session_t *session, const char *value, yaml_scalar_style_t style);
static bool dmi_yaml_sequence_start(dmi_yaml_session_t *session, yaml_sequence_style_t style);
static bool dmi_yaml_sequence_end(dmi_yaml_session_t *session);
static bool dmi_yaml_mapping_start(dmi_yaml_session_t *session, yaml_mapping_style_t style);
static bool dmi_yaml_mapping_end(dmi_yaml_session_t *session);

const dmi_format_t dmi_yaml_format =
{
    .code     = "yaml",
    .name     = "YAML",
    .handlers = {
        .initialize     = dmi_yaml_initialize,
        .dump_start     = dmi_yaml_dump_start,
        .entry          = dmi_yaml_entry,
        .table_start    = dmi_yaml_table_start,
        .entity_start   = dmi_yaml_entity_start,
        .entity_attr    = dmi_yaml_entity_attr,
        .entity_data    = dmi_yaml_entity_data,
        .entity_strings = dmi_yaml_entity_strings,
        .entity_end     = dmi_yaml_entity_end,
        .table_end      = dmi_yaml_table_end,
        .dump_end       = dmi_yaml_dump_end,
        .finalize       = dmi_yaml_finalize
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
    assert(asession != nullptr);

    bool success = false;
    dmi_yaml_session_t *session = dmi_cast(session, asession);
    yaml_event_t event = { 0 };

    do {
        if (not yaml_document_start_event_initialize(&event, nullptr, nullptr, nullptr, true))
            break;
        if (not yaml_emitter_emit(session->emitter, &event))
            break;

        if (not dmi_yaml_mapping_start(session, YAML_BLOCK_MAPPING_STYLE))
            break;

        success = true;
    } while (false);

    if (!success)
        dmi_error_raise_ex(session->context, DMI_ERROR_INTERNAL, "Unable to start YAML document");

    return success;
}

static bool dmi_yaml_entry(void *asession)
{
    assert(asession != nullptr);

    bool success = false;
    dmi_yaml_session_t *session = dmi_cast(session, asession);
    char *smbios_version = nullptr;

    do {
        smbios_version = dmi_version_format(session->context->smbios_version);
        if (smbios_version == nullptr)
            break;

        if (not dmi_yaml_label(session, "entry"))
            break;
        if (not dmi_yaml_mapping_start(session, YAML_BLOCK_MAPPING_STYLE))
            break;

        if (not dmi_yaml_label(session, "smbios-version"))
            break;
        if (not dmi_yaml_scalar(session, smbios_version, YAML_PLAIN_SCALAR_STYLE))
            break;

        if (not dmi_yaml_mapping_end(session))
            break;

        success = true;
    } while (false);

    dmi_free(smbios_version);

    return success;
}

static bool dmi_yaml_table_start(void *asession)
{
    assert(asession != nullptr);

    bool success = false;
    dmi_yaml_session_t *session = dmi_cast(session, asession);

    do {
        if (not dmi_yaml_label(session, "table"))
            break;
        if (not dmi_yaml_sequence_start(session, YAML_BLOCK_SEQUENCE_STYLE))
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_yaml_entity_start(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);

    bool success = false;
    dmi_yaml_session_t *session = dmi_cast(session, asession);
    char buf[32];

    do {
        if (not dmi_yaml_mapping_start(session, YAML_BLOCK_MAPPING_STYLE))
            break;

        snprintf(buf, sizeof(buf), "0x%04hx", entity->handle);
        if (not dmi_yaml_label(session, "handle"))
            break;
        if (not dmi_yaml_scalar(session, buf, YAML_PLAIN_SCALAR_STYLE))
            break;

        snprintf(buf, sizeof(buf), "%u", entity->type);
        if (not dmi_yaml_label(session, "type"))
            break;
        if (not dmi_yaml_scalar(session, buf, YAML_PLAIN_SCALAR_STYLE))
            break;

        snprintf(buf, sizeof(buf), "%zu", entity->total_length);
        if (not dmi_yaml_label(session, "length"))
            break;
        if (not dmi_yaml_scalar(session, buf, YAML_PLAIN_SCALAR_STYLE))
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_yaml_entity_attr(
        void                  *asession,
        const dmi_entity_t     *entity,
        const dmi_attribute_t *attr,
        const void            *data)
{
    DMI_UNUSED(asession);
    DMI_UNUSED(entity);
    DMI_UNUSED(attr);
    DMI_UNUSED(data);

    return true;
}

static bool dmi_yaml_entity_data(void *asession, const dmi_entity_t *entity)
{
    DMI_UNUSED(asession);
    DMI_UNUSED(entity);

    return true;
}

static bool dmi_yaml_entity_strings(void *asession, const dmi_entity_t *entity)
{
    DMI_UNUSED(asession);
    DMI_UNUSED(entity);

    return true;
}

static bool dmi_yaml_entity_end(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);

    DMI_UNUSED(entity);

    dmi_yaml_session_t *session = dmi_cast(session, asession);

    return dmi_yaml_mapping_end(session);
}

static bool dmi_yaml_table_end(void *asession)
{
    assert(asession != nullptr);

    dmi_yaml_session_t *session = dmi_cast(session, asession);

    return dmi_yaml_sequence_end(session);
}

static bool dmi_yaml_dump_end(void *asession)
{
    assert(asession != nullptr);

    bool success = false;
    dmi_yaml_session_t *session = dmi_cast(session, asession);
    yaml_event_t event = { 0 };

    do {
        if (not dmi_yaml_mapping_end(session))
            break;

        if (not yaml_document_end_event_initialize(&event, true))
            break;
        if (not yaml_emitter_emit(session->emitter, &event))
            break;
        if (not yaml_emitter_flush(session->emitter))
            break;

        success = true;
    } while (false);

    if (!success)
        dmi_error_raise_ex(session->context, DMI_ERROR_INTERNAL, "Unable to end YAML document");

    return success;
}

static void dmi_yaml_finalize(void *asession)
{
    assert(asession != nullptr);

    dmi_yaml_session_t *session = dmi_cast(session, asession);

    yaml_emitter_close(session->emitter);
    yaml_emitter_delete(session->emitter);

    dmi_free(session->emitter);
}

static bool dmi_yaml_label(dmi_yaml_session_t *session, const char *value)
{
    return dmi_yaml_scalar(session, value, YAML_PLAIN_SCALAR_STYLE);
}

static bool dmi_yaml_scalar(dmi_yaml_session_t *session, const char *value, yaml_scalar_style_t style)
{
    assert(session != nullptr);

    bool success = false;
    yaml_event_t event = { 0 };

    do {
        if (not yaml_scalar_event_initialize(
                    &event, nullptr, nullptr, (const yaml_char_t *)value, strlen(value), true, false, style))
            break;
        if (not yaml_emitter_emit(session->emitter, &event))
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_yaml_sequence_start(dmi_yaml_session_t *session, yaml_sequence_style_t style)
{
    assert(session != nullptr);

    bool success = false;
    yaml_event_t event = { 0 };

    do {
        if (not yaml_sequence_start_event_initialize(&event, nullptr, nullptr, true, style))
            break;
        if (not yaml_emitter_emit(session->emitter, &event))
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_yaml_sequence_end(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    bool success = false;
    yaml_event_t event = { 0 };

    do {
        if (not yaml_sequence_end_event_initialize(&event))
            break;
        if (not yaml_emitter_emit(session->emitter, &event))
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_yaml_mapping_start(dmi_yaml_session_t *session, yaml_mapping_style_t style)
{
    assert(session != nullptr);

    bool success = false;
    yaml_event_t event = { 0 };

    do {
        if (not yaml_mapping_start_event_initialize(&event, nullptr, nullptr, true, style))
            break;
        if (not yaml_emitter_emit(session->emitter, &event))
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_yaml_mapping_end(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    bool success = false;
    yaml_event_t event = { 0 };

    do {
        if (not yaml_mapping_end_event_initialize(&event))
            break;
        if (not yaml_emitter_emit(session->emitter, &event))
            break;

        success = true;
    } while (false);

    return success;
}
