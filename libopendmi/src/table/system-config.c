//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/utils.h>
#include <opendmi/table/system-config.h>

const dmi_attribute_t dmi_system_config_opts_attrs[] =
{
    DMI_ATTRIBUTE(dmi_system_config_opts_t, option_count, INTEGER, {
        .code = "option-count",
        .name = "Option count"
    }),
    DMI_ATTRIBUTE_ARRAY(dmi_system_config_opts_t, options, option_count, STRING, {
        .code    = "options",
        .name    = "Options"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_system_config_opts_table =
{
    .tag        = "system-config-options",
    .name       = "System configuration options",
    .type       = DMI_TYPE_SYSTEM_CONFIG_OPTIONS,
    .min_length = 0x05,
    .attributes = dmi_system_config_opts_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_system_config_opts_decode,
        .free   = (dmi_table_free_fn_t)dmi_system_config_opts_free
    }
};

dmi_system_config_opts_t *dmi_system_config_opts_decode(const dmi_table_t *table)
{
    dmi_system_config_opts_t *info = nullptr;
    dmi_system_config_opts_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    info->option_count = dmi_value(data->count);

    info->options = calloc(info->option_count, sizeof(const char *));
    if (!info->options) {
        free(info);
        return nullptr;
    }

    for (size_t i = 0; i < info->option_count; i++) {
        info->options[i] = dmi_table_string(table, i + 1);
    }

    return info;
}

void dmi_system_config_opts_free(dmi_system_config_opts_t *info)
{
    free(info->options);
    free(info);
}
