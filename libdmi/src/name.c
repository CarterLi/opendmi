//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/name.h>

const char *dmi_code_lookup(const dmi_name_t *dictionary, int id)
{
    if ((dictionary == nullptr) || (id < 0))
        return nullptr;

    for (const dmi_name_t *entry = dictionary; entry->id >= 0; entry++) {
        if (entry->id == id)
            return entry->code;
    }

    return nullptr;
}

const char *dmi_name_lookup(const dmi_name_t *dictionary, int id)
{
    if ((dictionary == nullptr) || (id < 0))
        return nullptr;

    for (const dmi_name_t *entry = dictionary; entry->id >= 0; entry++) {
        if (entry->id == id)
            return entry->name;
    }

    return nullptr;
}
