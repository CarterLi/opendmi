//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_EXTENSION_H
#define OPENDMI_EXTENSION_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_extension dmi_extension_t;

/**
 * @brief DMI extension.
 */
struct dmi_extension
{
    const char *code;
    const char *name;
    const dmi_entity_spec_t *entities;
};

#endif // !OPENDMI_EXTENSION_H
