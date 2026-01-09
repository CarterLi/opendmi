//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_COMMAND_H
#define OPENDMI_COMMAND_H

#pragma once

#include <opendmi/option.h>

typedef struct dmi_command dmi_command_t;

struct dmi_command
{
    const char *name;
    const dmi_option_t *options;
    const dmi_argument_t *arguments;
};

__BEGIN_DECLS

__END_DECLS

#endif // !OPENDMI_COMMAND_H
