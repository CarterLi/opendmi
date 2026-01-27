//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "../config.h"

#ifdef HAVE_UNISTD_H
#   include <unistd.h>
#endif // HAVE_UNISTD_H

#include <errno.h>

#include <opendmi/utils/file.h>

off_t dmi_file_tell(int fd)
{
    return dmi_file_seek(fd, 0, SEEK_CUR);
}

off_t dmi_file_seek(int fd, off_t offset, int whence)
{
    off_t rv;

    do {
        rv = lseek(fd, offset, whence);
        if ((rv < 0) and (errno == EINTR))
            continue;
    } while (false);

    return rv;
}

bool  dmi_file_lock(int fd, off_t size)
{
    do {
        if (lockf(fd, F_LOCK, size) < 0) {
            if (errno == EINTR)
                continue;
            return false;
        }
    } while (false);

    return true;
}

bool  dmi_file_unlock(int fd, off_t size)
{
    do {
        if (lockf(fd, F_ULOCK, size) < 0) {
            if (errno == EINTR)
                continue;
            return false;
        }
    } while (false);

    return true;
}
