//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_MODULE_H
#define OPENDMI_MODULE_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_module dmi_module_t;

/**
 * @brief DMI extension module.
 */
struct dmi_module
{
    const char *code;
    const char *name;
    const dmi_entity_spec_t **entities;
};

#endif // !OPENDMI_MODULE_H
