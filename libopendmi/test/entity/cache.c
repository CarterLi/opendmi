//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/entity/cache.h>

static void test_cache_type_name(void **state);
static void test_cache_assoc_name(void **state);
static void test_cache_location_name(void **state);
static void test_cache_mode_name(void **state);
static void test_cache_size(void **state);
static void test_cache_size_ex(void **state);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_cache_type_name),
        cmocka_unit_test(test_cache_assoc_name),
        cmocka_unit_test(test_cache_location_name),
        cmocka_unit_test(test_cache_mode_name),
        cmocka_unit_test(test_cache_size),
        cmocka_unit_test(test_cache_size_ex)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_cache_type_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_cache_type_name(__DMI_CACHE_TYPE_COUNT));

    for (int i = 0; i < __DMI_CACHE_TYPE_COUNT; i++) {
        assert_non_null(dmi_cache_type_name(i));
    }
}

static void test_cache_assoc_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_cache_assoc_name(__DMI_CACHE_ASSOC_COUNT));

    for (int i = 0; i < __DMI_CACHE_ASSOC_COUNT; i++) {
        assert_non_null(dmi_cache_assoc_name(i));
    }
}

static void test_cache_location_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_cache_location_name(__DMI_CACHE_LOCATION_COUNT));

    for (int i = 1; i < __DMI_CACHE_LOCATION_COUNT; i++) {
        assert_non_null(dmi_cache_location_name(i));
    }
}

static void test_cache_mode_name(void **state)
{
    dmi_unused(state);

    assert_null(dmi_cache_mode_name(__DMI_CACHE_MODE_COUNT));

    for (int i = 1; i < __DMI_CACHE_MODE_COUNT; i++) {
        assert_non_null(dmi_cache_mode_name(i));
    }
}

static void test_cache_size(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < 15; i++) {
        dmi_size_t base_size = (dmi_size_t)1u << i;

        assert_uint_equal(dmi_cache_size(1u << i), base_size * 1024);
        assert_uint_equal(dmi_cache_size(0x8000u | (1u << i)), base_size * 65536);
    }
}

static void test_cache_size_ex(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < 31; i++) {
        size_t base_size = (dmi_size_t)1u << i;

        assert_uint_equal(dmi_cache_size_ex(1u << i), base_size * 1024);
        assert_uint_equal(dmi_cache_size_ex(0x80000000u | (1u << i)), base_size * 65536);
    }
}
