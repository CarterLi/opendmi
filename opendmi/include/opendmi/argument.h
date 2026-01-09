//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ARGUMENT_H
#define OPENDMI_ARGUMENT_H

#pragma once

#include <opendmi/defs.h>

typedef struct dmi_argument dmi_argument_t;

typedef bool (*dmi_argument_fn_t)(const char *value);

typedef enum dmi_argument_type
{
    DMI_ARGUMENT_TYPE_NONE,
    DMI_ARGUMENT_TYPE_BOOL,
    DMI_ARGUMENT_TYPE_STRING
} dmi_argument_type_t;

typedef struct dmi_argument
{
    const char *name;
    dmi_argument_type_t type;
    bool is_required;
    void *data;
    dmi_argument_fn_t handler;
};

#endif // !OPENDMI_ARGUMENT_H
