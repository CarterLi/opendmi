//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>

#include <opendmi/table/tpm-device.h>

static const dmi_name_t dmi_tpm_device_feature_names[] =
{
    {
        .id   = 2,
        .code = "is-unsupported",
        .name = "Characteristics are not supported"
    },
    {
        .id   = 3,
        .code = "is-update-configurable",
        .name = "Configurable via firmware update"
    },
    {
        .id   = 4,
        .code = "is-software-configurable",
        .name = "Configurable via platform software support"
    },
    {
        .id = 5,
        .code = "is-proprietary-configurable",
        .name = "Configurable via OEM proprietary mechanism"
    },
    DMI_NAME_NULL
};

static const dmi_attribute_t dmi_tpm_device_attrs[] =
{
    DMI_ATTRIBUTE(dmi_tpm_device_t, spec_version, VERSION, {
        .code   = "specification-version",
        .name   = "Specification version",
        .scale  = 2
    }),
    DMI_ATTRIBUTE(dmi_tpm_device_t, firmware_version, INTEGER, {
        .code   = "firmware-version",
        .name   = "Firmware version",
        .flags  = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_tpm_device_t, description, STRING, {
        .code   = "description",
        .name   = "Description"
    }),
    DMI_ATTRIBUTE(dmi_tpm_device_t, features, SET, {
        .code   = "characteristics",
        .name   = "Characteristics",
        .values = dmi_tpm_device_feature_names
    }),
    DMI_ATTRIBUTE(dmi_tpm_device_t, oem_defined, INTEGER, {
        .code   = "oem-defined",
        .name   = "OEM-defined",
        .flags  = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_tpm_device_table =
{
    .code       = "tpm-device",
    .name       = "TPM device",
    .type       = DMI_TYPE_TPM_DEVICE,
    .min_length = 0x1F,
    .attributes = dmi_tpm_device_attrs,
    .handlers   = {
        .decode = (dmi_table_decode_fn_t)dmi_tpm_device_decode,
        .free   = (dmi_table_free_fn_t)dmi_tpm_device_free
    }
};

dmi_tpm_device_t *dmi_tpm_device_decode(const dmi_table_t *table)
{
    dmi_tpm_device_t *info;
    const dmi_tpm_device_data_t *data;

    data = dmi_cast(data, dmi_table_data(table, DMI_TYPE_TPM_DEVICE));
    if (!data)
        return nullptr;

    info = dmi_alloc(table->context, sizeof(*info));
    if (!info)
        return nullptr;

    // Copy vendor identifier
    for (unsigned int i = 0; i < sizeof(data->vendor_id); i++)
        info->vendor_id[i] = data->vendor_id[i];
    info->vendor_id[sizeof(info->vendor_id) - 1] = 0;

    // Decode specification version
    info->spec_version = dmi_version(dmi_value(data->spec_version_major),
                                     dmi_value(data->spec_version_minor), 0);

    // Decode firmware version
    if (dmi_version_major(info->spec_version) > 1) {
        info->firmware_version = ((uint64_t)dmi_value(data->firmware_version_1) << 32) |
                                 ((uint64_t)dmi_value(data->firmware_version_2));
    } else {
        info->firmware_version = dmi_value(data->firmware_version_1);
    }

    // Decode description
    info->description = dmi_table_string(table, data->description);

    // Decode characteristics
    dmi_tpm_device_features_t features = {
        ._value = dmi_value(data->features)
    };

    info->features    = features;
    info->oem_defined = dmi_value(data->oem_defined);

    return info;
}

void dmi_tpm_device_free(dmi_tpm_device_t *info)
{
    dmi_free(info);
}
