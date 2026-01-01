//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_LOG_H
#define OPENDMI_LOG_H

#pragma once

#include <stdarg.h>
#include <opendmi/types.h>

/**
 * @brief Logging levels.
 */
typedef enum dmi_log_level
{
    DMI_LOG_ERROR,   ///< Error
    DMI_LOG_WARNING, ///< Warning
    DMI_LOG_NOTICE,  ///< Notice
    DMI_LOG_INFO,    ///< Info
    DMI_LOG_DEBUG,   ///< Debug
    __DMI_LOG_LEVEL_COUNT
} dmi_log_level_t;

typedef void (*dmi_log_handler_t)(dmi_context_t *context, dmi_log_level_t level, const char *fmt, va_list args);

__BEGIN_DECLS

void dmi_log(dmi_context_t *context, dmi_log_level_t level, const char *fmt, ...);

const char *dmi_log_level_name(dmi_log_level_t value);

__END_DECLS

#define dmi_log_error(context, fmt, ...)   dmi_log(context, DMI_LOG_ERROR, fmt, ##__VA_ARGS__)
#define dmi_log_warning(context, fmt, ...) dmi_log(context, DMI_LOG_WARNING, fmt, ##__VA_ARGS__)
#define dmi_log_notice(context, fmt, ...)  dmi_log(context, DMI_LOG_NOTICE, fmt, ##__VA_ARGS__)
#define dmi_log_info(context, fmt, ...)    dmi_log(context, DMI_LOG_INFO, fmt, ##__VA_ARGS__)
#define dmi_log_debug(context, fmt, ...)   dmi_log(context, DMI_LOG_DEBUG, fmt, ##__VA_ARGS__)

#endif // !OPENDMI_LOG_H
