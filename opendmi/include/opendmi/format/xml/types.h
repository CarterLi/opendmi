//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_XML_TYPES_H
#define OPENDMI_FORMAT_XML_TYPES_H

#pragma once

#include <stdio.h>

#include <libxml/xmlIO.h>
#include <libxml/xmlwriter.h>

#include <opendmi/types.h>
#include <opendmi/attribute.h>

#define DMI_XML_PREFIX    "dmi"
#define DMI_XML_NAMESPACE "http://opendmi.org/schema/opendmi.xsd"

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

#endif // !OPENDMI_FORMAT_XML_TYPES_H
