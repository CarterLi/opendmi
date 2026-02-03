//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/attribute.h>
#include <opendmi/utils/uuid.h>
#include <opendmi/utils/version.h>

static void test_attribute_format_address(void **state);
static void test_attribute_format_bool(void **state);
static void test_attribute_format_bool_ex(void **state);
static void test_attribute_format_decimal(void **state);
static void test_attribute_format_enum(void **state);
static void test_attribute_format_handle(void **state);
static void test_attribute_format_integer(void **state);
static void test_attribute_format_set(void **state);
static void test_attribute_format_size(void **state);
static void test_attribute_format_string(void **state);
static void test_attribute_format_uuid(void **state);
static void test_attribute_format_version(void **state);
static int free_attribute_value(void **state);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_teardown(test_attribute_format_address, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_bool, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_bool_ex, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_decimal, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_enum, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_handle, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_integer, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_set, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_size, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_string, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_uuid, free_attribute_value),
        cmocka_unit_test_teardown(test_attribute_format_version, free_attribute_value)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_attribute_format_address(void **state)
{
    dmi_unused(state);
    skip();
}

static void test_attribute_format_bool(void **state)
{
    dmi_unused(state);

    static const dmi_attribute_t attr = {
        .value   = {
            .size   = sizeof(dmi_handle_t),
            .offset = 0
        },
        .counter = DMI_MEMBER_NULL,
        .type    = DMI_ATTRIBUTE_TYPE_BOOL,
        .params  = {}
    };

    const struct {
        const void *value;
        bool pretty;
        const char *expected;
    } test_data[] = {
        { dmi_value_ptr((bool)0),  true,  "no"    },
        { dmi_value_ptr((bool)0),  false, "false" },
        { dmi_value_ptr((bool)1),  true,  "yes"   },
        { dmi_value_ptr((bool)1),  false, "true"  },
        { dmi_value_ptr((bool)-1), true,  "yes"   },
        { dmi_value_ptr((bool)-1), false, "true"  },
        { dmi_value_ptr((bool)2),  true,  "yes"   },
        { dmi_value_ptr((bool)2),  false, "true"  }
    };

    *state = nullptr;

    for (size_t i = 0; i < countof(test_data); i++) {
        const void *value    = test_data[i].value;
        bool        pretty   = test_data[i].pretty;
        const char *expected = test_data[i].expected;
        char       *result   = nullptr;

        result = dmi_attribute_format(&attr, value, pretty);
        *state = result;

        assert_non_null(result);
        assert_string_equal(result, expected);

        free(result);
    }

    *state = nullptr;
}

static void test_attribute_format_bool_ex(void **state)
{
    dmi_unused(state);

    const dmi_name_set_t test_values = {
        .names = (const dmi_name_t[]) {
            { .id = false, .code = "off", .name = "OFF" },
            { .id = true,  .code = "on",  .name = "ON"  }
        }
    };

    const dmi_attribute_t attr = {
        .value   = {
            .size   = sizeof(dmi_handle_t),
            .offset = 0
        },
        .counter = DMI_MEMBER_NULL,
        .type    = DMI_ATTRIBUTE_TYPE_BOOL,
        .params  = {
            .values = &test_values
        }
    };

    const struct {
        const void *value;
        bool pretty;
        const char *expected;
    } test_data[] = {
        { dmi_value_ptr((bool)0),  true,  "OFF" },
        { dmi_value_ptr((bool)0),  false, "off" },
        { dmi_value_ptr((bool)1),  true,  "ON"  },
        { dmi_value_ptr((bool)1),  false, "on"  },
        { dmi_value_ptr((bool)-1), true,  "ON"  },
        { dmi_value_ptr((bool)-1), false, "on"  },
        { dmi_value_ptr((bool)2),  true,  "ON"  },
        { dmi_value_ptr((bool)2),  false, "on"  }
    };

    *state = nullptr;

    for (size_t i = 0; i < countof(test_data); i++) {
        const void *value    = test_data[i].value;
        bool        pretty   = test_data[i].pretty;
        const char *expected = test_data[i].expected;
        char       *result   = nullptr;

        result = dmi_attribute_format(&attr, value, pretty);
        *state = result;

        assert_non_null(result);
        assert_string_equal(result, expected);

        free(result);
    }

    *state = nullptr;
}

static void test_attribute_format_decimal(void **state)
{
    dmi_unused(state);
    skip();
}

static void test_attribute_format_enum(void **state)
{
    dmi_unused(state);
    skip();
}

static void test_attribute_format_handle(void **state)
{
    dmi_unused(state);

    const struct {
        const void *value;
        bool pretty;
        const char *expected;
    } test_data[] = {
        { dmi_value_ptr((dmi_handle_t)0x0000u), false, "0x0000" },
        { dmi_value_ptr((dmi_handle_t)0x0000u), true,  "0x0000" },
        { dmi_value_ptr((dmi_handle_t)0x1234u), false, "0x1234" },
        { dmi_value_ptr((dmi_handle_t)0x1234u), true,  "0x1234" },
        { dmi_value_ptr((dmi_handle_t)0xABCDu), false, "0xABCD" },
        { dmi_value_ptr((dmi_handle_t)0xABCDu), true,  "0xABCD" },
        { dmi_value_ptr((dmi_handle_t)0xFFFFu), false, "0xFFFF" },
        { dmi_value_ptr((dmi_handle_t)0xFFFFu), true , "0xFFFF" }
    };

    static const dmi_attribute_t attr = {
        .value   = {
            .size   = sizeof(dmi_handle_t),
            .offset = 0
        },
        .counter = DMI_MEMBER_NULL,
        .type    = DMI_ATTRIBUTE_TYPE_HANDLE,
        .params  = {}
    };

    *state = nullptr;

    for (size_t i = 0; i < countof(test_data); i++) {
        const void *value    = test_data[i].value;
        bool        pretty   = test_data[i].pretty;
        const char *expected = test_data[i].expected;
        char       *result   = nullptr;

        result = dmi_attribute_format(&attr, value, pretty);
        *state = result;

        assert_non_null(result);
        assert_string_equal(result, expected);

        free(result);
    }

    *state = nullptr;
}

static void test_attribute_format_integer(void **state)
{
    dmi_unused(state);
    skip();
}

static void test_attribute_format_set(void **state)
{
    dmi_unused(state);
    skip();
}

static void test_attribute_format_size(void **state)
{
    dmi_unused(state);
    skip();
}

static void test_attribute_format_string(void **state)
{
    dmi_unused(state);
    skip();
}

static void test_attribute_format_uuid(void **state)
{
    dmi_unused(state);

    const struct {
        uint8_t value[16];
        bool pretty;
        const char *expected;
    } test_data[] = {
        {
            .value = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            },
            .pretty   = false,
            .expected = "00000000-0000-0000-0000-000000000000"
        },
        {
            .value = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            },
            .pretty   = true,
            .expected = "00000000-0000-0000-0000-000000000000"
        },
        {
            .value = {
                0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
            },
            .pretty   = false,
            .expected = "00112233-4455-6677-8899-AABBCCDDEEFF"
        },
        {
            .value = {
                0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
            },
            .pretty   = true,
            .expected = "00112233-4455-6677-8899-AABBCCDDEEFF"
        },
        {
            .value = {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
            },
            .pretty   = false,
            .expected = "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"
        },
        {
            .value = {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
            },
            .pretty   = true,
            .expected = "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"
        }
    };

    static const dmi_attribute_t attr = {
        .value   = {
            .size   = sizeof(dmi_uuid_t),
            .offset = 0
        },
        .counter = DMI_MEMBER_NULL,
        .type    = DMI_ATTRIBUTE_TYPE_UUID,
        .params  = {}
    };

    *state = nullptr;

    for (size_t i = 0; i < countof(test_data); i++) {
        const void *value    = test_data[i].value;
        bool        pretty   = test_data[i].pretty;
        const char *expected = test_data[i].expected;
        char       *result   = nullptr;

        result = dmi_attribute_format(&attr, value, pretty);
        *state = result;

        assert_non_null(result);
        assert_string_equal(result, expected);

        free(result);
    }

    *state = nullptr;
}

static void test_attribute_format_version(void **state)
{
    dmi_unused(state);

    const struct {
        const void *value;
        int scale;
        bool pretty;
        const char *expected;
    } test_data[] = {
        { dmi_value_ptr(dmi_version(1, 2, 3)), 0, false, "1.2.3" },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 0, true,  "1.2.3" },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 1, false, "1"     },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 1, true,  "1"     },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 2, false, "1.2"   },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 2, true,  "1.2"   },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 3, false, "1.2.3" },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 3, true,  "1.2.3" },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 4, false, "1.2.3" },
        { dmi_value_ptr(dmi_version(1, 2, 3)), 4, true,  "1.2.3" }
    };

    *state = nullptr;

    for (size_t i = 0; i < countof(test_data); i++) {
        const void *value    = test_data[i].value;
        int         scale    = test_data[i].scale;
        bool        pretty   = test_data[i].pretty;
        const char *expected = test_data[i].expected;
        char       *result   = nullptr;

        const dmi_attribute_t attr = {
            .value   = {
                .size   = sizeof(dmi_version_t),
                .offset = 0
            },
            .counter = DMI_MEMBER_NULL,
            .type    = DMI_ATTRIBUTE_TYPE_VERSION,
            .params  = {
                .scale = scale
            }
        };

        result = dmi_attribute_format(&attr, value, pretty);
        *state = result;

        assert_non_null(result);
        assert_string_equal(result, expected);

        free(result);
    }

    *state = nullptr;
}

static int free_attribute_value(void **state)
{
    if (*state != nullptr)
        free(*state);

    return 0;
}
