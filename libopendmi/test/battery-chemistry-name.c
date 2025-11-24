//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/table/battery.h>

int main(void)
{
    if (dmi_battery_chemistry_name(0) != nullptr)
        return EXIT_FAILURE;
    if (dmi_battery_chemistry_name(__DMI_BATTERY_CHEMISTRY_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 1; i < __DMI_BATTERY_CHEMISTRY_COUNT; i++) {
        if (dmi_battery_chemistry_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
