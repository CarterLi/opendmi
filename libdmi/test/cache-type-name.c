//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/table/cache.h>

int main(void)
{
    if (dmi_cache_type_name(0) != nullptr)
        return EXIT_FAILURE;
    if (dmi_cache_type_name(__DMI_CACHE_TYPE_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 1; i < __DMI_CACHE_TYPE_COUNT; i++) {
        if (dmi_cache_type_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
