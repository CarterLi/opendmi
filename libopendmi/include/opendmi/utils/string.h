//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_STRING_H
#define OPENDMI_UTILS_STRING_H

#pragma once

#include <stdarg.h>
#include <opendmi/types.h>

__BEGIN_DECLS

int dmi_asprintf(char **strp, const char *format, ...);
int dmi_vasprintf(char **strp, const char *format, va_list args);

void dmi_string_tolower(char *str);
void dmi_string_toupper(char *str);

__END_DECLS

#endif // !OPENDMI_UTILS_STRING_H
