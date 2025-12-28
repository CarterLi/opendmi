//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <assert.h>

#include <opendmi/context.h>
#include <opendmi/error.h>
#include <opendmi/utils.h>

#include <opendmi/format/yaml/handlers.h>
#include <opendmi/format/yaml/helpers.h>

void *dmi_yaml_initialize(dmi_context_t *context, FILE *stream)
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

bool dmi_yaml_dump_start(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    bool success = false;
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

bool dmi_yaml_entry(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    bool success = false;
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

bool dmi_yaml_table_start(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    bool success = false;

    do {
        if (not dmi_yaml_label(session, "table"))
            break;
        if (not dmi_yaml_sequence_start(session, YAML_BLOCK_SEQUENCE_STYLE))
            break;

        success = true;
    } while (false);

    return success;
}

bool dmi_yaml_entity_start(dmi_yaml_session_t *session, const dmi_entity_t *entity)
{
    assert(session != nullptr);

    bool success = false;
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

bool dmi_yaml_entity_attrs_start(dmi_yaml_session_t *session, const dmi_entity_t *entity)
{
    assert(session != nullptr);

    dmi_unused(entity);

    bool success = false;

    do {
        if (not dmi_yaml_label(session, "attributes"))
            break;
        if (not dmi_yaml_mapping_start(session, YAML_BLOCK_MAPPING_STYLE))
            break;

        success = true;
    } while (false);

    return success;
}

bool dmi_yaml_entity_attr(
        dmi_yaml_session_t    *session,
        const dmi_entity_t    *entity,
        const dmi_attribute_t *attr,
        const void            *data)
{
    dmi_unused(session);
    dmi_unused(entity);
    dmi_unused(attr);
    dmi_unused(data);

    return true;
}

bool dmi_yaml_entity_attr_array(
        dmi_yaml_session_t    *session,
        const dmi_attribute_t *attr,
        const dmi_data_t      *info,
        const void            *value)
{
    dmi_unused(session);
    dmi_unused(attr);
    dmi_unused(info);
    dmi_unused(value);

    return true;
}

bool dmi_yaml_entity_attr_struct(
        dmi_yaml_session_t    *session,
        const dmi_attribute_t *attr,
        const void            *value)
{
    dmi_unused(session);
    dmi_unused(attr);
    dmi_unused(value);

    return true;
}

bool dmi_yaml_entity_attr_value(
        dmi_yaml_session_t    *session,
        const dmi_attribute_t *attr,
        const void            *value)
{
    dmi_unused(session);
    dmi_unused(attr);
    dmi_unused(value);

    return true;
}

bool dmi_yaml_entity_attr_set(
        dmi_yaml_session_t    *session,
        const dmi_attribute_t *attr,
        const void            *value)
{
    dmi_unused(session);
    dmi_unused(attr);
    dmi_unused(value);

    return true;
}

bool dmi_yaml_entity_attrs_end(dmi_yaml_session_t *session, const dmi_entity_t *entity)
{
    assert(session != nullptr);

    dmi_unused(entity);

    return dmi_yaml_mapping_end(session);
}

bool dmi_yaml_entity_data(dmi_yaml_session_t *session, const dmi_entity_t *entity)
{
    dmi_unused(session);
    dmi_unused(entity);

    return true;
}

bool dmi_yaml_entity_strings(dmi_yaml_session_t *session, const dmi_entity_t *entity)
{
    dmi_unused(session);
    dmi_unused(entity);

    return true;
}

bool dmi_yaml_entity_end(dmi_yaml_session_t *session, const dmi_entity_t *entity)
{
    assert(session != nullptr);

    dmi_unused(entity);

    return dmi_yaml_mapping_end(session);
}

bool dmi_yaml_table_end(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    return dmi_yaml_sequence_end(session);
}

bool dmi_yaml_dump_end(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    bool success = false;
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

void dmi_yaml_finalize(dmi_yaml_session_t *session)
{
    assert(session != nullptr);

    yaml_emitter_close(session->emitter);
    yaml_emitter_delete(session->emitter);

    dmi_free(session->emitter);
}
