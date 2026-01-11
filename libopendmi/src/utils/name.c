//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/utils/name.h>

const char *dmi_code_lookup(const dmi_name_set_t *dict, int id)
{
    if ((dict == nullptr) or (id < 0))
        return nullptr;

    if (dict->names != nullptr) {
        for (const dmi_name_t *entry = dict->names; entry->code != nullptr; entry++) {
            if (id == entry->id)
                return entry->code;
        }
    }

    if (dict->ranges != nullptr) {
        for (const dmi_name_range_t *entry = dict->ranges; entry->code != nullptr; entry++) {
            if ((id >= entry->start_id) and (id <= entry->end_id))
                return entry->code;
        }
    }

    return nullptr;
}

const char *dmi_name_lookup(const dmi_name_set_t *dict, int id)
{
    if ((dict == nullptr) or (id < 0))
        return nullptr;

    if (dict->names != nullptr) {
        for (const dmi_name_t *entry = dict->names; entry->code != nullptr; entry++) {
            if (id == entry->id)
                return entry->name;
        }
    }

    if (dict->ranges != nullptr) {
        for (const dmi_name_range_t *entry = dict->ranges; entry->code != nullptr; entry++) {
            if ((id >= entry->start_id) and (id <= entry->end_id))
                return entry->name;
        }
    }

    return nullptr;
}
