//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/entity/slot.h>

int main(void)
{
    if (dmi_slot_usage_name(__DMI_SLOT_USAGE_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_SLOT_USAGE_COUNT; i++) {
        if (dmi_slot_usage_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
