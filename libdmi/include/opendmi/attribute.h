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

#ifndef DMI_ATTRIBUTE_T
#define DMI_ATTRIBUTE_T
typedef struct dmi_attribute dmi_attribute_t;
#endif // !DMI_ATTRIBUTE_T

#ifndef DMI_ATTRIBUTE_PARAMS_T
#define DMI_ATTRIBUTE_PARAMS_T
typedef struct dmi_attribute_params dmi_attribute_params_t;
#endif // !DMI_ATTRIBUTE_PARAMS_T

#ifndef DMI_ATTRIBUTE_OPS_T
#define DMI_ATTRIBUTE_OPS_T
typedef struct dmi_attribute_ops dmi_attribute_ops_t;
#endif // !DMI_ATTRIBUTE_OPS_T

typedef char *(*dmi_attribute_formatter_t)(const dmi_attribute_t *attr, const void *value);
typedef void (*dmi_attribute_parser_t)(const dmi_attribute_t *attr);

typedef enum dmi_attribute_type
{
    DMI_ATTRIBUTE_TYPE_NONE,
    DMI_ATTRIBUTE_TYPE_HANDLE,
    DMI_ATTRIBUTE_TYPE_STRING,
    DMI_ATTRIBUTE_TYPE_BOOL,
    DMI_ATTRIBUTE_TYPE_INTEGER,
    DMI_ATTRIBUTE_TYPE_DECIMAL,
    DMI_ATTRIBUTE_TYPE_SIZE,
    DMI_ATTRIBUTE_TYPE_ADDRESS,
    DMI_ATTRIBUTE_TYPE_ENUM,
    DMI_ATTRIBUTE_TYPE_SET,
    DMI_ATTRIBUTE_TYPE_UUID
} dmi_attribute_type_t;

typedef enum dmi_attribute_flag
{
    DMI_ATTRIBUTE_FLAG_SIGNED = 0x01,
    DMI_ATTRIBUTE_FLAG_HEX    = 0x02,
    DMI_ATTRIBUTE_FLAG_BCD    = 0x04
} dmi_attribute_flag_t;

typedef enum dmi_attribute_format
{
    DMI_ATTRIBUTE_FORMAT_NONE,
    DMI_ATTRIBUTE_FORMAT_HEX
} dmi_attribute_format_t;

/**
 * @brief Attribute parameters.
 */
struct dmi_attribute_params
{
    /**
     * @brief Code name, used to identify the attribute during serialization.
     */
    char *code;

    /**
     * @brief Printable name, used to identify the attribute when printing.
     */
    char *name;

    /**
     * @brief Output format.
     */
    dmi_attribute_format_t format;

    /**
     * @brief Measurement units. Valid only for integer or decimal values,
     * should be set to `nullptr` in other cases.
     */
    const char *unit;

    /**
     * @brief Number of decimal digits after the decimal point. Valid only for
     * decimal attributes, should be set to zero in other cases.
     */
    unsigned int scale;

    /**
     * @brief Flags.
     */
    unsigned int flags;

    /**
     * @brief Enumeration or boolean value names.
     */
    const dmi_name_t *values;
};

struct dmi_attribute_ops
{
    dmi_attribute_formatter_t format;
    dmi_attribute_parser_t parse;
};

struct dmi_attribute
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

__BEGIN_DECLS

char *dmi_attribute_format(const dmi_attribute_t *attr, const void *value);

__END_DECLS

#endif // !OPENDMI_ATTRIBUTE_H
