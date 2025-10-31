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

const dmi_attribute_spec_t dmi_cache_attrs[] =
{
    {
        .tag  = "socket-designator",
        .name = "Socket designator",
        .type = DMI_ATTRIBUTE_TYPE_STRING
    },
    {
        .tag  = "level",
        .name = "Cache level"
    },
    {
        .tag  = "socketed",
        .name = "Socketed",
        .type = DMI_ATTRIBUTE_TYPE_BOOL
    },
    {
        .tag  = "location",
        .name = "Location (relative to CPU module)",
        .type = DMI_ATTRIBUTE_TYPE_ENUM
    },
    {
        .tag  = "status",
        .name = "Status",
        .type = DMI_ATTRIBUTE_TYPE_BOOL
    },
    {
        .tag    = "mode",
        .name   = "Operational mode",
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_cache_mode_names
    },
    {
        .tag  = "maximum-size",
        .name = "Maximum cache size",
        .type = DMI_ATTRIBUTE_TYPE_SIZE,
        .unit = "KiB"
    },
    {
        .tag  = "installed-size",
        .name = "Installed cache size",
        .type = DMI_ATTRIBUTE_TYPE_SIZE,
        .unit = "KiB"
    },
    {
        .tag  = "supported-sram",
        .name = "Supported SRAM type",
        .type = DMI_ATTRIBUTE_TYPE_SET
    },
    {
        .tag  = "installed-sram",
        .name = "Installed SRAM type",
        .type = DMI_ATTRIBUTE_TYPE_SET
    },
    {
        .tag  = "speed",
        .name = "Cache speed",
        .type = DMI_ATTRIBUTE_TYPE_INT,
        .unit = "ns"
    },
    {
        .tag  = "ecc-type",
        .name = "Error correction type",
        .type = DMI_ATTRIBUTE_TYPE_ENUM
    },
    {
        .tag    = "type",
        .name   = "System cache type",
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_cache_type_names
    },
    {
        .tag    = "associativity",
        .name   = "Associativity",
        .type   = DMI_ATTRIBUTE_TYPE_ENUM,
        .values = dmi_cache_assoc_names
    },
    { NULL, NULL, DMI_ATTRIBUTE_TYPE_NONE, NULL, NULL }
};

const dmi_table_spec_t dmi_cache_table =
{
    .tag        = "cache",
    .name       = "Cache information",
    .type       = DMI_TYPE_CACHE,
    .min_length = 0x0F,
    .attributes = dmi_cache_attrs
};

const char *dmi_cache_type_name(enum dmi_cache_type value)
{
    return dmi_name_lookup(dmi_cache_type_names, value);
}

const char *dmi_cache_mode_name(enum dmi_cache_mode value)
{
    return dmi_name_lookup(dmi_cache_mode_names, value);
}

const char *dmi_cache_assoc_name(enum dmi_cache_assoc value)
{
    return dmi_name_lookup(dmi_cache_assoc_names, value);
}

const char *dmi_cache_location_name(enum dmi_cache_location value)
{
    return dmi_name_lookup(dmi_cache_location_names, value);
}

struct dmi_cache_info *dmi_cache_info_create(struct dmi_cache_data *table)
{
    struct dmi_cache_info *info;

    if (!table) {
        errno = EINVAL;
        return nullptr;
    }

    info = malloc(sizeof(struct dmi_cache_info));
    if (!info) {
        errno = ENOMEM;
        return nullptr;
    }

    return info;
}

void dmi_cache_info_destroy(struct dmi_cache_info *info)
{
    if (!info)
        return;

    free(info);
}

size_t dmi_cache_size(dmi_cache_size_t value)
{
    size_t size = value & 0x7FFFU;

    if (value & 0x8000U)
        size <<= 16; // Granularity is 64 Kb
    else
        size <<= 10; // Granularity is 1 Kb

    return size;
}

size_t dmi_cache_size_ex(dmi_cache_size_ex_t value)
{
    size_t size = value & 0x7FFFFFFFU;

    if (value & 0x80000000U)
        size <<= 16; // Granularity is 64 Kb
    else
        size <<= 10; // Granularity is 1 Kb

    return size;
}

struct dmi_cache_info *dmi_cache_info_decode(dmi_table_t *table)
{
    struct dmi_cache_info *info;
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
    info->maximum_size        = dmi_cache_size(data->maximum_size);
    info->installed_size      = dmi_cache_size(data->installed_size);
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
            info->maximum_size = dmi_cache_size_ex(data->maximum_size_ex);
        if (data->installed_size == 0xFFFU)
            info->installed_size = dmi_cache_size_ex(data->installed_size_ex);
    }

    return info;
}

void dmi_cache_info_free(struct dmi_cache_info *info)
{
    if (info == nullptr)
        return;

    free(info);
}
