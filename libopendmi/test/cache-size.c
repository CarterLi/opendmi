//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/entity/cache.h>

int main(void)
{
    for (size_t i = 0; i < 15; i++) {
        if (dmi_cache_size(1U << i) != (dmi_size_t)(1U << i) * 1024)
            return EXIT_FAILURE;

        if (dmi_cache_size(0x8000U | (1U << i)) != (dmi_size_t)(1U << i) * 65536)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
