//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef __APPLE__
#error "Unsupported OS type"
#endif // !__APPLE__

#include <IOKit/IOKitLib.h>

#include <opendmi/context.h>
#include <opendmi/backend.h>

typedef struct dmi_context_darwin dmi_context_darwin_t;

struct dmi_context_darwin
{
    io_service_t service;
};

static bool dmi_darwin_open(dmi_context_t *context);
static dmi_data_t *dmi_darwin_read_entry(dmi_context_t *context, size_t *plength);
static dmi_data_t *dmi_darwin_read_tables(dmi_context_t *context, size_t *plength);
static bool dmi_darwin_close(dmi_context_t *context);

static dmi_data_t *dmi_darwin_read_data(dmi_context_t *context, CFStringRef key, size_t *plength);

dmi_backend_t dmi_backend_darwin =
{
    .name        = "Apple SMBIOS service",
    .open        = dmi_darwin_open,
    .read_entry  = dmi_darwin_read_entry,
    .read_tables = dmi_darwin_read_tables,
    .close       = dmi_darwin_close
};

static bool dmi_darwin_open(dmi_context_t *context)
{
    dmi_context_darwin_t *backend = nullptr;

    if (context == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if (context->backend != nullptr) {
        dmi_set_error(context, DMI_ERROR_INVALID_STATE);
        return false;
    }

    // Allocate backend descriptor
    backend = malloc(sizeof(dmi_context_darwin_t));
    if (backend == nullptr) {
        dmi_set_error(context, DMI_ERROR_OUT_OF_MEMORY);
        return false;
    }
    memset(backend, 0, sizeof(dmi_context_darwin_t));

    // Establish SMBIOS service connection
    bool success = false;
    do {
        // Connect to SMBIOS service
        backend->service = IOServiceGetMatchingService(kIOMainPortDefault, IOServiceMatching("AppleSMBIOS"));
        if (backend->service == MACH_PORT_NULL) {
            dmi_set_error(context, DMI_ERROR_SERVICE_UNAVAILABLE);
            return EXIT_FAILURE;
        }

        success = true;
    } while (false);

    if (!success) {
        free(backend);
        return false;
    }

    context->backend = backend;

    return true;
}

static dmi_data_t *dmi_darwin_read_entry(dmi_context_t *context, size_t *plength)
{
    return dmi_darwin_read_data(context, CFSTR("SMBIOS-EPS"), plength);
}

static dmi_data_t *dmi_darwin_read_tables(dmi_context_t *context, size_t *plength)
{
    return dmi_darwin_read_data(context, CFSTR("SMBIOS"), plength);
}

static bool dmi_darwin_close(dmi_context_t *context)
{
    if (context == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if (context->backend == nullptr) {
        dmi_set_error(context, DMI_ERROR_INVALID_STATE);
        return false;
    }

    dmi_context_darwin_t *backend = (dmi_context_darwin_t *)context->backend;

    if (context->table_data != nullptr) {
        free(context->table_data);
        context->table_data = nullptr;
    }
    if (context->entry_data != nullptr) {
        free(context->entry_data);
        context->entry_data = nullptr;
    }

    if (backend->service != MACH_PORT_NULL)
        IOObjectRelease(backend->service);

    free(backend);
    context->backend = nullptr;

    return true;
}

static dmi_data_t *dmi_darwin_read_data(dmi_context_t *context, CFStringRef key, size_t *plength)
{
    if ((context == nullptr) || (plength == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (context->backend == nullptr) {
        dmi_set_error(context, DMI_ERROR_INVALID_STATE);
        return nullptr;
    }

    dmi_context_darwin_t *backend = (dmi_context_darwin_t *)context->backend;

    bool        success = false;
    CFDataRef   ref     = nullptr;
    dmi_data_t *data    = nullptr;
    size_t      length  = 0;

    do {
        ref = (CFDataRef)IORegistryEntryCreateCFProperty(backend->service, key,
                                                         kCFAllocatorDefault, kNilOptions);
        if (ref == NULL) {
            dmi_set_error(context, DMI_ERROR_INTERNAL);
            return nullptr;
        }

        length = CFDataGetLength(ref);

        data = malloc(length);
		if (data == nullptr) {
			dmi_set_error(context, DMI_ERROR_OUT_OF_MEMORY);
			break;
		}
    
        CFDataGetBytes(ref, CFRangeMake(0, length), (UInt8 *)data);

        success = true;
    } while (false);

    if (ref != nullptr)
        CFRelease(ref);
    
    if (!success) {
        if (data != nullptr)
            free(data);

        return nullptr;
    }

    *plength = length;

    return data;
}
