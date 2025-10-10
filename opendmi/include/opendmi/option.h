//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_OPTION_H
#define OPENDMI_OPTION_H

#pragma once

#include <sys/cdefs.h>

#ifndef DMI_OPTION_T
#define DMI_OPTION_T
typedef struct dmi_option dmi_option_t;
#endif // !DMI_OPTION_T

struct dmi_option
{
    char short_name;
    char *long_name;
    char *description;
};

__BEGIN_DECLS

__END_DECLS

#endif // !OPENDMI_OPTION_H
