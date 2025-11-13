//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <opendmi/context.h>
#include <opendmi/name.h>
#include <opendmi/utils.h>
#include <opendmi/table/cache.h>

static const dmi_name_t dmi_cache_type_names[] =
{
    {
        .id   = DMI_CACHE_TYPE_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_CACHE_TYPE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_CACHE_TYPE_INSTRUCTION,
        .code = "instruction",
        .name = "Instruction"
    },
    {
        .id   = DMI_CACHE_TYPE_DATA,
        .code = "data",
        .name = "Data"
    },
    {
        .id   = DMI_CACHE_TYPE_UNIFIED,
        .code = "unified",
        .name = "Unified"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_cache_mode_names[] =
{
    {
        .id   = DMI_CACHE_MODE_WRITE_THROUGH,
        .code = "write-through",
        .name = "Write-through"
    },
    {
        .id   = DMI_CACHE_MODE_WRITE_BACK,
        .code = "write-back",
        .name = "Write-back"
    },
    {
        .id   = DMI_CACHE_MODE_VARIABLE,
        .code = "variable",
        .name = "Variable"
    },
    {
        .id   = DMI_CACHE_MODE_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_cache_assoc_names[] =
{
    {
        .id   = DMI_CACHE_ASSOC_OTHER,
        .code = "other",
        .name = "Other"
    },
    {
        .id   = DMI_CACHE_ASSOC_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = DMI_CACHE_ASSOC_DIRECT,
        .code = "direct",
        .name = "Direct mapped"
    },
    {
        .id   = DMI_CACHE_ASSOC_2WAY,
        .code = "2-way",
        .name = "2-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_4WAY,
        .code = "4-way",
        .name = "4-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_FULL,
        .code = "full",
        .name = "Fully associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_8WAY,
        .code = "8-way",
        .name = "8-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_16WAY,
        .code = "16-way",
        .name = "16-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_12WAY,
        .code = "12-way",
        .name = "12-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_24WAY,
        .code = "24-way",
        .name = "24-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_32WAY,
        .code = "32-way",
        .name = "32-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_48WAY,
        .code = "48-way",
        .name = "48-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_64WAY,
        .code = "64-way",
        .name = "64-way set-associative"
    },
    {
        .id   = DMI_CACHE_ASSOC_20WAY,
        .code = "20-way",
        .name = "20-way set-associative"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_cache_location_names[] =
{
    {
        .id   = DMI_CACHE_LOCATION_INTERNAL,
        .code = "internal",
        .name = "Internal"
    },
    {
        .id   = DMI_CACHE_LOCATION_EXTERNAL,
        .code = "external",
        .name = "External"
    },
    {
        .id   = DMI_CACHE_LOCATION_RESERVED,
        .code = "reserved",
        .name = "Reserved"
    },
    {
        .id   = DMI_CACHE_LOCATION_UNKNOWN,
        .code = "unknown",
        .name = "Unknown"
    },
    DMI_NAME_NULL
};

const dmi_attribute_t dmi_cache_attrs[] =
{
    DMI_ATTRIBUTE(dmi_cache_t, socket, STRING, {
        .code = "socket-designator",
        .name = "Socket designator"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, level, INTEGER, {
        .code = "level",
        .name = "Cache level"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, socketed, BOOL, {
        .code = "socketed",
        .name = "Socketed",
    }),
    DMI_ATTRIBUTE(dmi_cache_t, location, ENUM, {
        .code = "location",
        .name = "Location (relative to CPU module)",
    }),
    DMI_ATTRIBUTE(dmi_cache_t, enabled, BOOL, {
        .code = "enabled",
        .name = "Enabled"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, mode, ENUM, {
        .code   = "mode",
        .name   = "Operational mode",
        .values = dmi_cache_mode_names
    }),
    DMI_ATTRIBUTE(dmi_cache_t, maximum_size, SIZE, {
        .code = "maximum-size",
        .name = "Maximum cache size",
        .unit = "KiB"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, installed_size, SIZE, {
        .code = "installed-size",
        .name = "Installed cache size",
        .unit = "KiB"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, supported_sram_type, SET, {
        .code = "supported-sram",
        .name = "Supported SRAM type"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, current_sram_type, SET, {
        .code = "current-sram",
        .name = "Current SRAM type"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, speed, INTEGER, {
        .code = "speed",
        .name = "Cache speed",
        .unit = "ns"
    }),
    DMI_ATTRIBUTE(dmi_cache_t, ecc_type, ENUM, {
        .code = "ecc-type",
        .name = "Error correction type",
    }),
    DMI_ATTRIBUTE(dmi_cache_t, type, ENUM, {
        .code   = "type",
        .name   = "System cache type",
        .values = dmi_cache_type_names
    }),
    DMI_ATTRIBUTE(dmi_cache_t, associativity, ENUM, {
        .code   = "associativity",
        .name   = "Associativity",
        .values = dmi_cache_assoc_names
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_cache_table =
{
    .tag        = "cache",
    .name       = "Cache information",
    .type       = DMI_TYPE_CACHE,
    .min_length = 0x0F,
    .attributes = dmi_cache_attrs
};

const char *dmi_cache_type_name(dmi_cache_type_t value)
{
    return dmi_name_lookup(dmi_cache_type_names, value);
}

const char *dmi_cache_mode_name(dmi_cache_mode_t value)
{
    return dmi_name_lookup(dmi_cache_mode_names, value);
}

const char *dmi_cache_assoc_name(dmi_cache_assoc_t value)
{
    return dmi_name_lookup(dmi_cache_assoc_names, value);
}

const char *dmi_cache_location_name(dmi_cache_location_t value)
{
    return dmi_name_lookup(dmi_cache_location_names, value);
}

struct dmi_cache *dmi_cache_info_create(struct dmi_cache_data *table)
{
    struct dmi_cache *info;

    if (!table) {
        errno = EINVAL;
        return nullptr;
    }

    info = malloc(sizeof(struct dmi_cache));
    if (!info) {
        errno = ENOMEM;
        return nullptr;
    }

    return info;
}

void dmi_cache_info_destroy(struct dmi_cache *info)
{
    if (!info)
        return;

    free(info);
}

dmi_size_t dmi_cache_size(dmi_cache_size_t value)
{
    dmi_size_t size = value & 0x7FFFU;

    if (value & 0x8000U)
        size <<= 16; // Granularity is 64 Kb
    else
        size <<= 10; // Granularity is 1 Kb

    return size;
}

dmi_size_t dmi_cache_size_ex(dmi_cache_size_ex_t value)
{
    dmi_size_t size = value & 0x7FFFFFFFU;

    if (value & 0x80000000U)
        size <<= 16; // Granularity is 64 Kb
    else
        size <<= 10; // Granularity is 1 Kb

    return size;
}

struct dmi_cache *dmi_cache_info_decode(dmi_table_t *table)
{
    struct dmi_cache *info;
    struct dmi_cache_data *data;

    if (table == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return nullptr;
    }
    if (table->type != DMI_TYPE_CACHE) {
        dmi_set_error(table->context, DMI_ERROR_INVALID_TABLE_TYPE);
        return nullptr;
    }

    info = malloc(sizeof(*info));
    if (info == nullptr) {
        dmi_set_error(table->context, DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }
    memset(info, 0, sizeof(*info));

    data = dmi_cast(data, table->data);

    // SMBIOS 2.0+
    info->socket              = dmi_table_string(table, data->socket);
    info->level               = data->config.level;
    info->mode                = data->config.mode;
    info->location            = data->config.location;
    info->socketed            = data->config.socketed;
    info->enabled             = data->config.enabled;
    info->maximum_size        = dmi_cache_size(dmi_decode_word(data->maximum_size));
    info->installed_size      = dmi_cache_size(dmi_decode_word(data->installed_size));
    info->supported_sram_type = data->supported_sram_type;
    info->current_sram_type   = data->current_sram_type;

    // SMBIOS 2.1+
    if (data->header.length >= 0x0F) {
        info->type          = data->type;
        info->associativity = data->associativity;
        info->speed         = data->speed;
        info->ecc_type      = data->ecc_type;
    }

    // SMBIOS 3.1+
    if (data->header.length >= 0x13) {
        if (data->maximum_size == 0xFFFFU)
            info->maximum_size = dmi_cache_size_ex(dmi_decode_dword(data->maximum_size_ex));
        if (data->installed_size == 0xFFFU)
            info->installed_size = dmi_cache_size_ex(dmi_decode_dword(data->installed_size_ex));
    }

    return info;
}

void dmi_cache_info_free(struct dmi_cache *info)
{
    if (info == nullptr)
        return;

    free(info);
}
