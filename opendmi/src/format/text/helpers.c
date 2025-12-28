//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <assert.h>

#include <opendmi/format/text/helpers.h>

void dmi_text_hex_data(void *asession, const void *data, size_t length)
{
    assert(asession != nullptr);
    assert(data != nullptr);

    dmi_text_session_t *session = dmi_cast(session, asession);
    const unsigned char *ptr = dmi_cast(ptr, data);

    for (size_t i = 0; i < length; i++) {
        char sp = ' ';

        if (i % 0x10 == 0)
            fprintf(session->stream, "\t\t");
        if (i % 0x10 == 0x0f)
            sp = '\n';

        fprintf(session->stream, "%02X%c", (int)ptr[i], sp);
    }

    if (length % 0x10 != 0)
        fprintf(session->stream, "\n");
}
