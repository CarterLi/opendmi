//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/power-controls.h>

const dmi_attribute_t dmi_power_controls_attrs[] =
{
    DMI_ATTRIBUTE(dmi_power_controls_t, poweron_month, INTEGER, {
        .code = "poweron-month",
        .name = "Next power-on month"
    }),
    DMI_ATTRIBUTE(dmi_power_controls_t, poweron_day, INTEGER, {
        .code = "poweron-day",
        .name = "Next power-on day of month"
    }),
    DMI_ATTRIBUTE(dmi_power_controls_t, poweron_hour, INTEGER, {
        .code = "poweron-hour",
        .name = "Next power-on hour"
    }),
    DMI_ATTRIBUTE(dmi_power_controls_t, poweron_minute, INTEGER, {
        .code = "poweron-minute",
        .name = "Next power-on minute"
    }),
    DMI_ATTRIBUTE(dmi_power_controls_t, poweron_second, INTEGER, {
        .code = "poweron-second",
        .name = "Next power-on second"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_power_controls_table =
{
    .code        = "power-controls",
    .name        = "System power controls",
    .type        = DMI_TYPE_POWER_CONTROLS,
    .min_version = DMI_VERSION(2, 2, 0),
    .min_length  = 0x09,
    .attributes  = dmi_power_controls_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_power_controls_decode,
        .free   = (dmi_table_free_fn_t)dmi_power_controls_free
    }
};

dmi_power_controls_t *dmi_power_controls_decode(const dmi_table_t *table)
{
    dmi_power_controls_t *info;
    const dmi_power_controls_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_POWER_CONTROLS));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    info->poweron_month  = dmi_cast(info->poweron_month,
                                    dmi_decode_bcd(&data->poweron_month, sizeof(data->poweron_month)));
    info->poweron_day    = dmi_cast(info->poweron_day,
                                    dmi_decode_bcd(&data->poweron_day, sizeof(data->poweron_day)));
    info->poweron_hour   = dmi_cast(info->poweron_hour,
                                    dmi_decode_bcd(&data->poweron_hour, sizeof(data->poweron_hour)));
    info->poweron_minute = dmi_cast(info->poweron_minute,
                                    dmi_decode_bcd(&data->poweron_minute, sizeof(data->poweron_minute)));
    info->poweron_second = dmi_cast(info->poweron_second,
                                    dmi_decode_bcd(&data->poweron_second, sizeof(data->poweron_second)));

    return info;
}

void dmi_power_controls_free(dmi_power_controls_t *info)
{
    dmi_free(info);
}
