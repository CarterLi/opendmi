//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "config.h"

#include <sys/stat.h>

#ifdef HAVE_SYS_MMAN_H
#include <sys/mman.h>
#endif // HAVE_SYS_MMAN_H

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif // HAVE_UNISTD_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

bool dmi_checksum(const void *data, size_t length)
{
    if (data == nullptr) {
        errno = EINVAL;
        return false;
    }

    uint8_t sum   = 0;
    size_t  index = 0;

    while (index < length) {
        sum += ((const uint8_t *)data)[index++];
    }

    return (sum == 0) ? true : false;
}

uint16_t dmi_bswap16(uint16_t value)
{
#if defined(_MSC_VER)
    value = _byteswap_ushort(value);
#elif defined(__GNUC__) || defined(__clang__)
    value = __builtin_bswap16(value);
#else
    value = dmi_bswap16_compat(value);
#endif

    return value;
}

uint16_t dmi_bswap16_compat(uint16_t value)
{
    // Flip bytes
    value = ((value & 0x00FFU) << 8) | ((value & 0xFF00U) >> 8);

    return value;
}

uint32_t dmi_bswap32(uint32_t value)
{
#if defined(_MSC_VER)
    value = _byteswap_ulong(value);
#elif defined(__GNUC__) || defined(__clang__)
    value = __builtin_bswap32(value);
#else
    value = dmi_bswap32_compat(value);
#endif

    return value;
}

uint32_t dmi_bswap32_compat(uint32_t value)
{
    // Flip bytes
    value = ((value & 0x00FF00FFU) << 8) | ((value & 0xFF00FF00U) >> 8);

    // Flip words
    value = ((value & 0x0000FFFFU) << 16) | ((value & 0xFFFF0000U) >> 16);

    return value;
}

uint64_t dmi_bswap64(uint64_t value)
{
#if defined(_MSC_VER)
    value = _byteswap_uint64(value);
#elif defined(__GNUC__) || defined(__clang__)
    value = __builtin_bswap64(value);
#else
    value = dmi_bswap64_compat(value);
#endif

    return value;
}

uint64_t dmi_bswap64_compat(uint64_t value)
{
    // Flip bytes
    value = ((value & 0x00FF00FF00FF00FFUL) << 8) | ((value & 0xFF00FF00FF00FF00UL) >> 8);

    // Flip words
    value = ((value & 0x0000FFFF0000FFFFUL) << 16) | ((value & 0xFFFF0000FFFF0000UL) >> 16);

    // Flip double words
    value = ((value & 0x00000000FFFFFFFFUL) << 32) | ((value & 0xFFFFFFFF00000000UL) >> 32);

    return value;
}

uint32_t dmi_ipow32(uint32_t value, unsigned int factor)
{
    uint32_t result = 1;

    if (factor == 0)
        return result;

    while (factor > 1) {
        if (factor % 2)
            result *= value, factor--;

        value *= value, factor /= 2;
    }

    return value * result;
}

uint64_t dmi_ipow64(uint64_t value, unsigned int factor)
{
    uint64_t result = 1;

    if (factor == 0)
        return result;

    while (factor > 1) {
        if (factor % 2)
            result *= value, factor--;

        value *= value, factor /= 2;
    }

    return value * result;
}

uint64_t dmi_decode_bcd(const dmi_byte_t *value, size_t length)
{
    uint64_t result = 0;
    uint64_t factor = 1;

    assert(value != nullptr);
    assert(length > 0);

    while (length > 0) {
        result += (*value & 0x0F) * factor;
        result += ((*value & 0xF0) >> 4) * factor * 10;
        factor *= 100;

        length--, value++;
    }

    return result;
}

dmi_uuid_t dmi_decode_uuid(const dmi_byte_t value[16])
{
    dmi_uuid_t uuid;

    memcpy(uuid._value, value, sizeof(uuid._value));

    uuid.time_low            = dmi_value(uuid.time_low);
    uuid.time_mid            = dmi_value(uuid.time_mid);
    uuid.time_hi_and_version = dmi_value(uuid.time_hi_and_version);

    return uuid;
}

int dmi_asprintf(char **strp, const char *fmt, ...)
{
    int rv;
    va_list ap;

    va_start(ap, fmt);
    rv = dmi_vasprintf(strp, fmt, ap);
    va_end(ap);

    return rv;
}

int dmi_vasprintf(char **strp, const char *fmt, va_list ap)
{
    int rv;

#if defined(_WIN32)
    // _vscprintf tells you how big the buffer needs to be
    int len = _vscprintf(fmt, ap);
    if (len < 0)
        return -1;

    size_t size = (size_t)len + 1;
    char *str = malloc(size);
    if (!str) {
        *strp = nullptr;
        return -1;
    }

    // vsprintf_s is the "secure" version of vsprintf
    rv = vsprintf_s(str, size, fmt, ap);
    if (rv < 0) {
        free(str);
        *strp = nullptr;
        return -1;
    }

    *strp = str;
#else // !defined(_WIN32)
    rv = vasprintf(strp, fmt, ap);
#endif // !defined(_WIN32)

    return rv;
}

#if !defined(_WIN32)
dmi_data_t *dmi_file_map(dmi_context_t *context, const char *path, size_t *plength)
{
    if ((context == nullptr) || (path == nullptr) || (plength == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }

    int         fd   = -1;
    dmi_data_t *data = nullptr;
    struct stat st;

    bool success = false;
    do {
        fd = open(path, O_RDONLY);
        if (fd < 0)
            break;
 
        if (fstat(fd, &st) < 0)
            break;

        if ((data = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == nullptr)
            break;

        success = true;
    } while (false);

    if (fd >= 0)
        close(fd);

    if (!success) {
        dmi_set_error(context, DMI_ERROR_SYSTEM);
        return nullptr;
    }

    *plength = st.st_size;

    return data;
}
#endif // !defined(_WIN32)
