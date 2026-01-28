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
#include <assert.h>

#include <opendmi/utils/file.h>

off_t dmi_file_tell(int fd)
{
    assert(fd >= 0);

    return dmi_file_seek(fd, 0, SEEK_CUR);
}

off_t dmi_file_seek(int fd, off_t offset, int whence)
{
    off_t rv;

    assert(fd >= 0);

    do {
        rv = lseek(fd, offset, whence);
        if ((rv < 0) and (errno == EINTR))
            continue;
    } while (false);

    return rv;
}

bool  dmi_file_lock(int fd, off_t size)
{
    assert(fd >= 0);

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
    assert(fd >= 0);

    do {
        if (lockf(fd, F_ULOCK, size) < 0) {
            if (errno == EINTR)
                continue;
            return false;
        }
    } while (false);

    return true;
}

ssize_t dmi_file_read(int fd, dmi_data_t *data, size_t size)
{
    size_t nread = 0;

    assert(fd >= 0);
    assert(data != nullptr);

    while (size > 0) {
        ssize_t rv = read(fd, data + nread, size - nread);

        if (rv < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }

        if (rv == 0)
            break;

        nread += rv;
    }

    return nread;
}
