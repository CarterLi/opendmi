//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_NAME_H
#define OPENDMI_NAME_H

#pragma once

#include <opendmi/types.h>

#ifndef DMI_NAME_T
#define DMI_NAME_T
typedef struct dmi_name dmi_name_t;
#endif // !DMI_NAME_T

#ifndef DMI_NAME_SET_T
#define DMI_NAME_SET_T
typedef struct dmi_name_set dmi_name_set_t;
#endif // !DMI_NAME_SET_T

struct dmi_name
{
    int id;
    const char *code;
    const char *name;
};

struct dmi_name_set
{
    const char *code;
    const dmi_name_t names[];
};

#define DMI_NAME_NULL { -1, nullptr, nullptr }

#define DMI_NAME_UNSPEC(id)      { (id), "unspecified", "Unspecified" }
#define DMI_NAME_UNKNOWN(id)     { (id), "unknown",     "Unknown"     }
#define DMI_NAME_OTHER(id)       { (id), "other",       "Other"       }
#define DMI_NAME_NONE(id)        { (id), "none",        "None"        }
#define DMI_NAME_UNSUPPORTED(id) { (id), "unsupported", "Unsupported" }
#define DMI_NAME_RESERVED(id)    { (id), "reserved",    "Reserved"    }

__BEGIN_DECLS

const char *dmi_code_lookup(const dmi_name_set_t *dict, int id);
const char *dmi_name_lookup(const dmi_name_set_t *dict, int id);

__END_DECLS

#endif // !OPENDMI_NAME_H
