//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef __OPENDMI_PIDFILE_H__
#define __OPENDMI_PIDFILE_H__

#pragma once

#include <opendmi/types.h>

typedef struct dmi_pidfile dmi_pidfile_t;

struct dmi_pidfile
{
    char *path;
    int fd;
};

__BEGIN_DECLS

pid_t dmi_pidfile_read(const char *path);
dmi_pidfile_t *dmi_pidfile_acquire(const char *path);
void dmi_pidfile_release(dmi_pidfile_t *pidfile);

__END_DECLS

#endif // !__OPENDMI_PIDFILE_H__
