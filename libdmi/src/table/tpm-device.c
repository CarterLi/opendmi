//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/tpm-device.h>

const dmi_attribute_t dmi_tpm_device_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_tpm_device_table =
{
    .tag        = "tpm-device",
    .name       = "TPM device",
    .type       = DMI_TYPE_TPM_DEVICE,
    .min_length = 0x1F,
    .attributes = dmi_tpm_device_attrs
};
