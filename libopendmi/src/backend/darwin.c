//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef __APPLE__
#error "Unsupported OS type"
#endif // !__APPLE__

#include <errno.h>

#include <IOKit/IOKitLib.h>

#include <opendmi/context.h>
#include <opendmi/log.h>
#include <opendmi/utils.h>

#include <opendmi/backend/darwin.h>

typedef struct dmi_darwin_session dmi_darwin_session_t;

struct dmi_darwin_session
{
    io_service_t service;
};

static bool dmi_darwin_open(dmi_context_t *context, const void *arg __attribute__((unused)));
static dmi_data_t *dmi_darwin_read_entry(dmi_context_t *context, size_t *plength);
static dmi_data_t *dmi_darwin_read_tables(dmi_context_t *context, size_t *plength);
static bool dmi_darwin_close(dmi_context_t *context);

static dmi_data_t *dmi_darwin_read_data(dmi_context_t *context, CFStringRef key, size_t *plength);

dmi_backend_t dmi_darwin_backend =
{
    .name        = "Apple SMBIOS service",
    .open        = dmi_darwin_open,
    .read_entry  = dmi_darwin_read_entry,
    .read_tables = dmi_darwin_read_tables,
    .close       = dmi_darwin_close
};

static bool dmi_darwin_open(dmi_context_t *context, const void *arg __attribute__((unused)))
{
    dmi_darwin_session_t *session = nullptr;

    if (context == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if (context->session != nullptr) {
        dmi_set_error(context, DMI_ERROR_INVALID_STATE);
        return false;
    }

    // Allocate backend descriptor
    session = malloc(sizeof(dmi_darwin_session_t));
    if (session == nullptr) {
        dmi_error(context, "Unable to allocate DMI backend descriptor: %s", strerror(errno));
        dmi_set_error(context, DMI_ERROR_OUT_OF_MEMORY);
        return false;
    }
    memset(session, 0, sizeof(dmi_darwin_session_t));

    // Establish SMBIOS service connection
    bool success = false;
    do {
        // Connect to SMBIOS service
        session->service = IOServiceGetMatchingService(kIOMainPortDefault, IOServiceMatching("AppleSMBIOS"));
        if (session->service == MACH_PORT_NULL) {
            dmi_error(context, "Apple SMBIOS service is not reachable");
            dmi_set_error(context, DMI_ERROR_SERVICE_UNAVAILABLE);
            break;
        }

        success = true;
    } while (false);

    if (!success) {
        dmi_free(session);
        return false;
    }

    context->session = session;

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
    if (context->session == nullptr) {
        dmi_set_error(context, DMI_ERROR_INVALID_STATE);
        return false;
    }

    dmi_darwin_session_t *session = dmi_cast(session, context->session);

    if (session->service != MACH_PORT_NULL)
        IOObjectRelease(session->service);

    dmi_free(context->table_data);
    dmi_free(context->entry_data);
    dmi_free(session);

    context->table_data = nullptr;
    context->entry_data = nullptr;
    context->session    = nullptr;
    context->backend    = nullptr;

    return true;
}

static dmi_data_t *dmi_darwin_read_data(dmi_context_t *context, CFStringRef key, size_t *plength)
{
    if ((context == nullptr) or (plength == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (context->session == nullptr) {
        dmi_set_error(context, DMI_ERROR_INVALID_STATE);
        return nullptr;
    }

    dmi_darwin_session_t *session = dmi_cast(session, context->session);

    bool        success = false;
    CFDataRef   ref     = nullptr;
    dmi_data_t *data    = nullptr;
    size_t      length  = 0;

    do {
        ref = (CFDataRef)IORegistryEntryCreateCFProperty(session->service, key,
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
        dmi_free(data);
        return nullptr;
    }

    *plength = length;

    return data;
}
