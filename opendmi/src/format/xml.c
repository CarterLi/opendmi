//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <libxml/xmlIO.h>
#include <libxml/xmlwriter.h>

#include <opendmi/format/xml.h>

static void dmi_xml_start(void *context);
static void dmi_xml_end(void *context);

typedef struct dmi_xml_context
{
    xmlOutputBuffer *buffer;
    xmlTextWriter *writer;
} dmi_xml_context_t;

const dmi_format_t dmi_xml_format =
{
    .code     = "xml",
    .name     = "XML",
    .handlers = {
        .start = dmi_xml_start,
        .end   = dmi_xml_end
    }
};

static void dmi_xml_start(void *context)
{
    (void)context;
}

static void dmi_xml_end(void *context)
{
    (void)context;
}
