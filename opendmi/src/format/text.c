//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/format/text.h>
#include <opendmi/format/text/handlers.h>

const dmi_format_t dmi_text_format =
{
    .code = "text",
    .name = "Plain text",
    .handlers = {
        .initialize     = dmi_text_initialize,
        .entry          = dmi_text_entry,
        .entity_start   = dmi_text_entity_start,
        .entity_attr    = dmi_text_entity_attr,
        .entity_data    = dmi_text_entity_data,
        .entity_strings = dmi_text_entity_strings,
        .entity_end     = dmi_text_entity_end,
        .finalize       = dmi_text_finalize
    }
};
