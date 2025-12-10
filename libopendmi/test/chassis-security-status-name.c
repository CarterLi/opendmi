//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/table/chassis.h>

int main(void)
{
    if (dmi_chassis_security_status_name(0) != nullptr)
        return EXIT_FAILURE;
    if (dmi_chassis_security_status_name(__DMI_CHASSIS_SECURITY_STATUS_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 1; i < __DMI_CHASSIS_SECURITY_STATUS_COUNT; i++) {
        if (dmi_chassis_security_status_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
