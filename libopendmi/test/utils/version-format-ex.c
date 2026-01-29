//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>

#include <opendmi/utils/version.h>

struct test_vector
{
    dmi_version_t value;
    int level;
    const char *result;
};

struct test_vector test_data[] =
{
    { DMI_VERSION(0, 0, 0), DMI_VERSION_LEVEL_MAJOR, "0" },
    { DMI_VERSION(0, 1, 0), DMI_VERSION_LEVEL_MAJOR, "0" },
    { DMI_VERSION(1, 0, 0), DMI_VERSION_LEVEL_MAJOR, "1" },
    { DMI_VERSION(1, 2, 0), DMI_VERSION_LEVEL_MAJOR, "1" },
    { DMI_VERSION(1, 2, 3), DMI_VERSION_LEVEL_MAJOR, "1" },

    { DMI_VERSION(0, 0, 0), DMI_VERSION_LEVEL_MINOR, "0.0" },
    { DMI_VERSION(0, 1, 0), DMI_VERSION_LEVEL_MINOR, "0.1" },
    { DMI_VERSION(1, 0, 0), DMI_VERSION_LEVEL_MINOR, "1.0" },
    { DMI_VERSION(1, 2, 0), DMI_VERSION_LEVEL_MINOR, "1.2" },
    { DMI_VERSION(1, 2, 3), DMI_VERSION_LEVEL_MINOR, "1.2" },

    { DMI_VERSION(0, 0, 0), DMI_VERSION_LEVEL_REVISION, "0.0.0" },
    { DMI_VERSION(0, 1, 0), DMI_VERSION_LEVEL_REVISION, "0.1.0" },
    { DMI_VERSION(1, 0, 0), DMI_VERSION_LEVEL_REVISION, "1.0.0" },
    { DMI_VERSION(1, 2, 0), DMI_VERSION_LEVEL_REVISION, "1.2.0" },
    { DMI_VERSION(1, 2, 3), DMI_VERSION_LEVEL_REVISION, "1.2.3" },

    { DMI_VERSION(0, 0, 0), -1, nullptr },
    { DMI_VERSION(0, 1, 0), -1, nullptr },
    { DMI_VERSION(1, 0, 0), -1, nullptr },
    { DMI_VERSION(1, 2, 0), -1, nullptr },
    { DMI_VERSION(1, 2, 3), -1, nullptr },

    { DMI_VERSION(0, 0, 0), INT_MAX, nullptr },
    { DMI_VERSION(0, 1, 0), INT_MAX, nullptr },
    { DMI_VERSION(1, 0, 0), INT_MAX, nullptr },
    { DMI_VERSION(1, 2, 0), INT_MAX, nullptr },
    { DMI_VERSION(1, 2, 3), INT_MAX, nullptr },
};

int main(void)
{
    for (size_t i = 0; i < countof(test_data); i++) {
        int status;
        char *result;

        result = dmi_version_format_ex(test_data[i].value, test_data[i].level);

        if (test_data[i].result == nullptr) {
            if (result != nullptr) {
                free(result);
                return EXIT_FAILURE;
            }

            continue;
        }

        if (result == nullptr)
            return EXIT_FAILURE;

        status = strcmp(result, test_data[i].result);
        free(result);

        if (status != 0)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
