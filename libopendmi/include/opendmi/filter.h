//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FILTER_H
#define OPENDMI_FILTER_H

#pragma once

#include <opendmi/types.h>
#include <opendmi/utils/vector.h>

typedef struct dmi_filter dmi_filter_t;

typedef enum dmi_filter_mask : unsigned
{
    DMI_FILTER_MASK_COMMON   = 1 << 0,
    DMI_FILTER_MASK_OEM      = 1 << 1,
    DMI_FILTER_MASK_INACTIVE = 1 << 2,
    DMI_FILTER_MASK_UNKNOWN  = 1 << 3,
    DMI_FILTER_MASK_ALL      = ~0u
} dmi_filter_mask_t;

struct dmi_filter
{
    dmi_context_t *context;

    unsigned mask;
    dmi_vector_t handles;
    dmi_vector_t types;
};

__BEGIN_DECLS

dmi_filter_t *dmi_filter_create(dmi_context_t *context);

bool dmi_filter_add_handle(dmi_filter_t *filter, dmi_handle_t handle);
bool dmi_filter_add_type(dmi_filter_t *filter, dmi_type_t type);

bool dmi_filter_is_empty(const dmi_filter_t *filter);
bool dmi_filter_match(const dmi_filter_t *filter, const dmi_entity_t *entity);

void dmi_filter_destroy(dmi_filter_t *filter);

__END_DECLS

#endif // !OPENDMI_FILTER_H
