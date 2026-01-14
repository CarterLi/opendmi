//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <memory.h>

#include <opendmi/utils.h>
#include <opendmi/utils/decode.h>

#include <opendmi/entity/mgmt-controller.h>

static bool dmi_mgmt_controller_decode(dmi_entity_t *entity);
static void dmi_mgmt_controller_cleanup(dmi_entity_t *entity);

const dmi_name_set_t dmi_mgmt_if_type_names =
{
    .code  = "mgmt-if-types",
    .names = (dmi_name_t[]){
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_KCS,
            .code = "keyboard-controller-style",
            .name = "Keyboard Controller Style"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_8250_UART,
            .code = "8250-uart",
            .name = "8250 UART Register Compatible"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_16450_UART,
            .code = "16450-uart",
            .name = "16450 UART Register Compatible"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_16550_UART,
            .code = "16550-uart",
            .name = "16550/16550A UART Register Compatible"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_16650_UART,
            .code = "16650-uart",
            .name = "16650/16650A UART Register Compatible"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_16750_UART,
            .code = "16750-uart",
            .name = "16750/16750A UART Register Compatible"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_16850_UART,
            .code = "16850-uart",
            .name = "16850/16850A UART Register Compatible"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_I2C_SMBUS,
            .code = "i2c-smbus",
            .name = "I2C/SMBUS"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_I3C,
            .code = "i3c",
            .name = "I3C"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_PCIE_VDM,
            .code = "pcie-vdm",
            .name = "PCIe VDM"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_MMBI,
            .code = "mmbi",
            .name = "MMBI"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_PCC,
            .code = "pcc",
            .name = "PCC"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_UCIE,
            .code = "ucie",
            .name = "UCIe"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_MCTP_USB,
            .code = "usb",
            .name = "USB"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_NETWORK_HOST_IF,
            .code = "network-host-interface",
            .name = "Network Host Interface"
        },
        {
            .id   = DMI_MGMT_IF_TYPE_OEM,
            .code = "oem-defined",
            .name = "OEM-defined"
        },
        DMI_NAME_NULL
    }
};

const dmi_name_set_t dmi_mgmt_protocol_names =
{
    .code  = "mgmt-protocols",
    .names = (dmi_name_t[]){
        {
            .id   = DMI_MGMT_PROTOCOL_IPMI,
            .code = "ipmi",
            .name = "IPMI"
        },
        {
            .id   = DMI_MGMT_PROTOCOL_MCTP,
            .code = "mctp",
            .name = "MCTP"
        },
        {
            .id   = DMI_MGMT_PROTOCOL_REDFISH_OVER_IP,
            .code = "redfish-over-ip",
            .name = "Redfish over IP"
        },
        {
            .id   = DMI_MGMT_PROTOCOL_OEM,
            .code = "oem-defined",
            .name = "OEM-defined"
        },
        DMI_NAME_NULL
    }
};

const dmi_entity_spec_t dmi_mgmt_controller_host_if_spec =
{
    .code            = "mgmt-controller-host-if",
    .name            = "Management controller host interface",
    .type            = DMI_TYPE(MGMT_CONTROLLER_HOST_IF),
    .minimum_version = DMI_VERSION(2, 0, 0),
    .minimum_length  = 0x06,
    .decoded_length  = sizeof(dmi_mgmt_controller_t),
    .attributes      = (dmi_attribute_t[]){
        DMI_ATTRIBUTE(dmi_mgmt_controller_t, if_type, ENUM, {
            .code    = "if-type",
            .name    = "Interface Type",
            .values  = &dmi_mgmt_if_type_names
        }),
        DMI_ATTRIBUTE_NULL
    },
    .handlers = {
        .decode  = dmi_mgmt_controller_decode,
        .cleanup = dmi_mgmt_controller_cleanup
    }
};

static bool dmi_mgmt_controller_decode(dmi_entity_t *entity)
{
    dmi_mgmt_controller_t *info;
    const dmi_mgmt_controller_data_t *data;
    const dmi_mgmt_controller_extra_t *extra;

    data = dmi_entity_data(entity, DMI_TYPE_MGMT_CONTROLLER_HOST_IF);
    if (data == nullptr)
        return false;

    info = dmi_entity_info(entity, DMI_TYPE_MGMT_CONTROLLER_HOST_IF);
    if (info == nullptr)
        return false;

    const off_t offset = sizeof(*data) + dmi_decode(data->if_data_length);
    extra = dmi_cast(extra, (uint8_t *)data + offset);

    info->if_type        = dmi_decode(data->if_type);
    info->if_data_length = dmi_decode(data->if_data_length);

    info->if_data = dmi_alloc(entity->context, info->if_data_length);
    if (info->if_data == nullptr) {
        dmi_mgmt_controller_cleanup(entity);
        return false;
    }
    memcpy(info->if_data, data->if_data, info->if_data_length);

    info->protocol_records_count = dmi_decode(extra->protocol_records_count);

    const size_t memsize = sizeof(*info->protocol_records) * info->protocol_records_count;
    info->protocol_records = dmi_alloc(entity->context, memsize);
    if (info->protocol_records == nullptr) {
        dmi_mgmt_controller_cleanup(entity);
        return false;
    }

    const dmi_byte_t *cursor = extra->protocol_records_data;
    for (size_t i = 0; i < info->protocol_records_count; i++) {
        dmi_mgmt_protocol_record_data_t *rec_data = dmi_cast(rec_data, cursor);

        dmi_mgmt_if_type_t type   = dmi_decode(rec_data->type);
        size_t             length = dmi_decode(rec_data->length);

        dmi_mgmt_protocol_record_t *rec = dmi_alloc(entity->context, sizeof(*rec) + length);
        if (rec == nullptr) {
            dmi_mgmt_controller_cleanup(entity);
            return false;
        }
        rec->type   = type;
        rec->length = length;
        memcpy(rec->data, rec_data->data, length);

        info->protocol_records[i] = rec;

        cursor += sizeof(*rec_data) + rec_data->length;
    }

    return true;
}

static void dmi_mgmt_controller_cleanup(dmi_entity_t *entity)
{
    dmi_mgmt_controller_t *info;

    info = dmi_entity_info(entity, DMI_TYPE_MGMT_CONTROLLER_HOST_IF);
    if (info == nullptr)
        return;

    dmi_free(info->if_data);

    if (info->protocol_records != nullptr) {
        for (size_t i = 0; i < info->protocol_records_count; i++) {
            dmi_free(info->protocol_records[i]);
        }
    }
    dmi_free(info->protocol_records);
}
