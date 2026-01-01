//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/entity/memory-array.h>

int main(void)
{
    if (dmi_memory_array_usage_name(__DMI_MEMORY_ARRAY_USAGE_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_MEMORY_ARRAY_USAGE_COUNT; i++) {
        if (dmi_memory_array_usage_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
