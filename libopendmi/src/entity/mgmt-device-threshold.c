//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <limits.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/mgmt-device-threshold.h>

static bool dmi_mgmt_device_threshold_decode(dmi_entity_t *entity);

const dmi_entity_spec_t dmi_mgmt_device_threshold_spec =
{
    .code            = "mgmt-device-threshold",
    .name            = "Management device threshold data",
    .type            = DMI_TYPE_MGMT_DEVICE_THRESHOLD,
    .minimum_version = DMI_VERSION(2, 3, 0),
    .minimum_length  = 0x10,
    .decoded_length  = sizeof(dmi_mgmt_device_threshold_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, lower_non_critical, INTEGER, {
            .code    = "lower-non-critical",
            .name    = "Lower non-critical",
            .unknown = dmi_value_ptr((short)SHRT_MIN)
        }),
        DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, upper_non_critical, INTEGER, {
            .code    = "upper-non-critical",
            .name    = "Upper non-critical",
            .unknown = dmi_value_ptr((short)SHRT_MIN)
        }),
        DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, lower_critical, INTEGER, {
            .code    = "lower-critical",
            .name    = "Lower critical",
            .unknown = dmi_value_ptr((short)SHRT_MIN)
        }),
        DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, upper_critical, INTEGER, {
            .code    = "upper-critical",
            .name    = "Upper critical",
            .unknown = dmi_value_ptr((short)SHRT_MIN)
        }),
        DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, lower_non_recoverable, INTEGER, {
            .code    = "lower-non-recoverable",
            .name    = "Lower non-recoverable",
            .unknown = dmi_value_ptr((short)SHRT_MIN)
        }),
        DMI_ATTRIBUTE(dmi_mgmt_device_threshold_t, upper_non_recoverable, INTEGER, {
            .code    = "upper-non-recoverable",
            .name    = "Upper non-recoverable",
            .unknown = dmi_value_ptr((short)SHRT_MIN)
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers = {
        .decode = dmi_mgmt_device_threshold_decode
    }
};

static bool dmi_mgmt_device_threshold_decode(dmi_entity_t *entity)
{
    dmi_mgmt_device_threshold_t *info;
    const dmi_mgmt_device_threshold_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_MGMT_DEVICE_THRESHOLD);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_MGMT_DEVICE_THRESHOLD);
    if (info == nullptr)
        return false;

    info->lower_non_critical    = dmi_decode(data->lower_non_critical);
    info->upper_non_critical    = dmi_decode(data->upper_non_critical);
    info->lower_critical        = dmi_decode(data->lower_critical);
    info->upper_critical        = dmi_decode(data->upper_critical);
    info->lower_non_recoverable = dmi_decode(data->lower_non_recoverable);
    info->upper_non_recoverable = dmi_decode(data->upper_non_recoverable);

    return true;
}
