//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/table/common.h>

int main(void)
{
    if (dmi_error_correct_type_name(__DMI_ERROR_CORRECT_TYPE_COUNT) != nullptr)
        return EXIT_FAILURE;

    for (int i = 0; i < __DMI_ERROR_CORRECT_TYPE_COUNT; i++) {
        if (dmi_error_correct_type_name(i) == nullptr)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
