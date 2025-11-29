//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/name.h>
#include <opendmi/context.h>
#include <opendmi/utils.h>
#include <opendmi/table/system.h>

const dmi_name_t dmi_system_wakeup_type_names[] =
{
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_RESERVED,
        .code = "reserved",
        .name = "Reserved"
    },
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_APM_TIMER,
        .code = "apm-timer",
        .name = "APM Timer"
    },
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_MODEM_RING,
        .code = "modem-ring",
        .name = "Modem Ring"
    },
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_LAN_REMOTE,
        .code = "lan-remote",
        .name = "LAN Remote"
    },
    {
        .id = DMI_SYSTEM_WAKEUP_TYPE_POWER_SWITCH,
        .code = "power-switch",
        .name = "Power Switch"
    },
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_PCI_PME,
        .code = "pci-pme",
        .name = "PCI PME#"
    },
    {
        .id   = DMI_SYSTEM_WAKEUP_TYPE_POWER_RESTORE,
        .code = "power-restore",
        .name = "AC Power Restored"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_system_attrs[] =
{
    DMI_ATTRIBUTE(dmi_system_t, vendor, STRING, {
        .code = "vendor",
        .name = "Manufacturer"
    }),
    DMI_ATTRIBUTE(dmi_system_t, product, STRING, {
        .code = "product",
        .name = "Product"
    }),
    DMI_ATTRIBUTE(dmi_system_t, version, STRING, {
        .code = "version",
        .name = "Version"
    }),
    DMI_ATTRIBUTE(dmi_system_t, serial_number, STRING, {
        .code = "serial-number",
        .name = "Serial number"
    }),
    DMI_ATTRIBUTE(dmi_system_t, uuid, UUID, {
        .code = "uuid",
        .name = "UUID"
    }),
    DMI_ATTRIBUTE(dmi_system_t, wakeup_type, ENUM, {
        .code   = "wakeup-type",
        .name   = "Wakeup type",
        .values = dmi_system_wakeup_type_names
    }),
    DMI_ATTRIBUTE(dmi_system_t, sku_number, STRING, {
        .code = "sku-number",
        .name = "SKU number"
    }),
    DMI_ATTRIBUTE(dmi_system_t, family, STRING, {
        .code = "family",
        .name = "Family"
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_system_table =
{
    .code          = "system",
    .name          = "System information",
    .type          = DMI_TYPE_SYSTEM,
    .required_from = DMI_VERSION(2, 3, 0),
    .required_till = DMI_VERSION_NONE,
    .unique        = true,
    .min_length    = 0x8,
    .attributes    = dmi_system_attrs,
    .handlers      = {
        .decode = (dmi_table_decode_fn_t)dmi_system_decode,
        .free   = (dmi_table_free_fn_t)dmi_system_free
    }
};

const char *dmi_system_wakeup_type_name(dmi_system_wakeup_type_t value)
{
    return dmi_name_lookup(dmi_system_wakeup_type_names, value);
}

dmi_system_t *dmi_system_decode(const dmi_table_t *table)
{
    dmi_system_t *info;
    const dmi_system_data_t *data;

    if (!table) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_SYSTEM) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = calloc(1, sizeof(*info));
    if (!info) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    data = dmi_cast(data, table->data);

    info->vendor        = dmi_table_string(table, data->vendor);
    info->product       = dmi_table_string(table, data->product);
    info->version       = dmi_table_string(table, data->version);
    info->serial_number = dmi_table_string(table, data->serial_number);

    // SMBIOS 2.1 features
    if (table->body_length >= 0x08) {
        info->uuid        = dmi_decode_uuid(data->uuid);
        info->wakeup_type = data->wakeup_type;
    }

    // SMBIOS 2.4 features
    if (table->body_length >= 0x19) {
        info->sku_number = dmi_table_string(table, data->sku_number);
        info->family     = dmi_table_string(table, data->family);
    }

    return info;
}

void dmi_system_free(dmi_system_t *info)
{
    free(info);
}
