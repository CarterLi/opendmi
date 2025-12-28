//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_XML_HELPERS_H
#define OPENDMI_FORMAT_XML_HELPERS_H

#pragma once

#include <opendmi/format/xml/types.h>

__BEGIN_DECLS

bool dmi_xml_data(dmi_xml_session_t *session, const dmi_data_t *data, size_t length);

__END_DECLS

static inline const xmlChar *dmi_xml_string(const char *str)
{
    return (const xmlChar *)str;
}

#endif // !OPENDMI_FORMAT_XML_HELPERS_H
