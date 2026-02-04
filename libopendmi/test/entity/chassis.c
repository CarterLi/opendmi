//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/entity/chassis.h>

void test_chassis_type_name(void **pstate);
void test_chassis_security_status_name(void **pstate);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_chassis_type_name),
        cmocka_unit_test(test_chassis_security_status_name)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

void test_chassis_type_name(void **pstate)
{
    dmi_unused(pstate);

    assert_null(dmi_chassis_type_name(__DMI_CHASSIS_TYPE_COUNT));

    for (int i = 0; i < __DMI_CHASSIS_TYPE_COUNT; i++) {
        assert_non_null(dmi_chassis_type_name(i));
    }
}

void test_chassis_security_status_name(void **pstate)
{
    dmi_unused(pstate);

    assert_null(dmi_chassis_security_status_name(__DMI_CHASSIS_SECURITY_STATUS_COUNT));

    for (int i = 0; i < __DMI_CHASSIS_SECURITY_STATUS_COUNT; i++) {
        assert_non_null(dmi_chassis_security_status_name(i));
    }
}
