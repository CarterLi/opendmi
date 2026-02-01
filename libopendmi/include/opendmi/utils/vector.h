//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_UTILS_VECTOR_H
#define OPENDMI_UTILS_VECTOR_H

#pragma once

#include <opendmi/types.h>

typedef struct dmi_vector dmi_vector_t;

typedef bool dmi_vector_match_fn(uintptr_t entry, uintptr_t key);

struct dmi_vector
{
    uintptr_t *data;
    size_t capacity;
    size_t length;
    dmi_vector_match_fn *matcher;
};

__BEGIN_DECLS

bool dmi_vector_get(const dmi_vector_t *vector, size_t index, uintptr_t *value);
bool dmi_vector_exists(const dmi_vector_t *vector, uintptr_t key);
bool dmi_vector_push(dmi_vector_t *vector, uintptr_t value);
bool dmi_vector_pop(dmi_vector_t *vector, uintptr_t *value);
void dmi_vector_clear(dmi_vector_t *vector);

__END_DECLS

static inline size_t dmi_vector_length(const dmi_vector_t *vector)
{
    return vector->length;
}

static inline bool dmi_vector_is_empty(const dmi_vector_t *vector)
{
    return vector->length == 0;
}

#endif // !OPENDMI_UTILS_VECTOR_H
