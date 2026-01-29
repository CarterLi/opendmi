//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/codec.h>

#include <opendmi/entity/firmware-language.h>

static bool dmi_firmware_language_decode(dmi_entity_t *entity);
static void dmi_firmware_language_cleanup(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_firmware_language_spec =
{
    .code            = "firmware-language",
    .name            = "Firmware language information",
    .type            = DMI_TYPE(FIRMWARE_LANGUAGE),
    .minimum_version = DMI_VERSION(2, 0, 0),
    .minimum_length  = 0x05,
    .decoded_length  = sizeof(dmi_firmware_language_t),
    .attributes      = (dmi_attribute_t[]) {
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
    },
    .handlers = {
        .decode  = dmi_firmware_language_decode,
        .cleanup = dmi_firmware_language_cleanup
    }
};

static bool dmi_firmware_language_decode(dmi_entity_t *entity)
{
    dmi_firmware_language_t *info;
    const dmi_firmware_language_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_FIRMWARE_LANGUAGE);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_FIRMWARE_LANGUAGE);
    if (info == nullptr)
        return false;

    info->language_count = dmi_decode(data->language_count);

    info->languages = dmi_alloc_array(entity->context, sizeof(const char *), info->language_count);
    if (info->languages == nullptr)
        return false;

    for (size_t i = 0; i < info->language_count; i++) {
        info->languages[i] = dmi_entity_string(entity, (dmi_string_t)(i + 1));
    }

    dmi_firmware_language_flags_t flags = {
        .__value = dmi_decode(data->flags)
    };

    info->is_abbreviated   = flags.is_abbreviated;
    info->current_language = dmi_entity_string(entity, data->current_language);

    return true;
}

static void dmi_firmware_language_cleanup(dmi_entity_t *entity)
{
    dmi_firmware_language_t *info;

    info = dmi_entity_info(entity, DMI_TYPE_FIRMWARE_LANGUAGE);
    if (info == nullptr)
        return;

    dmi_free(info->languages);
}
