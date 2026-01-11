//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <memory.h>

#include <opendmi/entity.h>
#include <opendmi/stream.h>

bool dmi_stream_initialize(dmi_stream_t *stream, const dmi_entity_t *entity)
{
    if ((stream == nullptr) or (entity == nullptr))
        return false;

    stream->entity    = entity;
    stream->position  = 0;
    stream->remaining = entity->body_length;

    return true;
}

bool dmi_stream_seek(dmi_stream_t *stream, size_t position)
{
    if (stream == nullptr)
        return false;
    if (position >= stream->entity->body_length)
        return false;

    stream->position  = position;
    stream->remaining = stream->entity->body_length - position;

    return true;
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
    if ((stream == nullptr) or (ptr == nullptr))
        return false;
    if (stream->remaining < length)
        return false;

    memcpy(ptr, stream->entity->data + stream->position, length);

    return true;
}

void dmi_stream_reset(dmi_stream_t *stream)
{
    stream->position  = 0;
    stream->remaining = stream->entity->body_length;
}
