//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/entity/memory-device.h>

static void test_memory_device_type_name(void **state);
static void test_memory_device_form_factor_name(void **state);
static void test_memory_device_tech_name(void **state);
static void test_memory_device_size(void **state);
static void test_memory_device_size_ex(void **state);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_memory_device_type_name),
        cmocka_unit_test(test_memory_device_form_factor_name),
        cmocka_unit_test(test_memory_device_tech_name),
        cmocka_unit_test(test_memory_device_size),
        cmocka_unit_test(test_memory_device_size_ex)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_memory_device_type_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_memory_device_type_name(__DMI_MEMORY_DEVICE_TYPE_COUNT));

    for (int i = 1; i < __DMI_MEMORY_DEVICE_TYPE_COUNT; i++) {
        if ((i >= __DMI_MEMORY_DEVICE_TYPE_UNASSIGNED_START) and
            (i <= __DMI_MEMORY_DEVICE_TYPE_UNASSIGNED_END))
            assert_null(dmi_memory_device_type_name(i));
        else
            assert_non_null(dmi_memory_device_type_name(i));
    }
}

static void test_memory_device_form_factor_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_memory_device_form_factor_name(__DMI_MEMORY_DEVICE_FORM_FACTOR_COUNT));

    for (int i = 1; i < __DMI_MEMORY_DEVICE_FORM_FACTOR_COUNT; i++) {
        assert_non_null(dmi_memory_device_form_factor_name(i));
    }
}

static void test_memory_device_tech_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_memory_device_tech_name(__DMI_MEMORY_DEVICE_TECH_COUNT));

    for (int i = 1; i < __DMI_MEMORY_DEVICE_TECH_COUNT; i++) {
        assert_non_null(dmi_memory_device_tech_name(i));
    }
}

static void test_memory_device_size(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < 15; i++) {
        dmi_size_t base_size = (dmi_size_t)1u << i;

        assert_uint_equal(dmi_memory_device_size(1u << i), base_size * 1048576);
        assert_uint_equal(dmi_memory_device_size(0x8000u | (1u << i)), base_size * 1024);
    }
}

static void test_memory_device_size_ex(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < 31; i++) {
        size_t base_size = (dmi_size_t)1u << i;

        assert_uint_equal(dmi_memory_device_size_ex(1u << i), base_size * 1048576);
        assert_uint_equal(dmi_memory_device_size_ex(0x80000000u | (1u << i)), SIZE_MAX);
    }
}
