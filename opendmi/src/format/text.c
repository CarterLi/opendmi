//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
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
        .initialize     = (dmi_format_initialize_fn_t)dmi_text_initialize,
        .entry          = (dmi_format_entry_fn_t)dmi_text_entry,
        .entity_start   = (dmi_format_entity_start_fn_t)dmi_text_entity_start,
        .entity_attr    = (dmi_format_entity_attr_fn_t)dmi_text_entity_attr,
        .entity_data    = (dmi_format_entity_data_fn_t)dmi_text_entity_data,
        .entity_strings = (dmi_format_entity_strings_fn_t)dmi_text_entity_strings,
        .entity_end     = (dmi_format_entity_end_fn_t)dmi_text_entity_end,
        .finalize       = (dmi_format_finalize_fn_t)dmi_text_finalize
    }
};
