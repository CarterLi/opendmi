//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <assert.h>

#include <opendmi/format/xml/helpers.h>

bool dmi_xml_data(dmi_xml_session_t *session, const dmi_data_t *data, size_t length)
{
    assert(session != nullptr);
    assert(data != nullptr);
    assert(length > 0);

    bool success = false;

    do {
        if (xmlTextWriterStartCDATA(session->writer) < 0)
            break;
        if (xmlTextWriterWriteBase64(session->writer, (const char *)data, 0, length) < 0)
            break;
        if (xmlTextWriterEndCDATA(session->writer) < 0)
            break;

        success = true;
    } while (false);

    return success;
}
