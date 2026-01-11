//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_NAME_H
#define OPENDMI_UTILS_NAME_H

#pragma once

#include <opendmi/types.h>

typedef struct dmi_name       dmi_name_t;
typedef struct dmi_name_range dmi_name_range_t;
typedef struct dmi_name_set   dmi_name_set_t;

struct dmi_name
{
    int id;
    const char *code;
    const char *name;
};

struct dmi_name_range
{
    int start_id;
    int end_id;
    const char *code;
    const char *name;
};

struct dmi_name_set
{
    const char *code;
    const dmi_name_t *names;
    const dmi_name_range_t *ranges;
};

#define DMI_NAME_NULL { -1, nullptr, nullptr }

#define DMI_NAME_UNSPEC(id)      { (id), "unspecified", "Unspecified" }
#define DMI_NAME_UNKNOWN(id)     { (id), "unknown",     "Unknown"     }
#define DMI_NAME_OTHER(id)       { (id), "other",       "Other"       }
#define DMI_NAME_NONE(id)        { (id), "none",        "None"        }
#define DMI_NAME_UNSUPPORTED(id) { (id), "unsupported", "Unsupported" }
#define DMI_NAME_RESERVED(id)    { (id), "reserved",    "Reserved"    }

#define DMI_NAME_RANGE_NULL { -1, -1, nullptr, nullptr }

__BEGIN_DECLS

const char *dmi_code_lookup(const dmi_name_set_t *dict, int id);
const char *dmi_name_lookup(const dmi_name_set_t *dict, int id);

__END_DECLS

#endif // !OPENDMI_UTILS_NAME_H
