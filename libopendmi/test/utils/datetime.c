//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <stdbool.h>
#include <cmocka.h>

#include <opendmi/utils/datetime.h>

static void test_date_parse(void **state);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_date_parse)
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}

static void test_date_parse(void **state)
{
    dmi_unused(state);

    static const struct {
        const char *value;
        dmi_date_t expected;
    } test_data[] = {
        { "",            DMI_DATE_NONE          },
        { "01",          DMI_DATE_NONE          },
        { "01/01",       DMI_DATE_NONE          },
        { "01/01/00",    DMI_DATE(1900, 01, 01) },
        { "12/31/99",    DMI_DATE(1999, 12, 31) },
        { "00/01/00",    DMI_DATE_NONE          },
        { "13/01/00",    DMI_DATE_NONE          },
        { "01/00/00",    DMI_DATE_NONE          },
        { "01/32/00",    DMI_DATE_NONE          },
        { "01/01/00/01", DMI_DATE_NONE          },
        { "01/01/2000",  DMI_DATE(2000, 01, 01) },
        { "01/01/0000",  DMI_DATE(0000, 01, 01) },
        { "01/01/9999",  DMI_DATE(9999, 01, 01) },
        { "01/01/1",     DMI_DATE_NONE          },
        { "01/01/100",   DMI_DATE_NONE          },
        { "01/01/10000", DMI_DATE_NONE          },
        { "+01/01/00",   DMI_DATE_NONE          },
        { "01/+01/00",   DMI_DATE_NONE          },
        { "01/01/+00",   DMI_DATE_NONE          },
        { "-01/01/00",   DMI_DATE_NONE          },
        { "01/-01/00",   DMI_DATE_NONE          },
        { "01/01/-00",   DMI_DATE_NONE          }
    };

    for (size_t i = 0; i < countof(test_data); i++) {
        const char *value    = test_data[i].value;
        dmi_date_t  expected = test_data[i].expected;

        assert_uint_equal(dmi_date_parse(value), expected);
    }
}
