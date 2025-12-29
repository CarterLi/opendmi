//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/entity/mgmt-controller.h>
#include <opendmi/utils.h>
#include <memory.h>

const dmi_attribute_t dmi_mgmt_controller_host_if_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_entity_spec_t dmi_mgmt_controller_host_if_spec =
{
    .code        = "mgmt-controller-host-if",
    .name        = "Management controller host interface",
    .type        = DMI_TYPE_MGMT_CONTROLLER_HOST_IF,
    .min_length  = 0x06,
    .attributes  = dmi_mgmt_controller_host_if_attrs
};

dmi_mgmt_controller_t *
dmi_mgmt_controller_decode(const dmi_entity_t *entity, dmi_version_t *plevel)
{
    dmi_context_t *ctx = entity->context;
    dmi_mgmt_controller_t *info;
    const dmi_mgmt_controller_data_t *data;
    const dmi_mgmt_controller_extra_t *extra;

    dmi_unused(plevel);

    data = dmi_cast(data, dmi_entity_data(entity, DMI_TYPE_MGMT_CONTROLLER_HOST_IF));
    if (data == nullptr)
        return nullptr;

    const off_t offset = sizeof(*data) + dmi_value(data->if_data_length);
    extra = dmi_cast(extra, (uint8_t *)data + offset);

    info = dmi_alloc(ctx, sizeof(*info));
    if (info == nullptr)
        return nullptr;

    info->if_type        = dmi_value(data->if_type);
    info->if_data_length = dmi_value(data->if_data_length);

    info->if_data = dmi_alloc(ctx, info->if_data_length);
    if (info->if_data == nullptr) {
        dmi_free(info);
        return nullptr;
    }
    memcpy(info->if_data, data->if_data, info->if_data_length);

    info->protocol_records_count = dmi_value(extra->protocol_records_count);

    const size_t memsize = sizeof(*info->protocol_records) * info->protocol_records_count;
    info->protocol_records = dmi_alloc(ctx, memsize);
    if (info->protocol_records == nullptr) {
        dmi_mgmt_controller_free(info);
        return nullptr;
    }

    const dmi_byte_t *cursor = extra->protocol_records_data;
    for (size_t i = 0; i < info->protocol_records_count; i++) {
        dmi_mgmt_protocol_record_data_t *rec_data = dmi_cast(rec_data, cursor);

        dmi_mgmt_if_type_t type   = dmi_value(rec_data->type);
        size_t             length = dmi_value(rec_data->length);

        dmi_mgmt_protocol_record_t *rec = dmi_alloc(ctx, sizeof(*rec) + length);
        if (rec == nullptr) {
            dmi_mgmt_controller_free(info);
            return nullptr;
        }
        rec->type   = type;
        rec->length = length;
        memcpy(rec->data, rec_data->data, length);

        info->protocol_records[i] = rec;

        cursor += sizeof(*rec_data) + rec_data->length;
    }

    return info;
}

void dmi_mgmt_controller_free(dmi_mgmt_controller_t *info)
{
    dmi_free(info->if_data);
    if (info->protocol_records != nullptr) {
        for (size_t i = 0; i < info->protocol_records_count; i++) {
            dmi_free(info->protocol_records[i]);
        }
    }
    dmi_free(info->protocol_records);
    dmi_free(info);
}
