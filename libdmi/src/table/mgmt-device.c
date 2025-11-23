//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/mgmt-device.h>
#include <opendmi/name.h>

static const dmi_name_t dmi_mgmt_device_type_names[] =
{
    {
        .id   = DMI_MGMT_DEVICE_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_NATIONAL_LM75,
        .code = "national-lm75",
        .name = "National Semiconductor LM75"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_NATIONAL_LM78,
        .code = "national-lm78",
        .name = "National Semiconductor LM78"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_NATIONAL_LM79,
        .code = "national-lm79",
        .name = "National Semiconductor LM79"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_NATIONAL_LM80,
        .code = "national-lm80",
        .name = "National Semiconductor LM80"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_NATIONAL_LM81,
        .code = "national-lm81",
        .name = "National Semiconductor LM81"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_ANALOG_ADM9240,
        .code = "analog-adm9240",
        .name = "Analog Devices ADM9240"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_DALLAS_DS1780,
        .code = "dallas-ds1780",
        .name = "Dallas Semiconductor DS1780"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_MAXIM_1617,
        .code = "maxim-1617",
        .name = "Maxim 1617"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_GENESYS_GL518SM,
        .code = "genesys-gl518sm",
        .name = "Genesys GL518SM"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_WINBOND_W83781D,
        .code = "winbond-w83781d",
        .name = "Winbond W83781D"
    },
    {
        .id   = DMI_MGMT_DEVICE_TYPE_HOLTEK_HT82H791,
        .code = "holtek-ht82h791",
        .name = "Holtek HT82H791"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_mgmt_device_addr_type_names[] =
{
    {
        .id   = DMI_MGMT_DEVICE_ADDR_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_MGMT_DEVICE_ADDR_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_MGMT_DEVICE_ADDR_TYPE_PORT,
        .code = "port",
        .name = "I/O port"
    },
    {
        .id   = DMI_MGMT_DEVICE_ADDR_TYPE_MEMORY,
        .code = "memory",
        .name = "Memory"
    },
    {
        .id   = DMI_MGMT_DEVICE_ADDR_TYPE_SMBUS,
        .code = "smbus",
        .name = "SMBus"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_mgmt_device_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_mgmt_device_table =
{
    .tag         = "mgmt-device",
    .name        = "Management device",
    .type        = DMI_TYPE_MGMT_DEVICE,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x0B,
    .attributes  = dmi_mgmt_device_attrs
};

const char *dmi_mgmt_device_type_name(enum dmi_mgmt_device_type value)
{
    return dmi_name_lookup(dmi_mgmt_device_type_names, value);
}

const char *dmi_mgmt_device_addr_type_name(enum dmi_mgmt_device_addr_type value)
{
    return dmi_name_lookup(dmi_mgmt_device_addr_type_names, value);
}
