//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/entry.h>
#include <opendmi/table.h>

#include <opendmi/backend/dump.h>
#if defined(__linux__)
#include <opendmi/backend/linux.h>
#define DMI_BACKEND dmi_linux_backend
#elif defined(__APPLE__)
#include <opendmi/backend/darwin.h>
#define DMI_BACKEND dmi_darwin_backend
#elif defined(__FreeBSD__)
#include <opendmi/backend/freebsd.h>
#define DMI_BACKEND dmi_freebsd_backend
#elif defined(__WINNT__)
#include <opendmi/backend/windows.h>
#define DMI_BACKEND dmi_windows_backend
#else
#error "Unsupported OS type"
#endif

static dmi_context_t *dmi_context_create(dmi_backend_t *backend, const void *arg);

/**
 * @internal
 * @brief Fixup DMI version number.
 */
static void dmi_version_fixup(dmi_context_t *context);

/**
 * @brief Last error code (thread-local).
 */
static __thread dmi_error_t dmi_last_error = DMI_OK;

/**
 * @brief Backend handle.
 */
static dmi_backend_t *dmi_backend = &DMI_BACKEND;

dmi_context_t *dmi_open(void)
{
    return dmi_context_create(dmi_backend, nullptr);
}

dmi_context_t *dmi_dump_load(const char *path)
{
    if (path == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }

    return dmi_context_create(dmi_backend, path);
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

static dmi_context_t *dmi_context_create(dmi_backend_t *backend, const void *arg)
{
    dmi_context_t *context = nullptr;

    // Allocate context descriptor
    context = malloc(sizeof(dmi_context_t));
    if (context == nullptr) {
        dmi_set_error(nullptr,  DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }
    memset(context, 0, sizeof(dmi_context_t));

    // Initialize context
    bool success = false;
    do {
        context->backend = backend;

        // Initialize backend
        if (!context->backend->open(context, arg))
            break;

        // Read and decode entry point
        context->entry_data = context->backend->read_entry(context, &context->entry_size);
        if (context->entry_data == nullptr)
            break;
        if (!dmi_entry_decode(context, context->entry_data, context->entry_size))
            break;

        // Fixup SMBIOS version number
        dmi_version_fixup(context);

        // Read and decode SMBIOS tables
        // TODO: Use separate variable for size
        context->table_data = context->backend->read_tables(context, &context->table_area_size);
        if (context->table_data == nullptr)
            break;
        if (!dmi_table_scan(context))
            break;

        success = true;
    } while (false);

    if (!success) {
        dmi_set_error(nullptr, context->last_error);
        dmi_close(context);
        return nullptr;
    }

    return context;
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
