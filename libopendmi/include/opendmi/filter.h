//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FILTER_H
#define OPENDMI_FILTER_H

#pragma once

#include <opendmi/types.h>

#ifndef DMI_FILTER_T
#define DMI_FILTER_T
typedef struct dmi_filter dmi_filter_t;
#endif // !DMI_FILTER_T

struct dmi_filter
{
    dmi_context_t *context;
    dmi_handle_t *handles;
    dmi_type_t *types;
};

__BEGIN_DECLS

dmi_filter_t *dmi_filter_create(dmi_context_t *context);

bool dmi_filter_add_handle(dmi_filter_t *filter, dmi_handle_t handle);
bool dmi_filter_add_type(dmi_filter_t *filter, dmi_type_t type);

void dmi_filter_destroy(dmi_filter_t *filter);

__END_DECLS

#endif // !OPENDMI_FILTER_H
