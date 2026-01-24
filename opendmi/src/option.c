//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdio.h>
#include <assert.h>

#include <opendmi/option.h>

void dmi_option_list(const dmi_option_group_t *group)
{
    const dmi_option_t *opt;
    const dmi_argument_t *arg;

    assert(group != nullptr);

    printf("%s:\n", group->name);

    for (opt = group->options; opt->short_names || opt->long_names; opt++) {
        arg = &opt->argument;

        if (opt->flags & DMI_OPTION_FLAG_HIDDEN)
            continue;

        int count = 0;

        if (opt->short_names != nullptr) {
            const char *name = opt->short_names;

            while (*name != 0) {
                printf("%s-%c", count > 0 ? ", " : "    ", *name);
                name++, count++;
            }
        }

        if (opt->long_names != nullptr) {
            const char **name = opt->long_names;

            while (*name != nullptr) {
                printf("%s--%s", count > 0 ? ", " : "    ", *name);
                name++, count++;
            }
        }

        if (arg->type != DMI_ARGUMENT_TYPE_NONE) {
            printf(arg->required ? " <%s>" : " [%s]", arg->name);
        }

        printf("\n%8s%s\n", "", opt->description);
    }

    printf("\n");
}
