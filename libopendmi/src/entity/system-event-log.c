//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/system-event-log.h>

static bool dmi_system_event_log_decode(dmi_entity_t *entity);

static const dmi_name_set_t dmi_system_log_access_method_names =
{
    .code  = "access-methods",
    .names = (dmi_name_t[]){
        {
            .id   = DMI_SYSTEM_LOG_ACCESS_METHOD_INDEXED_IO_8BIT_1_1,
            .code = "indexed-io-8bit-1-1",
            .name = "Indexed I/O: 1 8-bit index port, 1 8-bit data port"
        },
        {
            .id   = DMI_SYSTEM_LOG_ACCESS_METHOD_INDEXED_IO_8BIT_2_1,
            .code = "indexed-io-8bit-2-1",
            .name = "Indexed I/O: 2 8-bit index ports, 1 8-bit data port"
        },
        {
            .id   = DMI_SYSTEM_LOG_ACCESS_METHOD_INDEXED_IO_16BIT,
            .code = "indexed-io-16bit",
            .name = "Indexed I/O: 1 16-bit index port, 1 8-bit data port"
        },
        {
            .id   = DMI_SYSTEM_LOG_ACCESS_METHOD_MMAP_32BIT_ADDR,
            .code = "memory-mapped-32bit-address",
            .name = "Memory-mapped physical 32-bit address"
        },
        {
            .id   = DMI_SYSTEM_LOG_ACCESS_METHOD_DATA_FUNCTIONS,
            .code = "data-functions",
            .name = "General-purpose non-volatile data functions"
        },
        DMI_NAME_NULL
    }
};

static const dmi_name_set_t dmi_system_log_status_names =
{
    .code = "status",
    .names = (dmi_name_t[]){
        {
            .id   = 0,
            .code = "log-area-valid",
            .name = "Log area valid"
        },
        {
            .id   = 1,
            .code = "log-area-full",
            .name = "Log area full"
        },
        DMI_NAME_NULL
    }
};

const dmi_entity_spec_t dmi_system_event_log_spec =
{
    .code            = "system-event-log",
    .name            = "System event log",
    .type            = DMI_TYPE_SYSTEM_EVENT_LOG,
    .minimum_version = DMI_VERSION(2, 0, 0),
    .minimum_length  = 0x14,
    .decoded_length  = sizeof(dmi_system_event_log_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_system_event_log_t, access_method, ENUM, {
            .code   = "access-method",
            .name   = "Access Method",
            .values = &dmi_system_log_access_method_names
        }),
        DMI_ATTRIBUTE(dmi_system_event_log_t, status, SET, {
            .code = "status",
            .name = "Status",
            .values = &dmi_system_log_status_names,
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers = {
        .decode = dmi_system_event_log_decode
    }
};

static bool dmi_system_event_log_decode(dmi_entity_t *entity)
{
    dmi_system_event_log_t *info;
    const dmi_system_event_log_data_t *data;

    data = dmi_entity_data(entity, DMI_TYPE_SYSTEM_EVENT_LOG);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_SYSTEM_EVENT_LOG);
    if (info == nullptr)
        return false;

    info->access_method  = dmi_decode(data->access_method);
    info->status.__value = dmi_decode(data->status);

    if (entity->body_length > 0x14u) {
        entity->level = dmi_version(2, 1, 0);
    }

    return true;
}
