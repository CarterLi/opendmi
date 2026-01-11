//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_STREAM_H
#define OPENDMI_STREAM_H

#pragma once

#include <opendmi/utils/decode.h>

typedef struct dmi_stream dmi_stream_t;

struct dmi_stream
{
    const dmi_entity_t *entity;
    size_t position;
    size_t remaining;
};

__BEGIN_DECLS

bool dmi_stream_initialize(dmi_stream_t *stream, const dmi_entity_t *entity);
bool dmi_stream_seek(dmi_stream_t *stream, size_t position);
bool dmi_stream_read_data(dmi_stream_t *stream, void *ptr, size_t length);
bool dmi_stream_peek_data(dmi_stream_t *stream, void *ptr, size_t length);
void dmi_stream_reset(dmi_stream_t *stream);

__END_DECLS

#define dmi_stream_read(__stream, __pvalue) \
        dmi_stream_read_data((__stream), (__pvalue), sizeof(*(__pvalue)))
#define dmi_stream_peek(__stream, __pvalue) \
        dmi_stream_read_data((__stream), (__pvalue), sizeof(*(__pvalue)))

#define dmi_stream_decode(__stream, __type, __pvalue)                         \
        ({                                                                    \
            __type __value;                                                   \
            bool rv = dmi_stream_read(__stream, &__value);                    \
            if (rv)                                                           \
                *(__pvalue) = (typeof(*(__pvalue)))dmi_decode(__value);       \
            rv;                                                               \
        })

#define dmi_stream_decode_str(__stream, __pvalue)                             \
        ({                                                                    \
            dmi_string_t __value;                                             \
            bool rv = dmi_stream_read(__stream, &__value);                    \
            if (rv)                                                           \
                *(__pvalue) = dmi_entity_string((__stream)->entity, __value); \
            rv;                                                               \
        })

#endif // !OPENDMI_STREAM_H
