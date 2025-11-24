//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>

#include <opendmi/utils.h>

struct test_vector
{
    uint32_t value;
    uint32_t result;
};

static bool test_bswap(uint32_t (*func)(uint32_t));

struct test_vector test_data[] =
{
    { 0x00000000U, 0x00000000U },
    { 0xFFFFFFFFU, 0xFFFFFFFFU },
    { 0x01234567U, 0x67452301U }
};

int main(void)
{
    if (!test_bswap(dmi_bswap32_compat))
        return EXIT_FAILURE;
    if (!test_bswap(dmi_bswap32))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

static bool test_bswap(uint32_t (*func)(uint32_t))
{
    for (unsigned i = 0; i < DMI_ARRAY_SIZE(test_data); i++) {
        if (func(test_data[i].value) != test_data[i].result)
            return false;
    }

    return true;
}
