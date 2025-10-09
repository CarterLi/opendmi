//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

const char *dmi_name(const char **table, size_t id, size_t count)
{
    assert(table != nullptr);

    if (id >= count) {
        errno = ENOENT;
        return nullptr;
    }

    return table[id];
}

bool dmi_checksum(const void *data, size_t length)
{
    if (data == nullptr) {
        errno = EINVAL;
        return false;
    }

    uint8_t sum   = 0;
    size_t  index = 0;

    while (index < length) {
        sum += ((const uint8_t *)data)[index++];
    }

    return (sum == 0) ? true : false;
}

dmi_data_t *dmi_file_map(const char *path, size_t *plength)
{
    if ((path == nullptr) || (plength == nullptr)) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }

    int         fd   = -1;
    dmi_data_t *data = nullptr;
    struct stat st;

    bool success = false;
    do {
        fd = open(path, O_RDONLY);
        if (fd < 0)
            break;
 
        if (fstat(fd, &st) < 0)
            break;

        if ((data = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == nullptr)
            break;

        success = true;
    } while (false);

    if (fd >= 0)
        close(fd);

    if (!success)
        return nullptr;

    *plength = st.st_size;

    return data;
}
