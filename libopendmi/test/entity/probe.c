//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/entity/probe.h>

static void test_probe_location_name(void **pstate);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_probe_location_name)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_probe_location_name(void **pstate)
{
    dmi_unused(pstate);

    assert_null(dmi_probe_location_name(__DMI_PROBE_LOCATION_COUNT));

    for (int i = 0; i < __DMI_PROBE_LOCATION_COUNT; i++) {
        assert_non_null(dmi_probe_location_name(i));
    }
}
