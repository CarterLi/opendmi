//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ERROR_H
#define OPENDMI_ERROR_H

#pragma once

#include <opendmi/types.h>

#define DMI_ERROR_MAX_DEPTH 32

typedef struct dmi_error       dmi_error_t;
typedef struct dmi_error_state dmi_error_state_t;

/**
 * @brief DMI error codes
 */
typedef enum dmi_error_code
{
    DMI_ERROR_NONE,                  ///< Success
    DMI_ERROR_NULL_ARGUMENT,         ///< Argument is NULL
    DMI_ERROR_INVALID_ARGUMENT,      ///< Invalid argument
    DMI_ERROR_INVALID_STATE,         ///< Invalid state
    DMI_ERROR_FILE_OPEN,             ///< Unable to open file
    DMI_ERROR_FILE_STAT,             ///< Unable to stat file
    DMI_ERROR_FILE_READ,             ///< Unable to read file
    DMI_ERROR_FILE_WRITE,            ///< Unable to write file
    DMI_ERROR_FILE_MAP,              ///< Unable to map file
    DMI_ERROR_UNKNOWN_EPS_ANCHOR,    ///< Unknown entry point structure anchor
    DMI_ERROR_INVALID_EPS_LENGTH,    ///< Invalid entry point structure length
    DMI_ERROR_INVALID_EPS_CHECKSUM,  ///< Invalid entry point structure checksum
    DMI_ERROR_INVALID_ENTITY_ADDR,   ///< Invalid structure address
    DMI_ERROR_INVALID_ENTITY_LENGTH, ///< Invalid structure length
    DMI_ERROR_INVALID_ENTITY_TYPE,   ///< Invalid structure type
    DMI_ERROR_ENTITY_DECODE,         ///< Unable to decode structure
    DMI_ERROR_ENTITY_REGISTER,       ///< Unable to register structure
    DMI_ERROR_ENTITY_LINK,           ///< Unable to link structure
    DMI_ERROR_ENTITY_NOT_FOUND,      ///< Structure not found
    DMI_ERROR_STRING_NOT_FOUND,      ///< String not found
    DMI_ERROR_DUPLICATE_ENTRY,       ///< Duplicate entry
    DMI_ERROR_DUPLICATE_HANDLE,      ///< Duplicate handle
    DMI_ERROR_NO_MORE_ENTRIES,       ///< No more entries
    DMI_ERROR_OUT_OF_MEMORY,         ///< Out of memory
    DMI_ERROR_SERVICE_UNAVAILABLE,   ///< Service unavailable
    DMI_ERROR_SYSTEM,                ///< System error
    DMI_ERROR_INTERNAL,              ///< Internal error
    __DMI_ERROR_COUNT
} dmi_error_code_t;

/**
 * @brief Error descriptor.
 */
struct dmi_error
{
    /**
     * @brief Path to source file.
     */
    const char *file;

    /**
     * @brief Function name.
     */
    const char *function;

    /**
     * @brief Line number.
     */
    int line;

    /**
     * @brief Error reason code.
     */
    dmi_error_code_t reason;

    /**
     * @brief Additional error message (optional).
     */
    char *message;
};

struct dmi_error_state
{
    dmi_error_t errors[DMI_ERROR_MAX_DEPTH];
    size_t first;
    size_t last;
};

#define dmi_error_raise(context, reason) \
        __dmi_error_raise(context, __FILE__, __func__, __LINE__, reason, nullptr)
#define dmi_error_raise_ex(context, reason, message, ...) \
        __dmi_error_raise(context, __FILE__, __func__, __LINE__, reason, message, ##__VA_ARGS__)

__BEGIN_DECLS

/**
 * @brief Returns the error message for specified reason code.
 */
const char *dmi_error_message(dmi_error_code_t reason);

/**
 * @internal
 */
bool __dmi_error_raise(
        dmi_context_t    *context,
        const char       *file,
        const char       *function,
        unsigned int      line,
        dmi_error_code_t  reason,
        const char       *message,
        ...);

/**
 * @internal
 */
bool __dmi_error_vraise(
        dmi_context_t    *context,
        const char       *file,
        const char       *function,
        unsigned int      line,
        dmi_error_code_t  reason,
        const char       *message,
        va_list           args);

/**
 * @brief This function returns the earliest error code from the error stack.
 */
dmi_error_t *dmi_error_peek(dmi_context_t *context);

/**
 * @brief This function returns the latest error code from the error stack.
 */
dmi_error_t *dmi_error_peek_last(dmi_context_t *context);

/**
 * @brief This function returns the earliest error code from the error stack
 * and removes the entry. It can be called repeatedly until there are no more
 * error codes to return.
 *
 * @note
 * The returned value is only valid until next call of `dmi_error_get()`,
 * `dmi_error_get_last()` or `dmi_error_raise()`.
 */
dmi_error_t *dmi_error_get(dmi_context_t *context);

/**
 * @brief This function returns the latest error code from the error stack
 * and removes the entry. It can be called repeatedly until there are no more
 * error codes to return.
 *
 * @note
 * The returned value is only valid until next call of `dmi_error_get()`,
 * `dmi_error_get_last()` or `dmi_error_raise()`.
 */
dmi_error_t *dmi_error_get_last(dmi_context_t *context);

void dmi_error_clear(dmi_context_t *context);

__END_DECLS

#endif // !OPENDMI_ERROR_H
