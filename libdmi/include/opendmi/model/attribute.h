//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_MODEL_ATTRIBUTE_H
#define OPENDMI_MODEL_ATTRIBUTE_H

#pragma once

#include <opendmi/name.h>

#ifndef DMI_ATTRIBUTE_SPEC_T
#define DMI_ATTRIBUTE_SPEC_T
typedef struct dmi_attribute_spec dmi_attribute_spec_t;
#endif // !DMI_ATTRIBUTE_SPEC_T

enum dmi_attribute_type
{
    DMI_ATTRIBUTE_TYPE_NONE,
    DMI_ATTRIBUTE_TYPE_HANDLE,
    DMI_ATTRIBUTE_TYPE_STRING,
    DMI_ATTRIBUTE_TYPE_BOOL,
    DMI_ATTRIBUTE_TYPE_INT,
    DMI_ATTRIBUTE_TYPE_SIZE,
    DMI_ATTRIBUTE_TYPE_ENUM,
    DMI_ATTRIBUTE_TYPE_SET
};

enum dmi_attribute_format
{
    DMI_ATTRIBUTE_FORMAT_NONE,
    DMI_ATTRIBUTE_FORMAT_HEX
};

struct dmi_attribute_spec
{
    char *code;
    char *name;
    size_t offset;
    enum dmi_attribute_type type;
    enum dmi_attribute_format format;
    const char *unit;
    const dmi_name_t *values;
    const char *(*to_string)(const void *value);
};

#define DMI_ATTRIBUTE_NULL                   \
    {                                        \
        .code   = nullptr,                   \
        .name   = nullptr,                   \
        .type   = DMI_ATTRIBUTE_TYPE_NONE,   \
        .format = DMI_ATTRIBUTE_FORMAT_NONE, \
        .unit   = nullptr,                   \
        .values = nullptr                    \
    }

#endif // !OPENDMI_MODEL_ATTRIBUTE_H
