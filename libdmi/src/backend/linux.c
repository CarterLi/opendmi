//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef __linux__
#error "Unsupported OS type"
#endif // !__linux__

#include <opendmi/backend.h>

static bool dmi_linux_open(dmi_context_t *context);
static bool dmi_linux_close(dmi_context_t *context);

dmi_backend_t dmi_backend_darwin =
{
    .name  = "Linux SysFS",
    .open  = dmi_linux_open,
    .close = dmi_linux_close
};

static bool dmi_linux_open(dmi_context_t *context)
{
    return false;
}

static bool dmi_linux_close(dmi_context_t *context)
{
    return false;
}
