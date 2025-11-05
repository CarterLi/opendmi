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

uint16_t dmi_bswap16(uint16_t value);
uint16_t dmi_bswap16_compat(uint16_t value);

uint32_t dmi_bswap32(uint32_t value);
uint32_t dmi_bswap32_compat(uint32_t value);

uint64_t dmi_bswap64(uint64_t value);
uint64_t dmi_bswap64_compat(uint64_t value);

dmi_data_t *dmi_file_map(dmi_context_t *context, const char *path, size_t *plength);

__END_DECLS

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static inline uint16_t dmi_decode_word(dmi_word_t value)   { return value; }
static inline uint32_t dmi_decode_dword(dmi_dword_t value) { return value; }
static inline uint64_t dmi_decode_qword(dmi_qword_t value) { return value; }
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN
static inline uint16_t dmi_decode_word(dmi_word_t value)   { return dmi_bswap16(value); }
static inline uint32_t dmi_decode_dword(dmi_dword_t value) { return dmi_bswap32(value); }
static inline uint64_t dmi_decode_qword(dmi_qword_t value) { return dmi_bswap64(value); }
#else
#   error "Unsupported endianness"
#endif

#endif // !OPENDMI_UTILS_H
