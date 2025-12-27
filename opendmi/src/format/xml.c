//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <time.h>
#include <inttypes.h>
#include <assert.h>

#include <libxml/xmlIO.h>
#include <libxml/xmlwriter.h>

#include <opendmi/context.h>
#include <opendmi/error.h>
#include <opendmi/utils.h>

#include <opendmi/format/xml.h>

typedef struct dmi_xml_session
{
    /**
     * @brief Context handle.
     */
    dmi_context_t *context;

    /**
     * @brief Output stream.
     */
    FILE *stream;

    /**
     * @brief XML output buffer.
     */
    xmlOutputBuffer *buffer;

    /**
     * @brief XML writer handle.
     */
    xmlTextWriter *writer;
} dmi_xml_session_t;

static void *dmi_xml_initialize(dmi_context_t *context, FILE *stream);

static bool dmi_xml_dump_start(void *asession);
static bool dmi_xml_entry(void *asession);
static bool dmi_xml_entity_start(void *asession, const dmi_entity_t *entity);
static bool dmi_xml_entity_attrs_start(void *asession, const dmi_entity_t *entity);

static bool dmi_xml_entity_attr(
        void                  *asession,
        const dmi_entity_t     *entity,
        const dmi_attribute_t *attr,
        const void            *data);

static bool dmi_xml_entity_attr_array(
        void                  *asession,
        const dmi_attribute_t *attr,
        const dmi_data_t      *info,
        const void            *value);

static bool dmi_xml_entity_attr_struct(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value);

static bool dmi_xml_entity_attr_value(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value);

static bool dmi_xml_entity_attr_set(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value);

static bool dmi_xml_entity_attrs_end(void *asession, const dmi_entity_t *entity);
static bool dmi_xml_entity_data(void *asession, const dmi_entity_t *entity);
static bool dmi_xml_entity_strings(void *asession, const dmi_entity_t *entity);
static bool dmi_xml_entity_end(void *asession, const dmi_entity_t *entity);
static bool dmi_xml_dump_end(void *asession);

static void dmi_xml_finalize(void *asession);

const dmi_format_t dmi_xml_format =
{
    .code     = "xml",
    .name     = "XML",
    .handlers = {
        .initialize         = dmi_xml_initialize,
        .dump_start         = dmi_xml_dump_start,
        .entry              = dmi_xml_entry,
        .entity_start       = dmi_xml_entity_start,
        .entity_attrs_start = dmi_xml_entity_attrs_start,
        .entity_attr        = dmi_xml_entity_attr,
        .entity_attrs_end   = dmi_xml_entity_attrs_end,
        .entity_data        = dmi_xml_entity_data,
        .entity_strings     = dmi_xml_entity_strings,
        .entity_end         = dmi_xml_entity_end,
        .dump_end           = dmi_xml_dump_end,
        .finalize           = dmi_xml_finalize
    }
};

static inline const xmlChar *dmi_xml_string(const char *str)
{
    return (const xmlChar *)str;
}

static void *dmi_xml_initialize(dmi_context_t *context, FILE *stream)
{
    assert(context != nullptr);
    assert(stream != nullptr);

    bool success = false;
    dmi_xml_session_t *session;

    session = dmi_alloc(context, sizeof(*session));
    if (session == nullptr) {
        dmi_error_raise(context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    do {
        session->buffer = xmlOutputBufferCreateFile(stream, nullptr);
        if (session->buffer == nullptr) {
            dmi_error_raise_ex(context, DMI_ERROR_INTERNAL, "Unable to create xmlOutputBuffer");
            break;
        }

        session->writer = xmlNewTextWriter(session->buffer);
        if (session->writer == nullptr) {
            dmi_error_raise_ex(context, DMI_ERROR_INTERNAL, "Unable to create xmlWriter");
            break;
        }

        if (xmlTextWriterSetIndent(session->writer, 1) < 0) {
            dmi_error_raise_ex(context, DMI_ERROR_INTERNAL, "Unable to configure xmlWriter indentation");
            break;
        }
        if (xmlTextWriterSetIndentString(session->writer, dmi_xml_string("  ")) < 0) {
            dmi_error_raise_ex(context, DMI_ERROR_INTERNAL, "Unable to configure xmlWriter indentation");
            break;
        }

        success = true;
    } while (false);

    if (not success) {
        if (session->writer != nullptr)
            xmlFreeTextWriter(session->writer);
        else
            xmlOutputBufferClose(session->buffer);

        return nullptr;
    }

    session->context = context;
    session->stream  = stream;

    return session;
}

static bool dmi_xml_dump_start(void *asession)
{
    assert(asession != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    do {
        time_t t;
        struct tm tm;

        t = time(nullptr);
        if (t == (time_t)-1) {
            dmi_error_raise_ex(session->context, DMI_ERROR_SYSTEM, "Unable to get current time");
            break;
        }
        if (gmtime_r(&t, &tm) == nullptr) {
            dmi_error_raise_ex(session->context, DMI_ERROR_SYSTEM, "Unable to convert current time");
            break;
        }

        if (xmlTextWriterStartDocument(session->writer, "1.0", "UTF-8", NULL) < 0)
            break;

        if (xmlTextWriterStartElementNS(
                    session->writer,
                    dmi_xml_string(DMI_XML_PREFIX),
                    dmi_xml_string("dump"),
                    dmi_xml_string(DMI_XML_NAMESPACE)) < 0)
            break;
        if (xmlTextWriterWriteFormatAttribute(
                    session->writer,
                    dmi_xml_string("created-at"),
                    "%04u-%02u-%02uT%02u:%02u:%02u",
                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                    tm.tm_hour, tm.tm_min, tm.tm_sec) < 0)
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_xml_entry(void *asession)
{
    assert(asession != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);
    dmi_context_t *context = session->context;
    char *smbios_version = nullptr;

    do {
        smbios_version = dmi_version_format(context->smbios_version);
        if (smbios_version == nullptr) {
            dmi_error_raise(context, DMI_ERROR_OUT_OF_MEMORY);
            break;
        }

        if (xmlTextWriterStartElementNS(
                    session->writer,
                    dmi_xml_string(DMI_XML_PREFIX),
                    dmi_xml_string("entry"),
                    nullptr) < 0)
            break;

        if (xmlTextWriterWriteAttribute(
                    session->writer,
                    dmi_xml_string("smbios-version"),
                    dmi_xml_string(smbios_version)) < 0)
            break;
        if (xmlTextWriterWriteFormatAttribute(
                    session->writer,
                    dmi_xml_string("table-area-address"),
                    "0x%" PRIx64, context->table_area_addr) < 0)
            break;
        if (xmlTextWriterWriteFormatAttribute(
                    session->writer,
                    dmi_xml_string("table-area-size"),
                    "%zu", context->table_area_size) < 0)
            break;

        if (xmlTextWriterEndElement(session->writer) < 0)
            break;

        success = true;
    } while (false);

    dmi_free(smbios_version);

    return success;
}

static bool dmi_xml_entity_start(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);
    assert(entity != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    do {
        if (xmlTextWriterStartElementNS(
                    session->writer,
                    dmi_xml_string(DMI_XML_PREFIX),
                    dmi_xml_string("entity"),
                    nullptr) < 0)
            break;

        if (xmlTextWriterWriteFormatAttribute(
                    session->writer,
                    dmi_xml_string("handle"),
                    "0x%04hx", entity->handle) < 0)
            break;
        if (xmlTextWriterWriteFormatAttribute(
                    session->writer,
                    dmi_xml_string("type"),
                    "%u", entity->type) < 0)
            break;
        if (xmlTextWriterWriteFormatAttribute(
                    session->writer,
                    dmi_xml_string("length"),
                    "%zu", entity->total_length) < 0)
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_xml_entity_attrs_start(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);
    assert(entity != nullptr);

    dmi_xml_session_t *session = dmi_cast(session, asession);

    if (xmlTextWriterStartElementNS(
                session->writer,
                dmi_xml_string(DMI_XML_PREFIX),
                dmi_xml_string(entity->spec->code),
                nullptr) < 0)
        return false;

    return true;
}

static bool dmi_xml_entity_attr(
        void                  *asession,
        const dmi_entity_t     *entity,
        const dmi_attribute_t *attr,
        const void            *value)
{
    assert(asession != nullptr);
    assert(entity != nullptr);
    assert(attr != nullptr);
    assert(value != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    do {
        bool rv;

        if (xmlTextWriterStartElement(session->writer, dmi_xml_string(attr->params.code)) < 0)
            break;

        if (attr->counter < 0) {
            if (attr->type == DMI_ATTRIBUTE_TYPE_STRUCT)
                rv = dmi_xml_entity_attr_struct(session, attr, value);
            else
                rv = dmi_xml_entity_attr_value(session, attr, value);
        } else {
            rv = dmi_xml_entity_attr_array(session, attr, entity->info, value);
        }
        if (not rv)
            break;

        if (xmlTextWriterFullEndElement(session->writer) < 0)
           break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_xml_entity_attr_array(
        void                  *asession,
        const dmi_attribute_t *attr,
        const dmi_data_t      *info,
        const void            *value)
{
    assert(asession != nullptr);
    assert(attr != nullptr);
    assert(info != nullptr);
    assert(value != nullptr);

    dmi_xml_session_t *session = dmi_cast(session, asession);

    size_t count = *(size_t *)(info + attr->counter);
    const dmi_data_t *ptr = *(const dmi_data_t **)value;

    for (size_t i = 0; i < count; i++, ptr += attr->size) {
        if (xmlTextWriterStartElement(session->writer, dmi_xml_string("item")) < 0)
            return false;

        if (attr->type == DMI_ATTRIBUTE_TYPE_STRUCT) {
            if (not dmi_xml_entity_attr_struct(session, attr, ptr))
                return false;
        } else {
            if (not dmi_xml_entity_attr_value(session, attr, ptr))
                return false;
        }

        if (xmlTextWriterFullEndElement(session->writer) < 0)
            return false;
    }

    return true;
}

static bool dmi_xml_entity_attr_struct(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value)
{
    assert(asession != nullptr);
    assert(attr != nullptr);
    assert(value != nullptr);

    dmi_xml_session_t *session = dmi_cast(session, asession);
    const dmi_attribute_t *child_attr = nullptr;

    for (child_attr = attr->params.attrs; child_attr->params.name; child_attr++) {
        const dmi_data_t *ptr = (dmi_data_t *)value + child_attr->offset;

        if (xmlTextWriterStartElement(session->writer, dmi_xml_string(child_attr->params.code)) < 0)
            return false;

        if (not dmi_xml_entity_attr_value(session, child_attr, ptr))
            return false;

        if (xmlTextWriterFullEndElement(session->writer) < 0)
            return false;
    }

    return true;
}

static bool dmi_xml_entity_attr_value(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value)
{
    assert(asession != nullptr);
    assert(attr != nullptr);
    assert(value != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);
    char *text = nullptr;

    // Write empty tag if the value is unspecified
    if (dmi_attribute_is_unspecified(attr, value))
        return true;

    // Handle unknown values
    if (dmi_attribute_is_unknown(attr, value)) {
        if (xmlTextWriterWriteString(session->writer, dmi_xml_string("unknown")) < 0)
            return false;
        return true;
    }

    // Handle value sets
    if (attr->type == DMI_ATTRIBUTE_TYPE_SET)
        return dmi_xml_entity_attr_set(session, attr, value);

    do {
        text = dmi_attribute_format(attr, value, false);
        if (text == nullptr)
            break;

        if (attr->params.unit) {
            if (xmlTextWriterWriteAttribute(
                        session->writer,
                        dmi_xml_string("units"),
                        dmi_xml_string(attr->params.unit)) < 0)
                break;
        }

        if (xmlTextWriterWriteString(session->writer, dmi_xml_string(text)) < 0)
            break;

        success = true;
    } while (false);

    dmi_free(text);

    return success;
}

static bool dmi_xml_entity_attr_set(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value)
{

    assert(asession != nullptr);
    assert(attr != nullptr);
    assert(value != nullptr);

    uint64_t mask;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    if (attr->size == sizeof(int8_t))
        mask = *(uint8_t *)value;
    else if (attr->size == sizeof(uint16_t))
        mask = *(uint16_t *)value;
    else if (attr->size == sizeof(uint32_t))
        mask = *(uint32_t *)value;
    else if (attr->size == sizeof(uint64_t))
        mask = *(uint64_t *)value;
    else
        return false;

    if (xmlTextWriterWriteFormatAttribute(
                session->writer,
                dmi_xml_string("value"),
                "0x%" PRIx64, mask) < 0)
        return false;

    for (unsigned i = 0; i < attr->size * CHAR_BIT; i++) {
        const char *name = dmi_code_lookup(attr->params.values, i);
        if (!name)
            continue;

        bool flag = mask & (1 << i);

        if (xmlTextWriterWriteElement(
                    session->writer,
                    dmi_xml_string(name),
                    dmi_xml_string(flag ? "true" : "false")) < 0)
            return false;
    }

    return true;
}

static bool dmi_xml_entity_attrs_end(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);
    assert(entity != nullptr);

    dmi_unused(entity);

    dmi_xml_session_t *session = dmi_cast(session, asession);

    if (xmlTextWriterFullEndElement(session->writer) < 0)
        return false;

    return true;
}

static bool dmi_xml_entity_data(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);
    assert(entity != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    do {
        if (xmlTextWriterStartElementNS(
                    session->writer,
                    dmi_xml_string(DMI_XML_PREFIX),
                    dmi_xml_string("data"),
                    nullptr) < 0)
            break;

        if (xmlTextWriterStartCDATA(session->writer) < 0)
            break;
        if (xmlTextWriterWriteBase64(session->writer, (const char *)entity->data, 0, entity->body_length) < 0)
            break;
        if (xmlTextWriterEndCDATA(session->writer) < 0)
            break;

        if (xmlTextWriterFullEndElement(session->writer) < 0)
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_xml_entity_strings(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);
    assert(entity != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    if (entity->string_count == 0)
        return true;

    do {
        if (xmlTextWriterStartElementNS(
                    session->writer,
                    dmi_xml_string(DMI_XML_PREFIX),
                    dmi_xml_string("strings"),
                    nullptr) < 0)
            break;

        for (size_t i = 1; i <= entity->string_count; i++) {
            if (xmlTextWriterStartElementNS(
                        session->writer,
                        dmi_xml_string(DMI_XML_PREFIX),
                        dmi_xml_string("string"),
                        nullptr) < 0)
                break;
            if (xmlTextWriterWriteFormatAttribute(
                        session->writer,
                        dmi_xml_string("index"),
                        "%zu", i) < 0)
                break;

            if (xmlTextWriterWriteString(
                        session->writer,
                        dmi_xml_string(dmi_entity_string(entity, i))) < 0)
                break;

            if (xmlTextWriterFullEndElement(session->writer) < 0)
                break;
        }

        if (xmlTextWriterFullEndElement(session->writer) < 0)
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_xml_entity_end(void *asession, const dmi_entity_t *entity)
{
    assert(asession != nullptr);
    assert(entity != nullptr);

    dmi_unused(entity);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    do {
        if (xmlTextWriterFullEndElement(session->writer) < 0)
            break;

        success = true;
    } while (false);

    return success;
}

static bool dmi_xml_dump_end(void *asession)
{
    assert(asession != nullptr);

    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    do {
        if (xmlTextWriterEndDocument(session->writer) < 0)
            break;
        if (xmlTextWriterFlush(session->writer) < 0)
            break;

        success = true;
    } while (false);

    return success;
}

static void dmi_xml_finalize(void *asession)
{
    assert(asession != nullptr);

    dmi_xml_session_t *session = dmi_cast(session, asession);

    xmlFreeTextWriter(session->writer);
    dmi_free(session);
}
