//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_WIN32_H
#define OPENDMI_UTILS_WIN32_H

#pragma once

#include <windef.h>
#include <ntdef.h>

#include <opendmi/defs.h>

__BEGIN_DECLS

const char *dmi_win32err_to_string(DWORD error_code);
const char *dmi_ntstatus_to_string(NTSTATUS status);

__END_DECLS

#endif // !OPENDMI_UTILS_WIN32_H
