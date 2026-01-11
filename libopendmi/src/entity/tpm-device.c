//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/tpm-device.h>

static bool dmi_tpm_device_decode(dmi_entity_t *entity);

static const dmi_name_set_t dmi_tpm_device_feature_names =
{
    .code  = "tpm-device-features",
    .names = (dmi_name_t[]){
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
    }
};

const dmi_entity_spec_t dmi_tpm_device_spec =
{
    .code            = "tpm-device",
    .name            = "TPM device",
    .type            = DMI_TYPE_TPM_DEVICE,
    .minimum_version = DMI_VERSION(2, 0, 0),
    .minimum_length  = 0x1F,
    .decoded_length  = sizeof(dmi_tpm_device_t),
    .attributes      = (dmi_attribute_t[]){
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
            .values = &dmi_tpm_device_feature_names
        }),
        DMI_ATTRIBUTE(dmi_tpm_device_t, oem_defined, INTEGER, {
            .code   = "oem-defined",
            .name   = "OEM-defined",
            .flags  = DMI_ATTRIBUTE_FLAG_HEX
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers = {
        .decode = dmi_tpm_device_decode
    }
};

static bool dmi_tpm_device_decode(dmi_entity_t *entity)
{
    dmi_tpm_device_t *info;
    const dmi_tpm_device_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_TPM_DEVICE);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_TPM_DEVICE);
    if (info == nullptr)
        return false;

    // Copy vendor identifier
    for (size_t i = 0; i < sizeof(data->vendor_id); i++)
        info->vendor_id[i] = data->vendor_id[i];
    info->vendor_id[sizeof(info->vendor_id) - 1] = 0;

    // Decode specification version
    info->spec_version = dmi_version(dmi_decode(data->spec_version_major),
                                     dmi_decode(data->spec_version_minor), 0);

    // Decode firmware version
    if (dmi_version_major(info->spec_version) > 1) {
        info->firmware_version = ((uint64_t)dmi_decode(data->firmware_version_1) << 32) |
                                 ((uint64_t)dmi_decode(data->firmware_version_2));
    } else {
        info->firmware_version = dmi_decode(data->firmware_version_1);
    }

    // Decode description
    info->description = dmi_entity_string(entity, data->description);

    // Decode characteristics
    dmi_tpm_device_features_t features = {
        .__value = dmi_decode(data->features)
    };

    info->features    = features;
    info->oem_defined = dmi_decode(data->oem_defined);

    return true;
}
