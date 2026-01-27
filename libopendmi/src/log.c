//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/log.h>
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/name.h>

static const dmi_name_set_t dmi_log_level_names =
{
    .code  = "log-levels",
    .names = (const dmi_name_t[]) {
        { .id = DMI_LOG_ERROR,   .code = "error",   .name = "ERROR"   },
        { .id = DMI_LOG_WARNING, .code = "warning", .name = "WARNING" },
        { .id = DMI_LOG_NOTICE,  .code = "notice",  .name = "NOTICE"  },
        { .id = DMI_LOG_INFO,    .code = "info",    .name = "INFO"    },
        { .id = DMI_LOG_DEBUG,   .code = "debug",   .name = "DEBUG"   },
        DMI_NAME_NULL
    }
};

void dmi_log(dmi_context_t *context, dmi_log_level_t level, const char *fmt, ...)
{
    va_list args;

    if ((context == nullptr) or (context->logger == nullptr))
        return;

    if (level > context->log_level)
        return;

    va_start(args, fmt);
    context->logger(context, level, fmt, args);
    va_end(args);
}

const char *dmi_log_level_name(dmi_log_level_t level)
{
    const char *name;

    name = dmi_name_lookup(&dmi_log_level_names, level);
    if (name == nullptr)
        return "UNKNOWN";

    return name;
}

dmi_log_level_t dmi_log_level_find(const char *code)
{
    dmi_log_level_t level;

    if (code == nullptr)
        return DMI_LOG_INVALID;

    level = dmi_code_lookup_rev(&dmi_log_level_names, code);
    if (level < 0)
        return DMI_LOG_INVALID;

    return level;
}
