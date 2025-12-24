//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_H
#define OPENDMI_FORMAT_H

#pragma once

#include <opendmi/defs.h>

#ifndef DMI_FORMAT_T
#define DMI_FORMAT_T
typedef struct dmi_format dmi_format_t;
#endif // !DMI_FORMAT_T

struct dmi_format
{
    const char *code;
    const char *name;
};

#endif // !OPENDMI_FORMAT_H
