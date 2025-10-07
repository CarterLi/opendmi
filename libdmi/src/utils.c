//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <assert.h>
#include <errno.h>

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
