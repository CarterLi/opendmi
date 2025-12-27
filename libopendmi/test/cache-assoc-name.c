//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/entity/cache.h>

int main(void)
{
    if (dmi_cache_assoc_name(__DMI_CACHE_ASSOC_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_CACHE_ASSOC_COUNT; i++) {
        if (dmi_cache_assoc_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
