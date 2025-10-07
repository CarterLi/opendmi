//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>

#include <opendmi/entry.h>
#include <opendmi/utils.h>

static void dmi_entry_version_fixup(dmi_context_t *context);

static bool dmi_entry_decode_legacy(dmi_context_t *context,
                                    const void *data, size_t length);
static bool dmi_entry_decode_v21(dmi_context_t *context,
                                 const void *data, size_t length);
static bool dmi_entry_decode_v30(dmi_context_t *context,
                                 const void *data, size_t length);

static const dmi_entry_spec_t dmi_entry_specs[] =
{
    {
        .name       = "SMBIOS 3.0+ (64-bit)",
        .anchor     = DMI_ANCHOR_V30,
        .min_length = sizeof(dmi_entry_v30_t),
        .handler    = dmi_entry_decode_v30
    },
    {
        .name       = "SMBIOS 2.1+ (32-bit)",
        .anchor     = DMI_ANCHOR_V21,
        .min_length = sizeof(dmi_entry_v21_t),
        .handler    = dmi_entry_decode_v21
    },
    {
        .name       = "Legacy (32-bit)",
        .anchor     = DMI_ANCHOR_LEGACY,
        .min_length = sizeof(dmi_entry_legacy_t),
        .handler    = dmi_entry_decode_legacy
    },
    DMI_ENTRY_SPEC_NULL
};

bool dmi_entry_decode(dmi_context_t *context, const void *data, size_t length)
{
    if ((context == nullptr) || (data == nullptr) || (length == 0)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    const dmi_entry_spec_t *spec = nullptr;

    for (spec = dmi_entry_specs; spec->name != nullptr; spec++) {
        if (length < spec->min_length)
            continue;
        if  (memcmp(data, spec->anchor, strlen(spec->anchor)) == 0)
            break;
    }

    if (spec->name == nullptr) {
        dmi_set_error(context, DMI_ERROR_UNKNOWN_EPS_ANCHOR);
        return false;
    }

    return spec->handler(context, data, length);
}

static bool dmi_entry_decode_legacy(dmi_context_t *context,
                                    const void *data, size_t length)
{
    if ((context == nullptr) || (data == nullptr) || (length < sizeof(dmi_entry_legacy_t))) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    const dmi_entry_legacy_t *entry = (dmi_entry_legacy_t *)data;

    // Verify EPS checksum value
    if (!dmi_checksum(data, sizeof(dmi_entry_legacy_t))) {
        dmi_set_error(context, DMI_ERROR_INVALID_EPS_CHECKSUM);
        return false;
    }

    // Decode SMBIOS version
    if ((entry->version != 0) && (context->smbios_version == 0)) {
        uint8_t major = (entry->version & 0xF0) >> 4;
        uint8_t minor = (entry->version & 0x0F);

        context->smbios_version = dmi_version(minor, major, 0);
    }

    // Decode table area parameters
    context->table_count         = entry->table_count;
    context->table_area_addr     = entry->table_area_addr;
    context->table_area_max_size = entry->table_area_size;
    context->table_area_size     = entry->table_area_size;

    return true;
}

static bool dmi_entry_decode_v21(dmi_context_t *context,
                                 const void *data, size_t length)
{
    if ((context == nullptr) || (data == nullptr) || (length < sizeof(dmi_entry_v21_t))) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    const dmi_entry_v21_t *entry = (dmi_entry_v21_t *)data;

    // Check maximum entry point length to prevent checksum run beyond
    // the buffer.
    if (entry->length > sizeof(dmi_entry_v21_t)) {
        dmi_set_error(context, DMI_ERROR_INVALID_EPS_LENGTH);
        return false;
    }

    // Check minimum entry point length. The size of this structure is 0x1F
    // bytes, but we also accept value 0x1E due to a mistake in SMBIOS
    // specification version 2.1.
    if (entry->length < sizeof(dmi_entry_v21_t) - 1) {
        dmi_set_error(context, DMI_ERROR_INVALID_EPS_LENGTH);
        return false;
    }

    // Verify EPS checksum value
    if (!dmi_checksum(data, entry->length)) {
        dmi_set_error(context, DMI_ERROR_INVALID_EPS_CHECKSUM);
        return false;
    }

    // Decode SMBIOS version
    context->smbios_version = dmi_version(entry->version_major,
                                          entry->version_minor,
                                          entry->revision);
    dmi_entry_version_fixup(context);

    // Decode table parameters
    context->table_max_size = entry->table_max_size;

    return dmi_entry_decode_legacy(context, (void *)&entry->ieps, sizeof(entry->ieps));
}

static bool dmi_entry_decode_v30(dmi_context_t *context,
                                 const void *data, size_t length)
{
    if ((context == nullptr) || (data == nullptr) || (length < sizeof(dmi_entry_v30_t))) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    const dmi_entry_v30_t *entry = (dmi_entry_v30_t *)data;

    // Check maximum entry point length to prevent checksum run beyond
    // the buffer.
    if (entry->length > sizeof(dmi_entry_v30_t)) {
        dmi_set_error(context, DMI_ERROR_INVALID_EPS_LENGTH);
        return false;
    }

    // Check minimum entry point length.
    if (entry->length < sizeof(dmi_entry_v30_t)) {
        dmi_set_error(context, DMI_ERROR_INVALID_EPS_LENGTH);
        return false;
    }

    // Verify EPS checksum value
    if (!dmi_checksum(data, entry->length)) {
        dmi_set_error(context, DMI_ERROR_INVALID_EPS_CHECKSUM);
        return false;
    }

    // Decode SMBIOS version
    context->smbios_version = dmi_version(entry->version_major,
                                          entry->version_minor,
                                          entry->revision);

    // Decode table parameters
    context->table_area_addr     = entry->table_area_addr;
    context->table_area_max_size = entry->table_area_max_size;

    return true;
}

static void dmi_entry_version_fixup(dmi_context_t *context)
{
    unsigned int major    = dmi_version_major(context->smbios_version);
    unsigned int minor    = dmi_version_minor(context->smbios_version);
    unsigned int revision = dmi_version_revision(context->smbios_version);

    if (major != 2)
        return;

    // Some BIOS report weird SMBIOS version, fix that up
    switch (minor) {
    case 0x1F:
    case 0x21:
        minor = 3;
        break;

    case 0x33:
        minor = 6;
        break;

    default:
        return;
    }

    context->smbios_version = dmi_version(major, minor, revision);
}
