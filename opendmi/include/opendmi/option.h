//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_OPTION_H
#define OPENDMI_OPTION_H

#pragma once

#include <opendmi/defs.h>

typedef struct dmi_option dmi_option_t;

struct dmi_option
{
    char short_name;
    char *long_name;
    char *description;
};

__BEGIN_DECLS

__END_DECLS

#endif // !OPENDMI_OPTION_H
