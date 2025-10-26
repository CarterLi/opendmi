//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_EXTENSION_H
#define OPENDMI_EXTENSION_H

#pragma once

#include <opendmi/table.h>

#ifndef DMI_EXTENSION_T
#define DMI_EXTENSION_T
typedef struct dmi_extension dmi_extension_t;
#endif // !DMI_EXTENSION_SPEC_T

/**
 * @brief DMI extension.
 */
struct dmi_extension
{
    const char *tag;
    const char *name;
    const dmi_table_spec_t *tables;
};

#endif // !OPENDMI_EXTENSION_H
