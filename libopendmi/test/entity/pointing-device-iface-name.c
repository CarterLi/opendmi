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
    if (dmi_pointing_device_iface_name(__DMI_POINTING_DEVICE_IFACE_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_POINTING_DEVICE_IFACE_COUNT; i++) {
        const char *name;

        name = dmi_pointing_device_iface_name(i);
        if ((i >= __DMI_POINTING_DEVICE_IFACE_UNASSIGNED_START) and
            (i <= __DMI_POINTING_DEVICE_IFACE_UNASSIGNED_END))
        {
            if (name != nullptr)
                return EXIT_FAILURE;
        } else {
            if (name == nullptr)
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
