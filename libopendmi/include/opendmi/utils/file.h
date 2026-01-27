//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_FILE_H
#define OPENDMI_UTILS_FILE_H

#pragma once

#include <opendmi/types.h>

__BEGIN_DECLS

off_t dmi_file_tell(int fd);
off_t dmi_file_seek(int fd, off_t offset, int whence);
bool  dmi_file_lock(int fd, off_t size);
bool  dmi_file_unlock(int fd, off_t size);

__END_DECLS

#endif // !OPENDMI_UTILS_FILE_H
