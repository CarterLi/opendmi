//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/format/yaml.h>
#include <opendmi/format/yaml/handlers.h>

const dmi_format_t dmi_yaml_format =
{
    .code     = "yaml",
    .name     = "YAML",
    .handlers = {
        .initialize     = dmi_yaml_initialize,
        .dump_start     = dmi_yaml_dump_start,
        .entry          = dmi_yaml_entry,
        .table_start    = dmi_yaml_table_start,
        .entity_start   = dmi_yaml_entity_start,
        .entity_attr    = dmi_yaml_entity_attr,
        .entity_data    = dmi_yaml_entity_data,
        .entity_strings = dmi_yaml_entity_strings,
        .entity_end     = dmi_yaml_entity_end,
        .table_end      = dmi_yaml_table_end,
        .dump_end       = dmi_yaml_dump_end,
        .finalize       = dmi_yaml_finalize
    }
};
