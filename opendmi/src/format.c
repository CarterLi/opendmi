//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "config.h"

#include <string.h>

#include <opendmi/format.h>
#include <opendmi/format/text.h>
#include <opendmi/format/json.h>
#include <opendmi/format/xml.h>
#include <opendmi/format/yaml.h>

const dmi_format_t *dmi_formats[] =
{
    &dmi_text_format,
#   ifdef ENABLE_JSON
        &dmi_json_format,
#   endif // ENABLE_JSON
#   ifdef ENABLE_XML
        &dmi_xml_format,
#   endif // ENABLE_XML
#   ifdef ENABLE_YAML
        &dmi_yaml_format,
#   endif
    nullptr
};

const dmi_format_t *dmi_format_get(const char *code)
{
    if (code == nullptr)
        return nullptr;

    for (size_t i = 0; dmi_formats[i]->code != nullptr; i++) {
        if (strcmp(dmi_formats[i]->code, code) == 0)
            return dmi_formats[i];
    }

    return nullptr;
}
