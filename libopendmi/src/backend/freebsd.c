//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef __FreeBSD__
#   error "Unsupported OS type"
#endif // !__FreeBSD__

#include <opendmi/backend.h>

typedef struct dmi_freebsd_session dmi_freebsd_session_t;

struct dmi_freebsd_session
{
};

static bool dmi_freebsd_open(dmi_context_t *context, const void *arg __attribute__((unused)));
static dmi_data_t *dmi_freebsd_read_entry(dmi_context_t *context, size_t *plength);
static dmi_data_t *dmi_freebsd_read_table(dmi_context_t *context, size_t *plength);
static bool dmi_freebsd_close(dmi_context_t *context);

dmi_backend_t dmi_freebsd_backend =
{
    .name       = "FreeBSD",
    .open       = dmi_freebsd_open,
    .read_entry = dmi_freebsd_read_entry,
    .read_table = dmi_freebsd_read_table,
    .close      = dmi_freebsd_close
};

static bool dmi_freebsd_open(dmi_context_t *context, const void *arg __attribute__((unused)))
{
    return false;
}

static dmi_data_t *dmi_freebsd_read_entry(dmi_context_t *context, size_t *plength)
{
    return nullptr;
}

static dmi_data_t *dmi_freebsd_read_table(dmi_context_t *context, size_t *plength)
{
    return nullptr;
}

static bool dmi_freebsd_close(dmi_context_t *context)
{
    return false;
}
