//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/format/yaml.h>

static void *dmi_yaml_initialize(dmi_context_t *context, FILE *stream);

static void dmi_yaml_finalize(void *asession);

const dmi_format_t dmi_yaml_format =
{
    .code     = "yaml",
    .name     = "YAML",
    .handlers = {
        .initialize = dmi_yaml_initialize,
        .finalize   = dmi_yaml_finalize
    }
};

static void *dmi_yaml_initialize(dmi_context_t *context, FILE *stream)
{
    DMI_UNUSED(context);
    DMI_UNUSED(stream);
}

static void dmi_yaml_finalize(void *asession)
{
    DMI_UNUSED(asession);
}
