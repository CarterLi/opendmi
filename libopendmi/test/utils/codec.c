//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/utils/codec.h>

typedef struct test_vector_16 test_vector_16_t;
typedef struct test_vector_32 test_vector_32_t;
typedef struct test_vector_64 test_vector_64_t;
typedef struct test_vector_bcd test_vector_bcd_t;

struct test_vector_16
{
    uint8_t  encoded[2];
    uint16_t decoded;
};

struct test_vector_32
{
    uint8_t  encoded[4];
    uint32_t decoded;
};

struct test_vector_64
{
    uint8_t  encoded[8];
    uint64_t decoded;
};

struct test_vector_bcd {
    uint8_t   encoded[4];
    size_t    length;
    uintmax_t decoded;
};

static void test_encode_byte(void **state);
static void test_encode_word(void **state);
static void test_encode_dword(void **state);
static void test_encode_qword(void **state);

static void test_decode_byte(void **state);
static void test_decode_word(void **state);
static void test_decode_dword(void **state);
static void test_decode_qword(void **state);

static void test_decode_bcd(void **state);

static const test_vector_16_t test_data_16[] =
{
    { { 0x00, 0x00 }, 0x0000U },
    { { 0xFF, 0xFF }, 0xFFFFU },
    { { 0x34, 0x12 }, 0x1234U }
};

static const test_vector_32_t test_data_32[] =
{
    { { 0x00, 0x00, 0x00, 0x00 }, 0x00000000U },
    { { 0xFF, 0xFF, 0xFF, 0xFF }, 0xFFFFFFFFU },
    { { 0x78, 0x56, 0x34, 0x12 }, 0x12345678U }
};

static const test_vector_64_t test_data_64[] =
{
    { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 0x0000000000000000UL },
    { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }, 0xFFFFFFFFFFFFFFFFUL },
    { { 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 }, 0x0123456789ABCDEFUL }
};

static const test_vector_bcd_t test_data_bcd[] =
{
    { { 0x00, 0x00, 0x00, 0x00 }, 1, 0        },
    { { 0x00, 0x00, 0x00, 0x00 }, 2, 0        },
    { { 0x00, 0x00, 0x00, 0x00 }, 3, 0        },
    { { 0x00, 0x00, 0x00, 0x00 }, 4, 0        },

    { { 0x01, 0x00, 0x00, 0x00 }, 1, 1        },
    { { 0x01, 0x00, 0x00, 0x00 }, 2, 1        },
    { { 0x01, 0x00, 0x00, 0x00 }, 3, 1        },
    { { 0x01, 0x00, 0x00, 0x00 }, 4, 1        },

    { { 0x12, 0x00, 0x00, 0x00 }, 1, 12       },
    { { 0x12, 0x00, 0x00, 0x00 }, 2, 12       },
    { { 0x12, 0x00, 0x00, 0x00 }, 3, 12       },
    { { 0x12, 0x00, 0x00, 0x00 }, 4, 12       },

    { { 0x23, 0x01, 0x00, 0x00 }, 1, 23       },
    { { 0x23, 0x01, 0x00, 0x00 }, 2, 123      },
    { { 0x23, 0x01, 0x00, 0x00 }, 3, 123      },
    { { 0x23, 0x01, 0x00, 0x00 }, 4, 123      },

    { { 0x34, 0x12, 0x00, 0x00 }, 1, 34       },
    { { 0x34, 0x12, 0x00, 0x00 }, 2, 1234     },
    { { 0x34, 0x12, 0x00, 0x00 }, 3, 1234     },
    { { 0x34, 0x12, 0x00, 0x00 }, 4, 1234     },

    { { 0x45, 0x23, 0x01, 0x00 }, 1, 45       },
    { { 0x45, 0x23, 0x01, 0x00 }, 2, 2345     },
    { { 0x45, 0x23, 0x01, 0x00 }, 3, 12345    },
    { { 0x45, 0x23, 0x01, 0x00 }, 4, 12345    },

    { { 0x56, 0x34, 0x12, 0x00 }, 1, 56       },
    { { 0x56, 0x34, 0x12, 0x00 }, 2, 3456     },
    { { 0x56, 0x34, 0x12, 0x00 }, 3, 123456   },
    { { 0x56, 0x34, 0x12, 0x00 }, 4, 123456   },

    { { 0x67, 0x45, 0x23, 0x01 }, 1, 67       },
    { { 0x67, 0x45, 0x23, 0x01 }, 2, 4567     },
    { { 0x67, 0x45, 0x23, 0x01 }, 3, 234567   },
    { { 0x67, 0x45, 0x23, 0x01 }, 4, 1234567  },

    { { 0x78, 0x56, 0x34, 0x12 }, 1, 78       },
    { { 0x78, 0x56, 0x34, 0x12 }, 2, 5678     },
    { { 0x78, 0x56, 0x34, 0x12 }, 3, 345678   },
    { { 0x78, 0x56, 0x34, 0x12 }, 4, 12345678 }
};

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_encode_byte),
        cmocka_unit_test(test_encode_word),
        cmocka_unit_test(test_encode_dword),
        cmocka_unit_test(test_encode_qword),

        cmocka_unit_test(test_decode_byte),
        cmocka_unit_test(test_decode_word),
        cmocka_unit_test(test_decode_dword),
        cmocka_unit_test(test_decode_qword),

        cmocka_unit_test(test_decode_bcd)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_encode_byte(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i <= UINT8_MAX; i++) {
        uint8_t    value  = dmi_cast(value, i);
        dmi_byte_t result = dmi_cast(result, i);

        assert_uint_equal(dmi_encode_byte(value), result);
        assert_uint_equal(dmi_encode(value), result);
    }
}

static void test_encode_word(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_16); i++) {
        uint16_t   value  = test_data_16[i].decoded;
        dmi_word_t result = *(dmi_word_t *)test_data_16[i].encoded;

        assert_uint_equal(dmi_encode_word(value), result);
        assert_uint_equal(dmi_encode(value), result);
    }
}

static void test_encode_dword(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_32); i++) {
        uint32_t    value  = test_data_32[i].decoded;
        dmi_dword_t result = *(dmi_dword_t *)test_data_32[i].encoded;

        assert_uint_equal(dmi_encode_dword(value), result);
        assert_uint_equal(dmi_encode(value), result);
    }
}

static void test_encode_qword(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_64); i++) {
        uint64_t    value  = test_data_64[i].decoded;
        dmi_qword_t result = *(dmi_qword_t *)test_data_64[i].encoded;

        assert_uint_equal(dmi_encode_qword(value), result);
        assert_uint_equal(dmi_encode(value), result);
    }
}

static void test_decode_byte(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i <= UINT8_MAX; i++) {
        dmi_byte_t value  = dmi_cast(value, i);
        uint8_t    result = dmi_cast(result, i);

        assert_uint_equal(dmi_decode_byte(value), result);
        assert_uint_equal(dmi_decode(value), result);
    }
}

static void test_decode_word(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_16); i++) {
        dmi_word_t value  = *(dmi_word_t *)test_data_16[i].encoded;
        uint16_t   result = test_data_16[i].decoded;

        assert_uint_equal(dmi_decode_word(value), result);
        assert_uint_equal(dmi_decode(value), result);
    }
}

static void test_decode_dword(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_32); i++) {
        dmi_dword_t value  = *(dmi_dword_t *)test_data_32[i].encoded;
        uint32_t    result = test_data_32[i].decoded;

        assert_uint_equal(dmi_decode_dword(value), result);
        assert_uint_equal(dmi_decode(value), result);
    }
}

static void test_decode_qword(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_64); i++) {
        dmi_qword_t value  = *(dmi_qword_t *)test_data_64[i].encoded;
        uint64_t    result = test_data_64[i].decoded;

        assert_uint_equal(dmi_decode_qword(value), result);
        assert_uint_equal(dmi_decode(value), result);
    }
}

static void test_decode_bcd(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_bcd); i++) {
        const uint8_t *value  = test_data_bcd[i].encoded;
        uint8_t        length = test_data_bcd[i].length;
        uintmax_t      result = test_data_bcd[i].decoded;

        assert_uint_equal(__dmi_decode_bcd(value, length), result);

        switch (length) {
        case sizeof(uint8_t):
            assert_uint_equal(dmi_decode_bcd(*(uint8_t *)value), result);
            break;

        case sizeof(uint16_t):
            assert_uint_equal(dmi_decode_bcd(*(uint16_t *)value), result);
            break;

        case sizeof(uint32_t):
            assert_uint_equal(dmi_decode_bcd(*(uint32_t *)value), result);
            break;

        case sizeof(uint64_t):
            assert_uint_equal(dmi_decode_bcd(*(uint64_t *)value), result);
            break;
        }
    }
}
