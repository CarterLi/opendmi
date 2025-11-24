//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef _WIN32
#error "Unsupported OS type"
#endif // !_WIN32

#include <opendmi/backend/windows.h>

static bool dmi_windows_open(dmi_context_t *context, const void *arg);
static dmi_data_t *dmi_windows_read_entry(dmi_context_t *context, size_t *plength);
static dmi_data_t *dmi_windows_read_tables(dmi_context_t *context, size_t *plength);
static bool dmi_windows_close(dmi_context_t *context);

dmi_backend_t dmi_windows_backend =
{
    .name        = "Linux SysFS",
    .open        = dmi_windows_open,
    .read_entry  = dmi_windows_read_entry,
    .read_tables = dmi_windows_read_tables,
    .close       = dmi_windows_close
};

static bool dmi_windows_open(dmi_context_t *context, const void *arg)
{
    (void)context;
    (void)arg;

    return false;
}

static dmi_data_t *dmi_windows_read_entry(dmi_context_t *context, size_t *plength)
{
    (void)context;
    (void)plength;

    return nullptr;
}

static dmi_data_t *dmi_windows_read_tables(dmi_context_t *context, size_t *plength)
{
    (void)context;
    (void)plength;

    return nullptr;
}

static bool dmi_windows_close(dmi_context_t *context)
{
    (void)context;

    return false;
}
