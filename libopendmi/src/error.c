#include <opendmi/error.h>
//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdio.h>

#include <opendmi/context.h>
#include <opendmi/error.h>
#include <opendmi/utils.h>

static size_t dmi_error_slot_get(dmi_error_state_t *state);
static void dmi_error_slot_clear(dmi_error_state_t *state, size_t idx);

static const char *dmi_error_messages[__DMI_ERROR_COUNT] =
{
    [DMI_ERROR_NONE]                  = "Success",
    [DMI_ERROR_NULL_ARGUMENT]         = "Argument is NULL",
    [DMI_ERROR_INVALID_ARGUMENT]      = "Invalid argument",
    [DMI_ERROR_INVALID_STATE]         = "Invalid state",
    [DMI_ERROR_FILE_OPEN]             = "Unable to open file",
    [DMI_ERROR_FILE_STAT]             = "Unable to stat file",
    [DMI_ERROR_FILE_READ]             = "Unable to read file",
    [DMI_ERROR_FILE_WRITE]            = "Unable to write file",
    [DMI_ERROR_FILE_DUP]              = "Unable to clone file handle",
    [DMI_ERROR_FILE_MAP]              = "Unable to map file",
    [DMI_ERROR_UNKNOWN_EPS_ANCHOR]    = "Unknown entry point structure anchor",
    [DMI_ERROR_INVALID_EPS_LENGTH]    = "Invalid entry point structure length",
    [DMI_ERROR_INVALID_EPS_CHECKSUM]  = "Invalid entry point structure checksum",
    [DMI_ERROR_INVALID_ENTITY_ADDR]   = "Invalid structure address",
    [DMI_ERROR_INVALID_ENTITY_LENGTH] = "Invalid structure length",
    [DMI_ERROR_INVALID_ENTITY_TYPE]   = "Invalid structure type",
    [DMI_ERROR_ENTITY_DECODE]         = "Unable to decode structure",
    [DMI_ERROR_ENTITY_REGISTER]       = "Unable to register structure",
    [DMI_ERROR_ENTITY_LINK]           = "Unable to link structure",
    [DMI_ERROR_ENTITY_NOT_FOUND]      = "Structure not found",
    [DMI_ERROR_STRING_NOT_FOUND]      = "String not found",
    [DMI_ERROR_DUPLICATE_ENTRY]       = "Duplicate entry",
    [DMI_ERROR_DUPLICATE_HANDLE]      = "Duplicate handle",
    [DMI_ERROR_NO_MORE_ENTRIES]       = "No more entries",
    [DMI_ERROR_MISSING_FIRMWARE_INFO] = "No platform firmware information structure is present",
    [DMI_ERROR_EXTENSION_CONFICT]     = "Extensions has conflics",
    [DMI_ERROR_SERVICE_UNAVAILABLE]   = "Service unavailable",
    [DMI_ERROR_OUT_OF_MEMORY]         = "Out of memory",
    [DMI_ERROR_SYSTEM]                = "System error",
    [DMI_ERROR_INTERNAL]              = "Internal error"
};

static const dmi_error_t dmi_error_null =
{
    .file     = nullptr,
    .function = nullptr,
    .line     = 0,
    .reason   = DMI_ERROR_NONE,
    .message  = nullptr
};

const char *dmi_error_message(dmi_error_code_t reason)
{
    if ((reason < 0) or (reason >= __DMI_ERROR_COUNT) or (dmi_error_messages[reason] == nullptr))
        return "Unknown error";

    return dmi_error_messages[reason];
}

bool __dmi_error_raise(
        dmi_context_t    *context,
        const char       *file,
        const char       *function,
        unsigned int      line,
        dmi_error_code_t  reason,
        const char       *message,
        ...)
{
    va_list args;
    bool rv;

    va_start(args, message);
    rv = __dmi_error_vraise(context, file, function, line, reason, message, args);
    va_end(args);

    return rv;
}

bool __dmi_error_vraise(
        dmi_context_t    *context,
        const char       *file,
        const char       *function,
        unsigned int      line,
        dmi_error_code_t  reason,
        const char       *message,
        va_list           args)
{
    size_t slot;
    dmi_error_t *error;
    int rv = -1;

    if (context == nullptr)
        return false;

    slot = dmi_error_slot_get(&context->error_state);
    error = &context->error_state.errors[slot];

    error->file     = file;
    error->function = function;
    error->line     = line;
    error->reason   = reason;

    if (message != nullptr) {
        rv = vasprintf(&error->message, message, args);

        if ((rv < 0) or (error->message == nullptr)) {
            dmi_error_raise(context, DMI_ERROR_OUT_OF_MEMORY);
            return false;
        }
    }

    if (error->message != nullptr)
        dmi_log_error(context, "%s: %s", dmi_error_message(error->reason), error->message);
    else
        dmi_log_error(context, "%s", dmi_error_message(error->reason));

    return true;
}

dmi_error_t *dmi_error_peek(dmi_context_t *context)
{
    dmi_error_state_t *state;

    if (context == nullptr)
        return nullptr;

    state = &context->error_state;
    if (state->first == state->last)
        return nullptr;

    return &state->errors[state->first + 1];
}

dmi_error_t *dmi_error_peek_last(dmi_context_t *context)
{
    dmi_error_state_t *state;

    if (context == nullptr)
        return nullptr;

    state = &context->error_state;
    if (state->first == state->last)
        return nullptr;

    return &state->errors[state->last];
}

dmi_error_t *dmi_error_get(dmi_context_t *context)
{
    dmi_error_state_t *state;
    dmi_error_t *error;

    if (context == nullptr)
        return nullptr;

    state = &context->error_state;
    if (state->first == state->last)
        return nullptr;

    error = &state->errors[state->first + 1];
    state->first = (state->first + 1) % DMI_ERROR_MAX_DEPTH;

    return error;
}

dmi_error_t *dmi_error_get_last(dmi_context_t *context)
{
    dmi_error_state_t *state;
    dmi_error_t *error;

    if (context == nullptr)
        return nullptr;

    state = &context->error_state;
    if (state->first == state->last)
        return nullptr;

    error = &state->errors[state->last];

    if (state->last > 0)
        state->last--;
    else
        state->last = DMI_ERROR_MAX_DEPTH - 1;

    return error;
}

void dmi_error_clear(dmi_context_t *context)
{
    dmi_error_state_t *state;

    if (context == nullptr)
        return;

    state = &context->error_state;

    for (size_t i = 0; i < DMI_ERROR_MAX_DEPTH; i++) {
        dmi_error_slot_clear(state, i);
    }

    state->first = 0;
    state->last  = 0;
}

static size_t dmi_error_slot_get(dmi_error_state_t *state)
{
    state->last = (state->last + 1) % DMI_ERROR_MAX_DEPTH;

    if (state->last == state->first)
        state->first = (state->first + 1) % DMI_ERROR_MAX_DEPTH;

    dmi_error_slot_clear(state, state->last);

    return state->last;
}

static void dmi_error_slot_clear(dmi_error_state_t *state, size_t idx)
{
    dmi_free(state->errors[idx].message);
    state->errors[idx] = dmi_error_null;
}
