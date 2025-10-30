//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_MODEL_ATTRIBUTE_H
#define OPENDMI_MODEL_ATTRIBUTE_H

#pragma once

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

struct dmi_attribute_spec
{
    char *tag;
    char *name;
    enum dmi_attribute_type type;
    const char *unit;
    const char **values;
};

#endif // !OPENDMI_MODEL_ATTRIBUTE_H
