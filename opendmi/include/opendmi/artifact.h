//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ARTIFACT_H
#define OPENDMI_ARTIFACT_H

#pragma once

#include <stdio.h>
#include <opendmi/context.h>

typedef void *dmi_artifact_initialize_fn(dmi_context_t *context, FILE *stream);
typedef bool  dmi_artifact_open_fn(void *session);
typedef bool  dmi_artifact_close_fn(void *session);
typedef void  dmi_artifact_finalize_fn(void *session);

struct dmi_artifact_ops
{
    dmi_artifact_initialize_fn *initialize;
    dmi_artifact_open_fn       *open;
    dmi_artifact_close_fn      *close;
    dmi_artifact_finalize_fn   *finalize;
};

#endif // !OPENDMI_ARTIFACT_H
