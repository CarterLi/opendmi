//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_JSON_HANDLERS_H
#define OPENDMI_FORMAT_JSON_HANDLERS_H

#pragma once

#include <stdio.h>

#include <opendmi/format/json/types.h>

__BEGIN_DECLS

void *dmi_json_initialize(dmi_context_t *context, FILE *stream);
void dmi_json_finalize(dmi_json_session_t *session);

__END_DECLS

#endif // !OPENDMI_FORMAT_JSON_HANDLERS_H
