//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/log.h>
#include <opendmi/context.h>
#include <opendmi/utils.h>

static const char *dmi_log_level_names[__DMI_LOG_LEVEL_COUNT] =
{
    [DMI_LOG_ERROR]   = "ERROR",
    [DMI_LOG_WARNING] = "WARNING",
    [DMI_LOG_NOTICE]  = "NOTICE",
    [DMI_LOG_INFO]    = "INFO",
    [DMI_LOG_DEBUG]   = "DEBUG"
};

void dmi_log(dmi_context_t *context, dmi_log_level_t level, const char *fmt, ...)
{
    va_list args;

    if ((context == nullptr) || (context->logger == nullptr))
        return;

    va_start(args, fmt);
    context->logger(context, level, fmt, args);
    va_end(args);
}

const char *dmi_log_level_name(dmi_log_level_t value)
{
    return dmi_name(dmi_log_level_names, value, __DMI_LOG_LEVEL_COUNT);
}
