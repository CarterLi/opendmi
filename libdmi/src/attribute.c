//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

#include <opendmi/attribute.h>
#include <opendmi/utils.h>

static char *dmi_attribute_format_handle(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_string(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_bool(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_integer(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_decimal(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_size(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_address(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_enum(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_set(const dmi_attribute_t *attr, const void *value);
static char *dmi_attribute_format_uuid(const dmi_attribute_t *attr, const void *value);

static const dmi_attribute_ops_t dmi_attribute_type_ops[] =
{
    [DMI_ATTRIBUTE_TYPE_HANDLE] = {
        .format = dmi_attribute_format_handle,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_STRING] = {
        .format = dmi_attribute_format_string,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_BOOL] = {
        .format = dmi_attribute_format_bool,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_INTEGER] = {
        .format = dmi_attribute_format_integer,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_DECIMAL] = {
        .format = dmi_attribute_format_decimal,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_SIZE] = {
        .format = dmi_attribute_format_size,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_ADDRESS] = {
        .format = dmi_attribute_format_address,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_ENUM] = {
        .format = dmi_attribute_format_enum,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_SET] = {
        .format = dmi_attribute_format_set,
        .parse  = nullptr
    },
    [DMI_ATTRIBUTE_TYPE_UUID] = {
        .format = dmi_attribute_format_uuid,
        .parse  = nullptr
    }
};

bool dmi_attribute_unknown(const dmi_attribute_t *attr, const void *value)
{
    assert(attr != nullptr);
    assert(value != nullptr);

    if (attr->params.unknown) {
        if (memcmp(value, attr->params.unknown, attr->size) == 0)
            return true;
    }

    return false;
}

char *dmi_attribute_format(const dmi_attribute_t *attr, const void *value)
{
    const dmi_attribute_ops_t *ops;

    assert(attr != nullptr);
    assert(value != nullptr);

    if (attr->type >= DMI_ARRAY_SIZE(dmi_attribute_type_ops))
        return nullptr;

    ops = &dmi_attribute_type_ops[attr->type];
    if (!ops->format)
        return nullptr;

    return ops->format(attr, value);
}

static char *dmi_attribute_format_handle(const dmi_attribute_t *attr, const void *value)
{
    char *str = nullptr;

    assert(attr != nullptr);
    assert(value != nullptr);

    if (asprintf(&str, "0x%04" PRIX16, *(dmi_handle_t *)value) < 0)
        return nullptr;

    return str;
}

static char *dmi_attribute_format_string(const dmi_attribute_t *attr, const void *value)
{
    assert(attr != nullptr);
    assert(value != nullptr);

    const char *str = *(const char **)value;
    if (!str)
        str = "<unspecified>";

    return strdup(str);
}

static char *dmi_attribute_format_bool(const dmi_attribute_t *attr, const void *value)
{
    const char *str = nullptr;

    assert(attr != nullptr);
    assert(value != nullptr);

    if (attr->params.values) {
        str = dmi_name_lookup(attr->params.values, *(bool *)value ? 1 : 0);
    } else {
        str = *(bool *)value ? "true" : "false";
    }

    return strdup(str);
}

static char *dmi_attribute_format_integer(const dmi_attribute_t *attr, const void *value)
{
    int rv;
    const char *fmt = nullptr;
    char *str = nullptr;

    assert(attr != nullptr);
    assert(value != nullptr);

    switch (attr->size) {
    case sizeof(int8_t):
        if (attr->params.flags & DMI_ATTRIBUTE_FLAG_SIGNED)
            fmt = "%" PRId8;
        else if (attr->params.flags & DMI_ATTRIBUTE_FLAG_HEX)
            fmt = "0x%" PRIX8;
        else
            fmt = "%" PRIu8;
        rv = asprintf(&str, fmt, *(int8_t *)value);
        break;

    case sizeof(int16_t):
        if (attr->params.flags & DMI_ATTRIBUTE_FLAG_SIGNED)
            fmt = "%" PRId16;
        else if (attr->params.flags & DMI_ATTRIBUTE_FLAG_HEX)
            fmt = "0x%" PRIX16;
        else
            fmt = "%" PRIu16;
        rv = asprintf(&str, fmt, *(int16_t *)value);
        break;

    case sizeof(int32_t):
        if (attr->params.flags & DMI_ATTRIBUTE_FLAG_SIGNED)
            fmt = "%" PRId32;
        else if (attr->params.flags & DMI_ATTRIBUTE_FLAG_HEX)
            fmt = "0x%" PRIX32;
        else
            fmt = "%" PRIu32;
        rv = asprintf(&str, fmt, *(int32_t *)value);
        break;

    case sizeof(int64_t):
        if (attr->params.flags & DMI_ATTRIBUTE_FLAG_SIGNED)
            fmt = "%" PRId64;
        else if (attr->params.flags & DMI_ATTRIBUTE_FLAG_HEX)
            fmt = "0x%" PRIX64;
        else
            fmt = "%" PRIu64;
        rv = asprintf(&str, fmt, *(int32_t *)value);
        break;

    default:
        return nullptr;
    }

    if (rv < 0)
        return nullptr;

    return str;
}

static char *dmi_attribute_format_decimal(const dmi_attribute_t *attr, const void *value)
{
    char  fmt[16];
    int   rv  = 0;
    char *str = nullptr;

    assert(attr != nullptr);
    assert(value != nullptr);

    if (attr->params.scale == 0)
        return dmi_attribute_format_integer(attr, value);

    int64_t src;
    if (attr->size == sizeof(int8_t))
        src = *(int8_t *)value;
    else if (attr->size == sizeof(int16_t))
        src = *(int16_t *)value;
    else if (attr->size == sizeof(int32_t))
        src = *(int32_t *)value;
    else if (attr->size == sizeof(int64_t))
        src = *(int64_t *)value;
    else
        return nullptr;

    unsigned int factor = dmi_ipow32(10, attr->params.scale);

    if (attr->params.flags & DMI_ATTRIBUTE_FLAG_SIGNED) {
        snprintf(fmt, sizeof(fmt), "%%lld.%%0%dllu", attr->params.scale);
        rv = asprintf(&str, fmt, src / factor, llabs(src) % factor);
    } else {
        snprintf(fmt, sizeof(fmt), "%%llu.%%0%dllu", attr->params.scale);
        rv = asprintf(&str, fmt, (uint64_t)src / factor, (uint64_t)src % factor);
    }

    if (rv < 0)
        return nullptr;

    return str;
}

static char *dmi_attribute_format_size(const dmi_attribute_t *attr, const void *value)
{
    assert(attr != nullptr);
    assert(value != nullptr);

    // TODO: Implement size formatting

    return dmi_attribute_format_integer(attr, value);
}

static char *dmi_attribute_format_address(const dmi_attribute_t *attr, const void *value)
{
    assert(attr != nullptr);
    assert(value != nullptr);

    // TODO: Implement address formatting

    return dmi_attribute_format_integer(attr, value);
}

static char *dmi_attribute_format_enum(const dmi_attribute_t *attr, const void *value)
{
    const char *str;

    assert(attr != nullptr);
    assert(value != nullptr);

    if (!attr->params.values)
        return nullptr;

    str = dmi_name_lookup(attr->params.values, *(int *)value);
    if (!str)
        str = "<invalid>";

    return strdup(str);
}

static char *dmi_attribute_format_set(const dmi_attribute_t *attr, const void *value)
{
    assert(attr != nullptr);
    assert(value != nullptr);

    // TODO: Implement set formatting

    return nullptr;
}

static char *dmi_attribute_format_uuid(const dmi_attribute_t *attr, const void *value)
{
    assert(attr != nullptr);
    assert(value != nullptr);

    // TODO: Implement UUID formatting

    return nullptr;
}
