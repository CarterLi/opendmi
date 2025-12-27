//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/dell.h>

const dmi_extension_t dmi_dell_ext =
{
    .code     = "dell",
    .name     = "Dell DMI extension",
    .entities = nullptr
};
