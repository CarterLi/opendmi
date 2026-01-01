//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_YAML_TYPES_H
#define OPENDMI_FORMAT_YAML_TYPES_H

#pragma once

#include <stdio.h>
#include <yaml.h>

#include <opendmi/types.h>
#include <opendmi/attribute.h>

typedef struct dmi_yaml_session
{
    dmi_context_t *context;
    FILE *stream;
    yaml_emitter_t *emitter;
} dmi_yaml_session_t;

#endif // !OPENDMI_FORMAT_YAML_TYPES_H
