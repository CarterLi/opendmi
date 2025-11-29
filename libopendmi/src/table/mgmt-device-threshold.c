//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <limits.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

#include <opendmi/table/mgmt-device-threshold.h>

const dmi_attribute_t dmi_mgmt_device_threshold_attrs[] =
{
    DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, lower_non_critical, INTEGER, {
        .code    = "lower-non-critical",
        .name    = "Lower non-critical",
        .unknown = &(short){ SHRT_MIN }
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, upper_non_critical, INTEGER, {
        .code    = "upper-non-critical",
        .name    = "Upper non-critical",
        .unknown = &(short){ SHRT_MIN }
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, lower_critical, INTEGER, {
        .code    = "lower-critical",
        .name    = "Lower critical",
        .unknown = &(short){ SHRT_MIN }
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, upper_critical, INTEGER, {
        .code    = "upper-critical",
        .name    = "Upper critical",
        .unknown = &(short){ SHRT_MIN }
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, lower_non_recoverable, INTEGER, {
        .code    = "lower-non-recoverable",
        .name    = "Lower non-recoverable",
        .unknown = &(short){ SHRT_MIN }
    }),
    DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, upper_non_recoverable, INTEGER, {
        .code    = "upper-non-recoverable",
        .name    = "Upper non-recoverable",
        .unknown = &(short){ SHRT_MIN }
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_mgmt_device_threshold_table =
{
    .code        = "mgmt-device-threshold",
    .name        = "Management device threshold data",
    .type        = DMI_TYPE_MGMT_DEVICE_THRESHOLD,
    .min_version = DMI_VERSION(2, 3, 0),
    .min_length  = 0x10,
    .attributes  = dmi_mgmt_device_threshold_attrs,
    .handlers    = {
        .decode = (dmi_table_decode_fn_t)dmi_mgmt_device_threshold_decode,
        .free   = (dmi_table_free_fn_t)dmi_mgmt_device_threshold_free
    }
};

dmi_mgmt_device_threshold_t *dmi_mgmt_device_threshold_decode(const dmi_table_t *table)
{
    dmi_mgmt_device_threshold_t *info;
    dmi_mgmt_device_threshold_data_t *data;

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_MGMT_DEVICE_THRESHOLD) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    info->lower_non_critical    = dmi_value(data->lower_non_critical);
    info->upper_non_critical    = dmi_value(data->upper_non_critical);
    info->lower_critical        = dmi_value(data->lower_critical);
    info->upper_critical        = dmi_value(data->upper_critical);
    info->lower_non_recoverable = dmi_value(data->lower_non_recoverable);
    info->upper_non_recoverable = dmi_value(data->upper_non_recoverable);

    return info;
}

void dmi_mgmt_device_threshold_free(dmi_mgmt_device_threshold_t *info)
{
    free(info);
}
