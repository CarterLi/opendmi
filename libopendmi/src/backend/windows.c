//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef _WIN32
#   error "Unsupported OS type"
#endif // !_WIN32

#include <opendmi/backend/windows.h>

static bool dmi_windows_open(dmi_context_t *context, const char *path);
static dmi_data_t *dmi_windows_read_entry(dmi_context_t *context, size_t *plength);
static dmi_data_t *dmi_windows_read_table(dmi_context_t *context, size_t *plength);
static bool dmi_windows_close(dmi_context_t *context);

dmi_backend_t dmi_windows_backend =
{
    .name       = "Linux SysFS",
    .open       = dmi_windows_open,
    .read_entry = dmi_windows_read_entry,
    .read_table = dmi_windows_read_table,
    .close      = dmi_windows_close
};

static bool dmi_windows_open(dmi_context_t *context, const char *path)
{
    dmi_unused(context);
    dmi_unused(path);

    return false;
}

static dmi_data_t *dmi_windows_read_entry(dmi_context_t *context, size_t *plength)
{
    dmi_unused(context);
    dmi_unused(plength);

    return nullptr;
}

static dmi_data_t *dmi_windows_read_table(dmi_context_t *context, size_t *plength)
{
    dmi_unused(context);
    dmi_unused(plength);

    return nullptr;
}

static bool dmi_windows_close(dmi_context_t *context)
{
    dmi_unused(context);

    return false;
}
