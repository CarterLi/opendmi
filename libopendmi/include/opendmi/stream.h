//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_STREAM_H
#define OPENDMI_STREAM_H

#pragma once

#include <opendmi/types.h>

typedef struct dmi_stream dmi_stream_t;

struct dmi_stream
{
    const dmi_data_t *data;
    size_t length;
    size_t position;
    size_t remaining;
};

__BEGIN_DECLS

void dmi_stream_initialize(dmi_stream_t *stream, const void *data, size_t length);
bool dmi_stream_read_data(dmi_stream_t *stream, void *ptr, size_t length);
bool dmi_stream_peek_data(dmi_stream_t *stream, void *ptr, size_t length);
void dmi_stream_reset(dmi_stream_t *stream);

__END_DECLS

#define dmi_stream_read(stream, pvalue) \
        dmi_stream_read_data((stream), (pvalue), sizeof(*(pvalue)))
#define dmi_stream_peek(stream, pvalue) \
        dmi_stream_read_data((stream), (pvalue), sizeof(*(pvalue)))

#endif // !OPENDMI_STREAM_H
