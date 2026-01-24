//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_OPTION_H
#define OPENDMI_OPTION_H

#pragma once

#include <opendmi/argument.h>

typedef struct dmi_option dmi_option_t;
typedef struct dmi_option_group dmi_option_group_t;

typedef enum dmi_option_flag
{
    DMI_OPTION_FLAG_HIDDEN       = 0x01,
    DMI_OPTION_FLAG_REVERSE      = 0x02,
    DMI_OPTION_FLAG_OPTIONAL_ARG = 0x04
} dmi_option_flag_t;

/**
 * @brief Command line option descriptor.
 */
struct dmi_option
{
    const char *short_names;
    const char **long_names;
    const char *description;
    dmi_argument_t argument;
    unsigned flags;
    void *value;
};

struct dmi_option_group
{
    const char *name;
    const dmi_option_t *options;
};

__BEGIN_DECLS

void dmi_option_list(const dmi_option_group_t *group);

const dmi_option_t *dmi_option_find_short(const dmi_option_group_t *group, char name);
const dmi_option_t *dmi_option_find_long(const dmi_option_group_t *group, const char *name);

int dmi_option_parse(const dmi_option_group_t *group, int argc, char *argv[]);

__END_DECLS

#endif // !OPENDMI_OPTION_H
