//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/extension/dell.h>
#include <opendmi/entity/dell/indexed-io.h>

const dmi_entity_spec_t dmi_dell_indexed_io_spec =
{
    .type = DMI_TYPE_DELL_INDEXED_IO,
    .code = "dell-indexed-io",
    .name = "Dell: Indexed IO"
};
