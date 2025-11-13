//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>
#include <stdlib.h>
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

int dmi_ipow(int x, int n)
{
    int y = 1;

    if (n < 0) {
        x = 1 / x;
        n = -n;
    }

    if (n == 0)
        return y;

    while (n > 1) {
        if (n % 2)
            y *= x, n--;

        x *= x, n /= 2;
    }

    return x * y;
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
