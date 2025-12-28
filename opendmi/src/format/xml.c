//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/format/xml.h>
#include <opendmi/format/xml/handlers.h>

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
