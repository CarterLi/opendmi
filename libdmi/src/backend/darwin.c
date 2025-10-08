//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef __APPLE__
#error "Unsupported OS type"
#endif // !__APPLE__

#include <errno.h>

#include <IOKit/IOKitLib.h>

#include <opendmi/backend.h>

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
    if (context == nullptr) {
        errno = EINVAL;
        return false;
    }

    return true;
}

static bool dmi_darwin_close(dmi_context_t *context)
{
    if (context == nullptr) {
        errno = EINVAL;
        return false;
    }

    return true;
}
