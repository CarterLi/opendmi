//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_TEXT_TYPES_H
#define OPENDMI_FORMAT_TEXT_TYPES_H

#pragma once

#include <stdio.h>

#include <opendmi/types.h>
#include <opendmi/attribute.h>

typedef struct dmi_text_session
{
    dmi_context_t *context;
    FILE *stream;
    bool is_tty;
} dmi_text_session_t;

#endif // !OPENDMI_FORMAT_TEXT_TYPES_H
