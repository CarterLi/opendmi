//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>

void dmi_set_error(dmi_context_t *context, dmi_error_t error)
{
    if (context != nullptr)
        context->last_error = error;
    else
        dmi_last_error = error;
}

dmi_error_t dmi_get_error(const dmi_context_t *context)
{
    if (context == nullptr)
        return dmi_last_error;

    return context->last_error;
}
