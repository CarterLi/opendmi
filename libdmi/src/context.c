//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>

#include <opendmi/context.h>

static void dmi_version_fixup(dmi_context_t *context);

static __thread dmi_error_t dmi_last_error = DMI_OK;

dmi_context_t *dmi_open(void)
{
    dmi_context_t *context = nullptr;

    context = malloc(sizeof(dmi_context_t));
    if (context == nullptr) {
        dmi_set_error(nullptr,  DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }
    memset(context, 0, sizeof(dmi_context_t));

    // Fixup SMBIOS version number
    dmi_version_fixup(context);

    return nullptr;
}

dmi_context_t *dmi_dump_load(const char *path)
{
    if (path == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }

    return nullptr;
}

bool dmi_dump_save(dmi_context_t *context, const char *path)
{
    if ((context == nullptr) || (path == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    return true;
}

void dmi_set_error(dmi_context_t *context, dmi_error_t error)
{
    if (context != nullptr)
        context->last_error = error;
    else
        dmi_last_error = error;
}

dmi_error_t dmi_get_error(const dmi_context_t *context)
{
    if (context == nullptr)
        return dmi_last_error;

    return context->last_error;
}

void dmi_close(dmi_context_t *context)
{
    if (context == nullptr)
        return;

    free(context);
}

static void dmi_version_fixup(dmi_context_t *context)
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
