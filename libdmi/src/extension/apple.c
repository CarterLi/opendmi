//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/apple.h>

const dmi_extension_t dmi_apple_ext =
{
    .tag    = "apple",
    .name   = "Apple DMI extension",
    .tables = nullptr
};
