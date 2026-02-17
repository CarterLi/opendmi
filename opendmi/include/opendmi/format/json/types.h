//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_JSON_TYPES_H
#define OPENDMI_FORMAT_JSON_TYPES_H

#pragma once

#include <opendmi/types.h>

typedef struct dmi_json_session
{
    /**
     * @brief Context handle.
     */
    dmi_context_t *context;
} dmi_json_session_t;

#endif // !OPENDMI_FORMAT_JSON_TYPES_H
