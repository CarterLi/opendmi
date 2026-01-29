//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/entity/pointing-device.h>

int main(void)
{
    if (dmi_pointing_device_type_name(__DMI_POINTING_DEVICE_TYPE_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_POINTING_DEVICE_TYPE_COUNT; i++) {
        if (dmi_pointing_device_type_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
