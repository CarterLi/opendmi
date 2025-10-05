//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/processor.h>
#include <opendmi/utils.h>

static const char *dmi_processor_type_names[__DMI_PROCESSOR_TYPE_COUNT] =
{
    [DMI_PROCESSOR_TYPE_OTHER]   = "Other",
    [DMI_PROCESSOR_TYPE_UNKNOWN] = "Unknown",
    [DMI_PROCESSOR_TYPE_CENTRAL] = "Central processor",
    [DMI_PROCESSOR_TYPE_MATH]    = "Math processor",
    [DMI_PROCESSOR_TYPE_DSP]     = "DSP processor",
    [DMI_PROCESSOR_TYPE_VIDEO]   = "Video processor"
};

const char *dmi_processor_type_name(enum dmi_processor_type value)
{
    return dmi_name(dmi_processor_type_names, value, __DMI_PROCESSOR_TYPE_COUNT);
}
