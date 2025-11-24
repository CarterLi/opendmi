//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/utils.h>
#include <opendmi/table/firmware-language.h>

const dmi_attribute_t dmi_firmware_language_attrs[] =
{
    DMI_ATTRIBUTE(dmi_firmware_language_t, language_count, INTEGER, {
        .code = "language-count",
        .name = "Language count"
    }),
    DMI_ATTRIBUTE_ARRAY(dmi_firmware_language_t, languages, language_count, STRING, {
        .code = "languages",
        .name = "Languages"
    }),
    DMI_ATTRIBUTE(dmi_firmware_language_t, is_abbreviated, BOOL, {
        .code = "is-abbreviated",
        .name = "Abbreviated"
    }),
    DMI_ATTRIBUTE(dmi_firmware_language_t, current_language, STRING, {
        .code = "current-language",
        .name = "Current language"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_firmware_language_table =
{
    .tag        = "firmware-language",
    .name       = "Firmware language information",
    .type       = DMI_TYPE_FIRMWARE_LANGUAGE,
    .min_length = 0x05,
    .attributes = dmi_firmware_language_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_firmware_language_decode,
        .free   = (dmi_table_free_fn_t)dmi_firmware_language_free
    }
};

dmi_firmware_language_t *dmi_firmware_language_decode(const dmi_table_t *table)
{
    dmi_firmware_language_t *info = nullptr;
    dmi_firmware_language_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    info->language_count = dmi_value(data->language_count);

    info->languages = calloc(info->language_count, sizeof(const char *));
    if (!info->languages) {
        free(info);
        return nullptr;
    }

    for (size_t i = 0; i < info->language_count; i++) {
        info->languages[i] = dmi_table_string(table, i + 1);
    }

    dmi_firmware_language_flags_t flags = {
        ._value = dmi_value(data->flags)
    };

    info->is_abbreviated = flags.is_abbreviated;
    info->current_language = dmi_table_string(table, data->current_language);

    return info;
}

void dmi_firmware_language_free(dmi_firmware_language_t *info)
{
    free(info->languages);
    free(info);
}
