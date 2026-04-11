//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/backend.h>

#include <opendmi/backend/dump.h>
#if defined(__linux__)
#   include <opendmi/backend/linux.h>
#   define DMI_BACKEND dmi_linux_backend
#elif defined(__APPLE__)
#   include <opendmi/backend/darwin.h>
#   define DMI_BACKEND dmi_darwin_backend
#elif defined(__FreeBSD__)
#   include <opendmi/backend/freebsd.h>
#   define DMI_BACKEND dmi_freebsd_backend
#elif defined(__NetBSD__)
#   include <opendmi/backend/netbsd.h>
#   define DMI_BACKEND dmi_netbsd_backend
#elif defined(_WIN32)
#   include <opendmi/backend/windows.h>
#   define DMI_BACKEND dmi_windows_backend
#else
#   error "Unsupported OS type"
#endif

dmi_backend_t *dmi_backend = &DMI_BACKEND;
