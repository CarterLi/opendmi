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

struct dmi_name
{
    int id;
    const char *code;
    const char *name;
};

#define DMI_NAME_NULL { -1, nullptr, nullptr }

__BEGIN_DECLS

const char *dmi_code_lookup(const dmi_name_t *dictionary, int id);
const char *dmi_name_lookup(const dmi_name_t *dictionary, int id);

__END_DECLS

#endif // !OPENDMI_NAME_H
