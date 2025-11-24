//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/table/memory-device.h>

int main(void)
{
    for (unsigned i = 0; i < 15; i++) {
        if (dmi_memory_device_size(1u << i) != (dmi_size_t)(1u << i) * 1048576)
            return EXIT_FAILURE;

        if (dmi_memory_device_size(0x8000u | (1u << i)) != (dmi_size_t)(1u << i) * 1024)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
