//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_H
#define OPENDMI_UTILS_H

#pragma once

#include <opendmi/utils/endian.h>

__BEGIN_DECLS

void *dmi_alloc(dmi_context_t *context, size_t size);
void dmi_free(void *ptr);

bool dmi_checksum(const void *data, size_t length);

uint32_t dmi_ipow32(uint32_t value, unsigned int factor);
uint64_t dmi_ipow64(uint64_t value, unsigned int factor);

int dmi_asprintf(char **strp, const char *fmt, ...);
int dmi_vasprintf(char **strp, const char *fmt, va_list ap);

void dmi_strlwr(char *str);
void dmi_strupr(char *str);

dmi_data_t *dmi_file_get(dmi_context_t *context, const char *path, size_t *plength);

#if !defined(_WIN32)
    dmi_data_t *dmi_memory_get(dmi_context_t *context, const char *path, size_t base, size_t length);
#endif // !defined(_WIN32)

__END_DECLS

static inline void *dmi_alloc_array(dmi_context_t *context, size_t size, size_t count)
{
    return dmi_alloc(context, size * count);
}

#endif // !OPENDMI_UTILS_H
