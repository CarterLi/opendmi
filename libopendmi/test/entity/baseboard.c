//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/entity/baseboard.h>

static void test_baseboard_type_name(void **state);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_baseboard_type_name)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_baseboard_type_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_baseboard_type_name(__DMI_BASEBOARD_TYPE_COUNT));

    for (int i = 0; i < __DMI_BASEBOARD_TYPE_COUNT; i++) {
        assert_non_null(dmi_baseboard_type_name(i));
    }
}
