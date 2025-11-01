//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_H
#define OPENDMI_UTILS_H

#pragma once

#include <opendmi/types.h>

__BEGIN_DECLS

bool dmi_checksum(const void *data, size_t length);
dmi_data_t *dmi_file_map(dmi_context_t *context, const char *path, size_t *plength);

__END_DECLS

#endif // !OPENDMI_UTILS_H
