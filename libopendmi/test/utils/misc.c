//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/utils.h>

typedef struct test_vector_32 test_vector_32_t;
typedef struct test_vector_64 test_vector_64_t;

struct test_vector_32
{
    uint32_t value;
    unsigned int factor;
    uint32_t result;
};

struct test_vector_64
{
    uint64_t value;
    unsigned int factor;
    uint64_t result;
};

static void test_ipow32(void **state);
static void test_ipow64(void **state);

static const test_vector_32_t test_data_32[] =
{
    { 1,  0, 1       },
    { 1,  1, 1       },
    { 1,  2, 1       },
    { 1,  3, 1       },
    { 1,  4, 1       },
    { 1,  5, 1       },
    { 1,  6, 1       },
    { 2,  0, 1       },
    { 2,  1, 2       },
    { 2,  2, 4       },
    { 2,  3, 8       },
    { 2,  4, 16      },
    { 2,  5, 32      },
    { 2,  6, 64      },
    { 3,  0, 1       },
    { 3,  1, 3       },
    { 3,  2, 9       },
    { 3,  3, 27      },
    { 3,  4, 81      },
    { 3,  5, 243     },
    { 3,  6, 729     },
    { 5,  0, 1       },
    { 5,  1, 5       },
    { 5,  2, 25      },
    { 5,  3, 125     },
    { 5,  4, 625     },
    { 5,  5, 3125    },
    { 5,  6, 15625   },
    { 10, 0, 1       },
    { 10, 1, 10      },
    { 10, 2, 100     },
    { 10, 3, 1000    },
    { 10, 4, 10000   },
    { 10, 5, 100000  },
    { 10, 6, 1000000 }
};

static const test_vector_64_t test_data_64[] =
{
    { 1,  0, 1       },
    { 1,  1, 1       },
    { 1,  2, 1       },
    { 1,  3, 1       },
    { 1,  4, 1       },
    { 1,  5, 1       },
    { 1,  6, 1       },
    { 2,  0, 1       },
    { 2,  1, 2       },
    { 2,  2, 4       },
    { 2,  3, 8       },
    { 2,  4, 16      },
    { 2,  5, 32      },
    { 2,  6, 64      },
    { 3,  0, 1       },
    { 3,  1, 3       },
    { 3,  2, 9       },
    { 3,  3, 27      },
    { 3,  4, 81      },
    { 3,  5, 243     },
    { 3,  6, 729     },
    { 5,  0, 1       },
    { 5,  1, 5       },
    { 5,  2, 25      },
    { 5,  3, 125     },
    { 5,  4, 625     },
    { 5,  5, 3125    },
    { 5,  6, 15625   },
    { 10, 0, 1       },
    { 10, 1, 10      },
    { 10, 2, 100     },
    { 10, 3, 1000    },
    { 10, 4, 10000   },
    { 10, 5, 100000  },
    { 10, 6, 1000000 }
};

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ipow32),
        cmocka_unit_test(test_ipow64)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_ipow32(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_32); i++) {
        uint32_t     value  = test_data_32[i].value;
        unsigned int factor = test_data_32[i].factor;
        uint32_t     result = test_data_32[i].result;

        assert_uint_equal(dmi_ipow32(value, factor), result);
    }
}

static void test_ipow64(void **state)
{
    dmi_unused(state);

    for (size_t i = 0; i < countof(test_data_64); i++) {
        uint32_t     value  = test_data_64[i].value;
        unsigned int factor = test_data_64[i].factor;
        uint32_t     result = test_data_64[i].result;

        assert_uint_equal(dmi_ipow64(value, factor), result);
    }
}
