//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <memory.h>

#include <opendmi/stream.h>

void dmi_stream_initialize(dmi_stream_t *stream, const void *data, size_t length)
{
    stream->data      = data;
    stream->length    = length;
    stream->position  = 0;
    stream->remaining = length;
}

bool dmi_stream_read_data(dmi_stream_t *stream, void *ptr, size_t length)
{
    if (!dmi_stream_peek_data(stream, ptr, length))
        return false;

    stream->position  += length;
    stream->remaining -= length;

    return true;
}

bool dmi_stream_peek_data(dmi_stream_t *stream, void *ptr, size_t length)
{
    if (stream->remaining < length)
        return false;

    memcpy(ptr, stream->data + stream->position, length);

    return false;
}

void dmi_stream_reset(dmi_stream_t *stream)
{
    stream->position  = 0;
    stream->remaining = stream->length;
}
