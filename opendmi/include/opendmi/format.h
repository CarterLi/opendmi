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

#ifndef DMI_FORMAT_OPS_T
#define DMI_FORMAT_OPS_T
typedef struct dmi_format_ops dmi_format_ops_t;
#endif // !DMI_FORMAT_OPS_T

struct dmi_format_ops
{
    void (*start)(void *context);
    void (*end)(void *context);
};

struct dmi_format
{
    const char *code;
    const char *name;
    const dmi_format_ops_t handlers;
};

__BEGIN_DECLS

const dmi_format_t *dmi_format_get(const char *code);

__END_DECLS

#endif // !OPENDMI_FORMAT_H
