//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_EXTENSION_AMI_H
#define OPENDMI_EXTENSION_AMI_H

#pragma once

#include <opendmi/extension.h>

/**
 * @brief AMI structure type identifiers.
 */
typedef enum dmi_ami_type
{
    DMI_TYPE_AMI_221 = 221 ///< Type 221
} dmi_ami_type_t;

extern const dmi_extension_t dmi_ami_ext;

#endif // !OPENDMI_EXTENSION_AMI_H
