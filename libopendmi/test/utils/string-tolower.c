//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>

#include <opendmi/utils/string.h>

int main(void)
{
    char string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const char *result = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz0123456789";

    dmi_string_tolower(string);
    if (strcmp(string, result) != 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
