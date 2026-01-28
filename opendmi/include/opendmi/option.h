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
typedef struct dmi_option_set dmi_option_set_t;

/**
 * @brief Option handler function type.
 */
typedef bool dmi_option_handler_fn(dmi_context_t *context, const char *value);

typedef enum dmi_option_flag
{
    DMI_OPTION_FLAG_HIDDEN  = 0x01,
    DMI_OPTION_FLAG_REVERSE = 0x02
} dmi_option_flag_t;

/**
 * @brief Command line option descriptor.
 */
struct dmi_option
{
    const char *short_names;
    const char **long_names;
    const char *description;
    void *value;
    unsigned flags;
    dmi_option_handler_fn *handler;
    dmi_argument_t argument;
};

struct dmi_option_set
{
    const dmi_option_t *options;
};

#define dmi_options(...) ((const dmi_option_set_t *[]){ __VA_ARGS__, nullptr })

__BEGIN_DECLS

void dmi_option_list(const dmi_option_set_t *set);

const dmi_option_t *dmi_option_find_short(const dmi_option_set_t *set, char name);
const dmi_option_t *dmi_option_find_short_ex(const dmi_option_set_t **options, char name);
const dmi_option_t *dmi_option_find_long(const dmi_option_set_t *set, const char *name);
const dmi_option_t *dmi_option_find_long_ex(const dmi_option_set_t **options, const char *name);

int dmi_option_parse(
        dmi_context_t           *context,
        const dmi_option_set_t **options,
        int                      argc,
        char                    *argv[]);

__END_DECLS

#endif // !OPENDMI_OPTION_H
