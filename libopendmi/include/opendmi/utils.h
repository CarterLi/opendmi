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

void *dmi_alloc(dmi_context_t *context, size_t size);
void dmi_free(void *ptr);

bool dmi_checksum(const void *data, size_t length);

static inline uint8_t dmi_bswap8(uint8_t value) { return value; };

uint16_t dmi_bswap16(uint16_t value);
uint16_t dmi_bswap16_compat(uint16_t value);

uint32_t dmi_bswap32(uint32_t value);
uint32_t dmi_bswap32_compat(uint32_t value);

uint64_t dmi_bswap64(uint64_t value);
uint64_t dmi_bswap64_compat(uint64_t value);

#define dmi_bswap(value) (_Generic((value),               \
                                   uint64_t: dmi_bswap64, \
                                   uint32_t: dmi_bswap32, \
                                   uint16_t: dmi_bswap16, \
                                   uint8_t:  dmi_bswap8   \
                                  )(value))

uint32_t dmi_ipow32(uint32_t value, unsigned int factor);
uint64_t dmi_ipow64(uint64_t value, unsigned int factor);

uint64_t dmi_decode_bcd(const dmi_byte_t *value, size_t length);

dmi_uuid_t dmi_uuid_decode(const dmi_byte_t value[16]);
void       dmi_uuid_encode(dmi_uuid_t value, uint8_t out[16]);

int dmi_asprintf(char **strp, const char *fmt, ...);
int dmi_vasprintf(char **strp, const char *fmt, va_list ap);

dmi_data_t *dmi_file_read(dmi_context_t *context, const char *path, size_t *plength);

#if !defined(_WIN32)
dmi_data_t *dmi_file_map(dmi_context_t *context, const char *path, size_t *plength);
#endif // !defined(_WIN32)

__END_DECLS

static inline void *dmi_alloc_array(dmi_context_t *context, size_t size, size_t count)
{
    return dmi_alloc(context, size * count);
}

static inline uint8_t dmi_byte_decode(dmi_byte_t value) { return value; }

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static inline uint16_t dmi_word_decode(dmi_word_t value)   { return value; }
static inline uint32_t dmi_dword_decode(dmi_dword_t value) { return value; }
static inline uint64_t dmi_qword_decode(dmi_qword_t value) { return value; }
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN
static inline uint16_t dmi_word_decode(dmi_word_t value)   { return dmi_bswap16(value); }
static inline uint32_t dmi_dword_decode(dmi_dword_t value) { return dmi_bswap32(value); }
static inline uint64_t dmi_qword_decode(dmi_qword_t value) { return dmi_bswap64(value); }
#else
#   error "Unsupported endianness"
#endif

#define dmi_value(value) (_Generic((value),                       \
                                   dmi_qword_t: dmi_qword_decode, \
                                   dmi_dword_t: dmi_dword_decode, \
                                   dmi_word_t:  dmi_word_decode,  \
                                   dmi_byte_t:  dmi_byte_decode   \
                                  )(value))

#endif // !OPENDMI_UTILS_H
