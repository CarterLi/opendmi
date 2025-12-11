//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/oem-strings.h>

const dmi_attribute_t dmi_oem_strings_attrs[] =
{
    DMI_ATTRIBUTE(dmi_oem_strings_t, string_count, INTEGER, {
        .code = "string-count",
        .name = "String count"
    }),
    DMI_ATTRIBUTE_ARRAY(dmi_oem_strings_t, strings, string_count, STRING, {
        .code    = "strings",
        .name    = "Strings"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_oem_strings_table =
{
    .code       = "oem-strings",
    .name       = "OEM strings",
    .type       = DMI_TYPE_OEM_STRINGS,
    .min_length = 0x05,
    .attributes = dmi_oem_strings_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_oem_strings_decode,
        .free   = (dmi_table_free_fn_t)dmi_oem_strings_free
    }
};

dmi_oem_strings_t *dmi_oem_strings_decode(const dmi_table_t *table, dmi_version_t *plevel)
{
    dmi_oem_strings_t *info;
    const dmi_oem_strings_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_OEM_STRINGS));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->string_count = dmi_value(data->count);

    info->strings = dmi_alloc_array(table->context, sizeof(const char *), info->string_count);
    if (!info->strings) {
        dmi_free(info);
        return nullptr;
    }

    for (size_t i = 0; i < info->string_count; i++) {
        info->strings[i] = dmi_table_string(table, (dmi_string_t)(i + 1));
    }

    if (plevel)
        *plevel = dmi_version(2, 0, 0);

    return info;
}

void dmi_oem_strings_free(dmi_oem_strings_t *info)
{
    dmi_free(info->strings);
    dmi_free(info);
}
