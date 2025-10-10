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

static bool dmi_open_ex(dmi_context_t *context, dmi_backend_t *backend, const void *arg);

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

dmi_context_t *dmi_create(void)
{
    dmi_context_t *context = nullptr;

    // Allocate context descriptor
    context = malloc(sizeof(dmi_context_t));
    if (context == nullptr) {
        dmi_set_error(nullptr,  DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    // Initialize context
    memset(context, 0, sizeof(dmi_context_t));

    return context;
}

bool dmi_open(dmi_context_t *context)
{
    return dmi_open_ex(context, dmi_backend, nullptr);
}

bool dmi_dump_load(dmi_context_t *context, const char *path)
{
    if (path == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    dmi_info(context, "Loading DMI dump: %s...", path);

    return dmi_open_ex(context, &dmi_dump_backend, path);
}

bool dmi_dump_save(dmi_context_t *context, const char *path)
{
    if ((context == nullptr) || (path == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    return true;
}

bool dmi_set_logger(dmi_context_t *context, dmi_log_handler_t logger)
{
    if (context == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    context->logger = logger;

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

bool dmi_close(dmi_context_t *context)
{
    if (context == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (context->backend == nullptr)
        return true;
    if (context->session != nullptr)
        context->backend->close(context);

    context->entry_data = nullptr;
    context->entry_size = 0;

    context->table_count         = 0;
    context->table_area_addr     = 0;
    context->table_area_size     = 0;
    context->table_area_max_size = 0;
    context->table_data          = nullptr;
    context->table_max_size      = 0;

    context->session = nullptr;
    context->backend = nullptr;

    return true;
}

void dmi_destroy(dmi_context_t *context)
{
    if (context == nullptr)
        return;

    // Close and free context
    dmi_close(context);
    free(context);
}

static bool dmi_open_ex(dmi_context_t *context, dmi_backend_t *backend, const void *arg)
{
    if (context == nullptr) {
        dmi_set_error(nullptr,  DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if ((context->backend != nullptr) || (context->session != nullptr)) {
        dmi_set_error(nullptr,  DMI_ERROR_INVALID_STATE);
        return false;
    }

    dmi_info(context, "Opening DMI context...");
    dmi_info(context, "Using backend: %s", backend->name);

    // Initialize context
    bool success = false;
    do {
        context->backend = backend;

        // Initialize backend
        if (!context->backend->open(context, arg)) {
            dmi_error(context, "Unable to open backend: %s", dmi_error_message(context->last_error));
            break;
        }

        // Read and decode entry point
        dmi_info(context, "Reading DMI entry point...");
        context->entry_data = context->backend->read_entry(context, &context->entry_size);
        if (context->entry_data == nullptr)
            break;
        if (!dmi_entry_decode(context, context->entry_data, context->entry_size))
            break;

        // Fixup SMBIOS version number
        dmi_version_fixup(context);
        dmi_info(context, "SMBIOS %u.%u.%u present",
                 dmi_version_major(context->smbios_version),
                 dmi_version_minor(context->smbios_version),
                 dmi_version_revision(context->smbios_version));

        // Read and decode SMBIOS tables
        // TODO: Use separate variable for size
        dmi_info(context, "Reading DMI tables...");
        context->table_data = context->backend->read_tables(context, &context->table_area_size);
        if (context->table_data == nullptr)
            break;
        if (!dmi_table_scan(context))
            break;

        success = true;
    } while (false);

    if (!success) {
        dmi_error(context, "Unable to open DMI context");
        dmi_set_error(context, context->last_error);
        dmi_close(context);
    }

    return success;
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
