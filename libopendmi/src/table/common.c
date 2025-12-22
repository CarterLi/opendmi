//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <assert.h>

#include <opendmi/utils.h>
#include <opendmi/table/common.h>

const dmi_name_set_t dmi_status_names =
{
    .code  = "statuses",
    .names = {
        DMI_NAME_UNSPEC(DMI_STATUS_UNSPEC),
        DMI_NAME_OTHER(DMI_STATUS_OTHER),
        DMI_NAME_UNKNOWN(DMI_STATUS_UNKNOWN),
        {
            .id   = DMI_STATUS_OK,
            .code = "ok",
            .name = "OK"
        },
        {
            .id   = DMI_STATUS_NON_CRITICAL,
            .code = "non-critical",
            .name = "Non-critical"
        },
        {
            .id   = DMI_STATUS_CRITICAL,
            .code = "critical",
            .name = "Critical"
        },
        {
            .id   = DMI_STATUS_NON_RECOVERABLE,
            .code = "non-recoverable",
            .name = "Non-recoverable"
        },
        DMI_NAME_NULL
    }
};

const dmi_name_set_t dmi_error_correct_type_names =
{
    .code  = "error-correction-types",
    .names = {
        DMI_NAME_UNSPEC(DMI_ERROR_CORRECT_TYPE_UNSPEC),
        DMI_NAME_OTHER(DMI_ERROR_CORRECT_TYPE_OTHER),
        DMI_NAME_UNKNOWN(DMI_ERROR_CORRECT_TYPE_UNKNOWN),
        DMI_NAME_NONE(DMI_ERROR_CORRECT_TYPE_NONE),
        {
            .id   = DMI_ERROR_CORRECT_TYPE_PARITY,
            .code = "parity",
            .name = "Parity" 
        },
        {
            .id   = DMI_ERROR_CORRECT_TYPE_SINGLE_BIT,
            .code = "single-bit",
            .name = "Single-bit ECC" 
        },
        {
            .id   = DMI_ERROR_CORRECT_TYPE_MULTI_BIT,
            .code = "multi-bit",
            .name = "Multi-bit ECC" 
        },
        {
            .id   = DMI_ERROR_CORRECT_TYPE_CRC,
            .code = "crc",
            .name = "CRC"
        },
        DMI_NAME_NULL
    }
};

const dmi_attribute_t dmi_pci_addr_attrs[] =
{
    DMI_ATTRIBUTE(dmi_pci_addr_t, segment_group, INTEGER, {
        .code   = "segment-group",
        .name   = "Segment group",
        .unspec = DMI_VALUE_PTR((uint16_t)UINT16_MAX),
        .flags  = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_pci_addr_t, bus_number, INTEGER, {
        .code   = "bus-number",
        .name   = "Bus number",
        .unspec = DMI_VALUE_PTR((uint8_t)UINT8_MAX),
        .flags  = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_pci_addr_t, device_number, INTEGER, {
        .code   = "device-number",
        .name   = "Device number",
        .unspec = DMI_VALUE_PTR((uint8_t)UINT8_MAX),
        .flags  = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE(dmi_pci_addr_t, function_number, INTEGER, {
        .code   = "function-number",
        .name   = "Function number",
        .unspec = DMI_VALUE_PTR((uint8_t)UINT8_MAX),
        .flags  = DMI_ATTRIBUTE_FLAG_HEX
    }),
    DMI_ATTRIBUTE_NULL
};

const char *dmi_status_name(dmi_status_t value)
{
    return dmi_name_lookup(&dmi_status_names, value);
}

const char *dmi_error_correct_type_name(dmi_error_correct_type_t value)
{
    return dmi_name_lookup(&dmi_error_correct_type_names, value);
}

void dmi_pci_addr_decode(dmi_pci_addr_t *addr, const dmi_pci_addr_data_t *data)
{
    assert(addr != nullptr);
    assert(data != nullptr);

    addr->segment_group   = dmi_value(data->segment_group);
    addr->bus_number      = dmi_value(data->bus_number);
    addr->device_number   = dmi_value((dmi_byte_t)data->device_number);
    addr->function_number = dmi_value((dmi_byte_t)data->function_number);

    if (addr->bus_number == UINT8_MAX) {
        addr->device_number = UINT8_MAX;
        addr->function_number = UINT8_MAX;
    }
}
