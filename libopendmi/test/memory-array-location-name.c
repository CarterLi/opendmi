//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/table/memory-array.h>

int main(void)
{
    if (dmi_memory_array_location_name(__DMI_MEMORY_ARRAY_LOCATION_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_MEMORY_ARRAY_LOCATION_COUNT; i++) {
        const char *str = dmi_memory_array_location_name(i);
        
        if ((i > 0x0A) and (i < 0xA0)) {
            if (str != nullptr)
                return EXIT_FAILURE;
        } else {
            if (str == nullptr)
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
