//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ATTRIBUTE_H
#define OPENDMI_ATTRIBUTE_H

#pragma once

#include <opendmi/name.h>

#ifndef DMI_ATTRIBUTE_PARAMS_T
#define DMI_ATTRIBUTE_PARAMS_T
typedef struct dmi_attribute_params dmi_attribute_params_t;
#endif // !DMI_ATTRIBUTE_PARAMS_T

#ifndef DMI_ATTRIBUTE_SPEC_T
#define DMI_ATTRIBUTE_SPEC_T
typedef struct dmi_attribute_spec dmi_attribute_spec_t;
#endif // !DMI_ATTRIBUTE_SPEC_T

typedef enum dmi_attribute_type
{
    DMI_ATTRIBUTE_TYPE_NONE,
    DMI_ATTRIBUTE_TYPE_HANDLE,
    DMI_ATTRIBUTE_TYPE_STRING,
    DMI_ATTRIBUTE_TYPE_BOOL,
    DMI_ATTRIBUTE_TYPE_INT,
    DMI_ATTRIBUTE_TYPE_DECIMAL,
    DMI_ATTRIBUTE_TYPE_SIZE,
    DMI_ATTRIBUTE_TYPE_ENUM,
    DMI_ATTRIBUTE_TYPE_SET,
    DMI_ATTRIBUTE_TYPE_UUID
} dmi_attribute_type_t;

typedef enum dmi_attribute_format
{
    DMI_ATTRIBUTE_FORMAT_NONE,
    DMI_ATTRIBUTE_FORMAT_HEX
} dmi_attribute_format_t;

struct dmi_attribute_params
{
    char *code;
    char *name;
    dmi_attribute_format_t format;
    const char *unit;
    unsigned int scale;
    unsigned int flags;
    const dmi_name_t *values;
    const char *(*to_string)(const void *value);

};

struct dmi_attribute_spec
{
    size_t offset;
    size_t size;
    dmi_attribute_type_t type;
    dmi_attribute_params_t params;
};

#define DMI_ATTRIBUTE(_entity, _member, _type, ...)     \
    {                                                   \
        .offset = dmi_member_offset(_entity, _member),  \
        .size   = dmi_member_size(_entity, _member),    \
        .type   = DMI_ATTRIBUTE_TYPE_ ## _type,         \
        .params = __VA_ARGS__                           \
    }

#define DMI_ATTRIBUTE_NULL                   \
    {                                        \
        .offset = 0,                         \
        .size   = 0,                         \
        .type   = DMI_ATTRIBUTE_TYPE_NONE,   \
        .params = { 0 }                      \
    }

#endif // !OPENDMI_ATTRIBUTE_H
