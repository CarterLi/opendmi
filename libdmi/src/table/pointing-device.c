//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/table/pointing-device.h>
#include <opendmi/name.h>

static bool dmi_pointing_device_decode(dmi_table_t *table);
static void dmi_pointing_device_free(dmi_table_t *table);

static const dmi_name_t dmi_pointing_device_type_names[] =
{
    {
        .id   = DMI_POINTING_DEVICE_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_MOUSE,
        .code = "mouse",
        .name = "Mouse"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_TRACK_BALL,
        .code = "track-ball",
        .name = "Track ball"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_TRACK_POINT,
        .code = "track-point",
        .name = "Track point"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_GLIDE_POINT,
        .code = "glide-point",
        .name = "Glide point"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_TOUCH_PAD,
        .code = "touch-pad",
        .name = "Touch pad"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_TOUCH_SCREEN,
        .code = "touch-screen",
        .name = "Touch screen"
    },
    {
        .id   = DMI_POINTING_DEVICE_TYPE_OPTICAL_SENSOR,
        .code = "optical-sensor",
        .name = "Optical sensor"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_pointing_device_interface_names[] =
{
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_SERIAL,
        .code = "serial",
        .name = "Serial"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_PS2,
        .code = "ps2",
        .name = "PS/2"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_INFRARED,
        .code = "infrared",
        .name = "Infrared"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_HP_HIL,
        .code = "hp-hil",
        .name = "HP-HIL"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_BUS_MOUSE,
        .code = "bus-mouse",
        .name = "Bus mouse"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_ADB,
        .code = "adb",
        .name = "ADB (Apple Desktop Bus)"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_BUS_MOUSE_DB9,
        .code = "bus-mouse-db9",
        .name = "Bus mouse DB-9"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_BUS_MOUSE_DIN,
        .code = "bus-mouse-din",
        .name = "Bus mouse micro-DIN"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_USB,
        .code = "usb",
        .name = "USB"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_I2C,
        .code = "i2c",
        .name = "I2C"
    },
    {
        .id   = DMI_POINTING_DEVICE_INTERFACE_SPI,
        .code = "spi",
        .name = "SPI"
    },
    DMI_NAME_NULL
};

const dmi_attribute_spec_t dmi_pointing_device_attrs[] =
{
    {
        .code   = "type",
        .name   = "Type",
        .offset = offsetof(dmi_pointing_device_t, type),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_pointing_device_type_names
    },
    {
        .code   = "interface",
        .name   = "Interface type",
        .offset = offsetof(dmi_pointing_device_t, interface),
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_pointing_device_interface_names
    },
    {
        .code   = "button-count",
        .name   = "Button count",
        .offset = offsetof(dmi_pointing_device_t, button_count),
        .type   = DMI_ATTRIBUTE_TYPE_INT
    },
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_pointing_device_table =
{
    .tag         = "pointing-device",
    .name        = "Built-in pointing device",
    .type        = DMI_TYPE_POINTING_DEVICE,
    .min_version = DMI_VERSION(2, 1, 0),
    .min_length  = 0x07,
    .decode      = dmi_pointing_device_decode,
    .free        = dmi_pointing_device_free,
    .attributes  = dmi_pointing_device_attrs
};

const char *dmi_pointing_device_type_name(dmi_pointing_device_type_t value)
{
    return dmi_name_lookup(dmi_pointing_device_type_names, value);
}

const char *dmi_pointing_device_interface_name(dmi_pointing_device_interface_t value)
{
    return dmi_name_lookup(dmi_pointing_device_interface_names, value);
}

static bool dmi_pointing_device_decode(dmi_table_t *table)
{
    dmi_pointing_device_t *info = nullptr;
    dmi_pointing_device_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return false;

    info->type         = data->type;
    info->interface    = data->interface;
    info->button_count = data->button_count;

    table->info = info;

    return true;
}

static void dmi_pointing_device_free(dmi_table_t *table)
{
    free(table->info);
}
