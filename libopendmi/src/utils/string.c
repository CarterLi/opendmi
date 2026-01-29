//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include <opendmi/utils/string.h>


int dmi_asprintf(char **strp, const char *format, ...)
{
    int rv;
    va_list args;

    assert(strp != nullptr);
    assert(format != nullptr);

    va_start(args, format);
    rv = dmi_vasprintf(strp, format, args);
    va_end(args);

    return rv;
}

int dmi_vasprintf(char **strp, const char *format, va_list args)
{
    int rv;

#if defined(_WIN32)
    // _vscprintf tells you how big the buffer needs to be
    int len = _vscprintf(format, args);
    if (len < 0)
        return -1;

    size_t size = (size_t)len + 1;
    char *str = malloc(size);
    if (str == nullptr) {
        *strp = nullptr;
        return -1;
    }

    // vsprintf_s is the "secure" version of vsprintf
    rv = vsprintf_s(str, size, format, args);
    if (rv < 0) {
        free(str);
        *strp = nullptr;
        return -1;
    }

    *strp = str;
#else // !defined(_WIN32)
    rv = vasprintf(strp, format, args);
#endif // !defined(_WIN32)

    return rv;
}

void dmi_strlwr(char *str)
{
    assert(str != nullptr);

    while (*str != 0) {
        *str = tolower(*str);
        str++;
    }
}

void dmi_strupr(char *str)
{
    assert(str != nullptr);

    while (*str != 0) {
        *str = toupper(*str);
        str++;
    }
}
