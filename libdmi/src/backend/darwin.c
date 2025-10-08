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
    mach_port_t port;
    io_service_t service;
};

static bool dmi_darwin_open(dmi_context_t *context);
static bool dmi_darwin_close(dmi_context_t *context);

dmi_backend_t dmi_backend_darwin =
{
    .name  = "Apple SMBIOS service",
    .open  = dmi_darwin_open,
    .close = dmi_darwin_close
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
        // Create service port
        IOMainPort(MACH_PORT_NULL, &backend->port);

        // Connect to SMBIOS service
        backend->service = IOServiceGetMatchingService(backend->port, IOServiceMatching("AppleSMBIOS"));
        if (backend->service == MACH_PORT_NULL) {
            dmi_set_error(context, DMI_ERROR_SERVICE_NOT_FOUND);
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

    IOObjectRelease(backend->service);
    free(backend);

    context->backend = nullptr;

    return true;
}
