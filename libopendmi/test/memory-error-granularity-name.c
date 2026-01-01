//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/entity/memory-error.h>

int main(void)
{
    if (dmi_memory_error_granularity_name(__DMI_MEMORY_ERROR_GRANULARITY_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_MEMORY_ERROR_GRANULARITY_COUNT; i++) {
        if (dmi_memory_error_granularity_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
