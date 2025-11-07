//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/onboard-device.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_onboard_device_type_names[] =
{
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_VIDEO,
        .code = "video",
        .name = "Video"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_SCSI_CONTROLLER,
        .code = "scsi-controller",
        .name = "SCSI controller"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_ETHERNET,
        .code = "ethernet",
        .name = "Ethernet"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_TOKEN_RING,
        .code = "token-ring",
        .name = "Token ring"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_SOUND,
        .code = "sound",
        .name = "Sound"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_PATA_CONTROLLER,
        .code = "pata-controller",
        .name = "PATA controller"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_SATA_CONTROLLER,
        .code = "sata-controller",
        .name = "SATA controller"
    },
    {
        .id   = DMI_ONBOARD_DEVICE_TYPE_SAS_CONTROLLER,
        .code = "sas-controller",
        .name = "SAS controller"
    },
    DMI_NAME_NULL
};

const dmi_attribute_spec_t dmi_onboard_device_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_onboard_device_table =
{
    .tag        = "onboard-device",
    .name       = "Onboard devices information",
    .type       = DMI_TYPE_ONBOARD_DEVICE,
    .min_length = 0x06,
    .attributes = dmi_onboard_device_attrs
};


const dmi_attribute_spec_t dmi_onboard_device_ex_attrs[] =
{
    { nullptr, nullptr, DMI_ATTRIBUTE_TYPE_NONE, nullptr, nullptr }
};

const dmi_table_spec_t dmi_onboard_device_ex_table =
{
    .tag         = "onboard-device-ex",
    .name        = "Onboard devices extended information",
    .type        = DMI_TYPE_ONBOARD_DEVICE_EX,
    .min_version = DMI_VERSION(2, 6, 0),
    .min_length  = 0x0B,
    .attributes  = dmi_onboard_device_ex_attrs
};

const char *dmi_onboard_device_type_name(enum dmi_onboard_device_type value)
{
    return dmi_name_lookup(dmi_onboard_device_type_names, value);
}
