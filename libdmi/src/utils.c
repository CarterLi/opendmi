//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <assert.h>

#include <opendmi/utils.h>

const char *dmi_name(const char **table, size_t id, size_t count)
{
    assert(table != nullptr);

    if (id >= count)
        return nullptr;

    return table[id];
}
