//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>

#include <opendmi/table/chassis.h>

static const dmi_name_t dmi_chassis_type_names[] =
{
    {
        .id   = DMI_CHASSIS_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_CHASSIS_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_CHASSIS_TYPE_DESKTOP,
        .code = "desktop",
        .name = "Desktop"
    },
    {
        .id   = DMI_CHASSIS_TYPE_LOW_PROFILE_DESKTOP,
        .code = "low-profile-desktop",
        .name = "Low-profile desktop"
    },
    {
        .id   = DMI_CHASSIS_TYPE_PIZZA_BOX,
        .code = "pizza-box",
        .name = "Pizza box"
    },
    {
        .id   = DMI_CHASSIS_TYPE_MINI_TOWER,
        .code = "mini-tower",
        .name = "Mini tower"
    },
    {
        .id   = DMI_CHASSIS_TYPE_TOWER,
        .code = "tower",
        .name = "Tower"
    },
    {
        .id   = DMI_CHASSIS_TYPE_PORTABLE,
        .code = "portable",
        .name = "Portable"
    },
    {
        .id   = DMI_CHASSIS_TYPE_LAPTOP,
        .code = "laptop",
        .name = "Laptop"
    },
    {
        .id   = DMI_CHASSIS_TYPE_NOTEBOOK,
        .code = "notebook",
        .name = "Notebook"
    },
    {
        .id   = DMI_CHASSIS_TYPE_HAND_HELD,
        .code = "hand-held",
        .name = "Hand held"
    },
    {
        .id   = DMI_CHASSIS_TYPE_DOCKING_STATION,
        .code = "docking-station",
        .name = "Docking station"
    },
    {
        .id   = DMI_CHASSIS_TYPE_ALL_IN_ONE,
        .code = "all-in-one",
        .name = "All-in-one"
    },
    {
        .id   = DMI_CHASSIS_TYPE_SUB_NOTEBOOK,
        .code = "sub-notebook",
        .name = "Sub-notebook"
    },
    {
        .id   = DMI_CHASSIS_TYPE_SPACE_SAVING,
        .code = "space-saving",
        .name = "Space-saving"
    },
    {
        .id   = DMI_CHASSIS_TYPE_LUNCH_BOX,
        .code = "lunch-box",
        .name = "Lunch box"
    },
    {
        .id   = DMI_CHASSIS_TYPE_MAIN_SERVER,
        .code = "main-server",
        .name = "Main server chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_EXPANSION,
        .code = "expansion",
        .name = "Expansion chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_SUB_CHASSIS,
        .code = "sub-chassis",
        .name = "Sub-chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_BUS_EXPANSION,
        .code = "bus-expansion",
        .name = "Bus expansion chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_PERIPHERAL,
        .code = "peripheral",
        .name = "Peripheral chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_RAID,
        .code = "raid",
        .name = "RAID chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_RACK_MOUNT,
        .code = "rack-mount",
        .name = "Rack-mount chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_SEALED_CASE_PC,
        .code = "sealed-case-pc",
        .name = "Sealed-case PC"
    },
    {
        .id   = DMI_CHASSIS_TYPE_MULTI_SYSTEM,
        .code = "multy-system",
        .name = "Multi-system chassis"
    },
    {
        .id   = DMI_CHASSIS_TYPE_COMPACT_PCI,
        .code = "compact-pci",
        .name = "Compact PCI"
    },
    {
        .id   = DMI_CHASSIS_TYPE_ADVANCED_TCA,
        .code = "advanced-tca",
        .name = "Advanced TCA"
    },
    {
        .id   = DMI_CHASSIS_TYPE_BLADE,
        .code = "blade",
        .name = "Blade"
    },
    {
        .id   = DMI_CHASSIS_TYPE_BLADE_ENCLOSURE,
        .code = "blade-enclosure",
        .name = "Blade enclosure"
    },
    {
        .id   = DMI_CHASSIS_TYPE_TABLET,
        .code = "tablet",
        .name = "Tablet"
    },
    {
        .id   = DMI_CHASSIS_TYPE_CONVERTIBLE,
        .code = "convertible",
        .name = "Convertible"
    },
    {
        .id   = DMI_CHASSIS_TYPE_DETACHABLE,
        .code = "detachable",
        .name = "Detachable"
    },
    {
        .id   = DMI_CHASSIS_TYPE_IOT_GATEWAY,
        .code = "iot-gateway",
        .name = "IoT gateway"
    },
    {
        .id   = DMI_CHASSIS_TYPE_EMBEDDED_PC,
        .code = "embedded-pc",
        .name = "Embedded PC"
    },
    {
        .id   = DMI_CHASSIS_TYPE_MINI_PC,
        .code = "mini-pc",
        .name = "Mini PC"
    },
    {
        .id   = DMI_CHASSIS_TYPE_STICK_PC,
        .code = "stick-pc",
        .name = "Stick PC"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_chassis_security_status_names[] =
{
    {
        .id   = DMI_CHASSIS_SECURITY_STATUS_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_CHASSIS_SECURITY_STATUS_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_CHASSIS_SECURITY_STATUS_NONE,
        .code = "none",
        .name = "None"
    },
    {
        .id   = DMI_CHASSIS_SECURITY_STATUS_EXT_IF_LOCKED,
        .code = "ext-if-locked",
        .name = "External interface locked"
    },
    {
        .id   = DMI_CHASSIS_SECURITY_STATUS_EXT_IF_ENABLED,
        .code = "ext-if-enabled",
        .name = "External interface enabled"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_chassis_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_chassis_table =
{
    .code          = "chassis",
    .name          = "System enclosure or chassis",
    .type          = DMI_TYPE_CHASSIS,
    .required_from = DMI_VERSION(2, 3, 0),
    .required_till = DMI_VERSION_NONE,
    .unique        = false,
    .min_length    = 0x09,
    .attributes    = dmi_chassis_attrs
};

const char *dmi_chassis_type_name(dmi_chassis_type_t value)
{
    return dmi_name_lookup(dmi_chassis_type_names, value);
}

const char *dmi_chassis_security_status_name(dmi_chassis_security_status_t value)
{
     return dmi_name_lookup(dmi_chassis_security_status_names, value);
}

dmi_chassis_t *dmi_chassis_decode(const dmi_table_t *table)
{
    dmi_chassis_t *info;
    const dmi_chassis_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_CHASSIS));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    return info;
}

void dmi_chassis_free(dmi_chassis_t *info)
{
    dmi_free(info);
}
