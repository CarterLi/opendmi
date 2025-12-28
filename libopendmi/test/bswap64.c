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
    uint64_t value;
    uint64_t result;
};

static bool test_bswap(uint64_t (*func)(uint64_t));

struct test_vector test_data[] =
{
    { 0x0000000000000000UL, 0x0000000000000000UL },
    { 0xFFFFFFFFFFFFFFFFUL, 0xFFFFFFFFFFFFFFFFUL },
    { 0x0123456789ABCDEFUL, 0xEFCDAB8967452301UL }
};

int main(void)
{
    if (!test_bswap(dmi_bswap64_compat))
        return EXIT_FAILURE;
    if (!test_bswap(dmi_bswap64))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

static bool test_bswap(uint64_t (*func)(uint64_t))
{
    for (unsigned i = 0; i < dmi_array_size(test_data); i++) {
        if (func(test_data[i].value) != test_data[i].result)
            return false;
    }

    return true;
}
