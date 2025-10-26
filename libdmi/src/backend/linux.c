//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef __linux__
#error "Unsupported OS type"
#endif // !__linux__

#include <opendmi/backend.h>

typedef struct dmi_linux_session dmi_linux_session_t;

struct dmi_linux_session
{
};

static bool dmi_linux_open(dmi_context_t *context, const void *arg __attribute__((unused)));
static dmi_data_t *dmi_linux_read_entry(dmi_context_t *context, size_t *plength);
static dmi_data_t *dmi_linux_read_tables(dmi_context_t *context, size_t *plength);
static bool dmi_linux_close(dmi_context_t *context);

dmi_backend_t dmi_linux_backend =
{
    .name        = "Linux SysFS",
    .open        = dmi_linux_open,
    .read_entry  = dmi_linux_read_entry,
    .read_tables = dmi_linux_read_tables,
    .close       = dmi_linux_close
};

static bool dmi_linux_open(dmi_context_t *context, const void *arg __attribute__((unused)))
{
    return false;
}

static dmi_data_t *dmi_linux_read_entry(dmi_context_t *context, size_t *plength)
{
    return nullptr;
}

static dmi_data_t *dmi_linux_read_tables(dmi_context_t *context, size_t *plength)
{
    return nullptr;
}

static bool dmi_linux_close(dmi_context_t *context)
{
    return false;
}
