//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <time.h>
#include <assert.h>

#include <libxml/xmlIO.h>
#include <libxml/xmlwriter.h>

#include <opendmi/context.h>
#include <opendmi/error.h>
#include <opendmi/utils.h>

#include <opendmi/format/xml.h>

typedef struct dmi_xml_session
{
    dmi_context_t *context;
    xmlOutputBuffer *buffer;
    xmlTextWriter *writer;
} dmi_xml_session_t;

static void *dmi_xml_initialize(dmi_context_t *context, FILE *stream);
static bool  dmi_xml_dump_start(void *asession);
static bool  dmi_xml_entry(void *asession);
static bool  dmi_xml_table_start(void *asession);
static bool  dmi_xml_table_attr(void *asession);
static bool  dmi_xml_table_data(void *asession);
static bool  dmi_xml_table_strings(void *asession);
static bool  dmi_xml_table_end(void *asession);
static bool  dmi_xml_dump_end(void *asession);
static void  dmi_xml_finalize(void *asession);

const dmi_format_t dmi_xml_format =
{
    .code     = "xml",
    .name     = "XML",
    .handlers = {
        .initialize    = dmi_xml_initialize,
        .dump_start    = dmi_xml_dump_start,
        .entry         = dmi_xml_entry,
        .table_start   = dmi_xml_table_start,
        .table_attr    = dmi_xml_table_attr,
        .table_data    = dmi_xml_table_data,
        .table_strings = dmi_xml_table_strings,
        .table_end     = dmi_xml_table_end,
        .dump_end      = dmi_xml_dump_end,
        .finalize      = dmi_xml_finalize
    }
};

static inline const xmlChar *dmi_xml_string(const char *str)
{
    return (const xmlChar *)str;
}

static void *dmi_xml_initialize(dmi_context_t *context, FILE *stream)
{
    bool success = false;
    dmi_xml_session_t *session;

    assert(context != nullptr);
    assert(stream != nullptr);

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

        success = true;
    } while (false);

    if (!success) {
        if (session->writer != nullptr)
            xmlFreeTextWriter(session->writer);
        else
            xmlOutputBufferClose(session->buffer);

        return nullptr;
    }

    session->context = context;

    return session;
}

static bool dmi_xml_dump_start(void *asession)
{
    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);
    char *timestamp = nullptr;

    assert(session != nullptr);

    do {
        time_t t;
        struct tm tm;
        int rv;

        t = time(nullptr);
        if (t == (time_t)-1) {
            dmi_error_raise_ex(session->context, DMI_ERROR_SYSTEM, "Unable to get current time");
            break;
        }
        if (gmtime_r(&t, &tm) == nullptr) {
            dmi_error_raise_ex(session->context, DMI_ERROR_SYSTEM, "Unable to convert current time");
            break;
        }

        rv = asprintf(
                &timestamp,
                "%04u-%02u-%02uT%02u:%02u:%02u",
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                tm.tm_hour, tm.tm_min, tm.tm_sec);
        if (rv < 0) {
            dmi_error_raise(session->context, DMI_ERROR_OUT_OF_MEMORY);
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
        if (xmlTextWriterWriteAttribute(
                    session->writer,
                    dmi_xml_string("created-at"),
                    dmi_xml_string(timestamp)) < 0)
            break;

        success = true;
    } while (false);

    dmi_free(timestamp);

    return success;
}

static bool dmi_xml_entry(void *asession)
{
    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);
    char *smbios_version = nullptr;

    assert(session != nullptr);

    do {
        int rv;

        rv = asprintf(
                &smbios_version, "%d.%d.%d",
                dmi_version_major(session->context->smbios_version),
                dmi_version_minor(session->context->smbios_version),
                dmi_version_revision(session->context->smbios_version));
        if (rv < 0) {
            dmi_error_raise(session->context, DMI_ERROR_OUT_OF_MEMORY);
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
        if (xmlTextWriterEndElement(session->writer) < 0)
            break;

        success = true;
    } while (false);

    dmi_free(smbios_version);

    return success;
}

static bool dmi_xml_table_start(void *asession)
{
    (void)asession;

    return true;
}

static bool dmi_xml_table_attr(void *asession)
{
    (void)asession;

    return true;
}

static bool dmi_xml_table_data(void *asession)
{
    (void)asession;

    return true;
}

static bool dmi_xml_table_strings(void *asession)
{
    (void)asession;

    return true;
}

static bool dmi_xml_table_end(void *asession)
{
    (void)asession;

    return true;
}

static bool dmi_xml_dump_end(void *asession)
{
    bool success = false;
    dmi_xml_session_t *session = dmi_cast(session, asession);

    do {
        if (xmlTextWriterEndElement(session->writer) < 0)
            break;

        success = true;
    } while (false);

    return success;
}

static void dmi_xml_finalize(void *asession)
{
    dmi_xml_session_t *session = dmi_cast(session, asession);

    assert(session != nullptr);

    xmlFreeTextWriter(session->writer);
    dmi_free(session);
}
