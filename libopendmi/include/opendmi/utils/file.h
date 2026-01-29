//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_FILE_H
#define OPENDMI_UTILS_FILE_H

#pragma once

#include <sys/stat.h>
#include <opendmi/types.h>

#if defined(_WIN32)
typedef struct _stat dmi_file_stat_t;
#else
typedef struct stat dmi_file_stat_t;
#endif

__BEGIN_DECLS

int dmi_file_stat(int fd, dmi_file_stat_t *st);

off_t dmi_file_tell(int fd);
off_t dmi_file_seek(int fd, off_t offset, int whence);

bool  dmi_file_lock(int fd, off_t size);
bool  dmi_file_unlock(int fd, off_t size);

ssize_t dmi_file_read(int fd, dmi_data_t *data, size_t size);

int dmi_file_close(int fd);

__END_DECLS

#endif // !OPENDMI_UTILS_FILE_H
