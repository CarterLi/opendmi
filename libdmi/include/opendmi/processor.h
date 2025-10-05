//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_PROCESSOR_H
#define OPENDMI_PROCESSOR_H

#pragma once

#include <sys/cdefs.h>
#include <stdint.h>

enum dmi_processor_type
{
    DMI_PROCESSOR_TYPE_OTHER   = 0x01,
    DMI_PROCESSOR_TYPE_UNKNOWN = 0x02,
    DMI_PROCESSOR_TYPE_CENTRAL = 0x03,
    DMI_PROCESSOR_TYPE_MATH    = 0x04,
    DMI_PROCESSOR_TYPE_DSP     = 0x05,
    DMI_PROCESSOR_TYPE_VIDEO   = 0x06
};

enum dmi_processor_family
{
    DMI_PROCERROR_FAMILY_OTHER   = 0x01,
    DMI_PROCESSOR_FAMILY_UNKNOWN = 0x02,
    DMI_PROCESSOR_FAMILY_8086    = 0x03,
    DMI_PROCESSOR_FAMILY_80286   = 0x04,
    DMI_PROCESSOR_FAMILY_80386   = 0x05,
    DMI_PROCESSOR_FAMILY_80486   = 0x06,
    DMI_PROCESSOR_FAMILY_8087    = 0x07,
};

enum dmi_processor_upgrade
{
    DMI_PROCESSOR_UPGRADE_OTHER   = 0x01,
    DMI_PROCESSOR_UPGRADE_UNKNOWN = 0x02,
};

__BEGIN_DECLS

const char *dmi_processor_type_name(enum dmi_processor_type id);
const char *dmi_processor_family_name(enum dmi_processor_family id);

__END_DECLS

#endif // !OPENDMI_PROCESSOR_H
