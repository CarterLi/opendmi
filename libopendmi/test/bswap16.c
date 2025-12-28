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
    uint16_t value;
    uint16_t result;
};

static bool test_bswap(uint16_t (*func)(uint16_t));

struct test_vector test_data[] =
{
    { 0x0000U, 0x0000U },
    { 0xFFFFU, 0xFFFFU },
    { 0x0123U, 0x2301U }
};

int main(void)
{
    if (!test_bswap(dmi_bswap16_compat))
        return EXIT_FAILURE;
    if (!test_bswap(dmi_bswap16))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

static bool test_bswap(uint16_t (*func)(uint16_t))
{
    for (unsigned i = 0; i < dmi_array_size(test_data); i++) {
        if (func(test_data[i].value) != test_data[i].result)
            return false;
    }

    return true;
}
