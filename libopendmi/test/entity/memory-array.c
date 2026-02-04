//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/entity/memory-array.h>

static void test_memory_array_location_name(void **pstate);
static void test_memory_array_usage_name(void **pstate);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_memory_array_location_name),
        cmocka_unit_test(test_memory_array_usage_name)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_memory_array_location_name(void **pstate)
{
    dmi_unused(pstate);

    assert_null(dmi_memory_array_location_name(__DMI_MEMORY_ARRAY_LOCATION_COUNT));

    for (int i = 0; i < __DMI_MEMORY_ARRAY_LOCATION_COUNT; i++) {
        if ((i >= __DMI_MEMORY_ARRAY_LOCATION_UNASSIGNED_START) and
            (i <= __DMI_MEMORY_ARRAY_LOCATION_UNASSIGNED_END))
            assert_null(dmi_memory_array_location_name(i));
        else
            assert_non_null(dmi_memory_array_location_name(i));
    }
}

static void test_memory_array_usage_name(void **pstate)
{
    dmi_unused(pstate);

    assert_null(dmi_memory_array_usage_name(__DMI_MEMORY_ARRAY_USAGE_COUNT));

    for (int i = 0; i < __DMI_MEMORY_ARRAY_USAGE_COUNT; i++) {
        assert_non_null(dmi_memory_array_usage_name(i));
    }
}
