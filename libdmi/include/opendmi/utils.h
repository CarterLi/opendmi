//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_H
#define OPENDMI_UTILS_H

#pragma once

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

const char *dmi_name(const char **table, size_t id, size_t count);

__END_DECLS

#endif // !OPENDMI_UTILS_H
