//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/utils/version.h>

struct test_vector
{
    unsigned int major;
    unsigned int minor;
    unsigned int revision;
    dmi_version_t result;
};

struct test_vector test_data[] =
{
    { 0x00, 0x00, 0x00, 0x00000000u },
    { 0x00, 0x00, 0x12, 0x00000012u },
    { 0x00, 0x12, 0x00, 0x00001200u },
    { 0x00, 0x12, 0x34, 0x00001234u },
    { 0x12, 0x00, 0x00, 0x00120000u },
    { 0x12, 0x00, 0x34, 0x00120034u },
    { 0x12, 0x34, 0x00, 0x00123400u },
    { 0x12, 0x34, 0x56, 0x00123456u }
};

int main(void)
{
    for (size_t i = 0; i < countof(test_data); i++) {
        dmi_version_t result;

        result = dmi_version(test_data[i].major, test_data[i].minor, test_data[i].revision);
        if (result != test_data[i].result)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
