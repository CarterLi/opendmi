//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>

#include <opendmi/context.h>
#include <opendmi/entity.h>
#include <opendmi/registry.h>

#include <opendmi/command.h>
#include <opendmi/command/common.h>

static bool dmi_filter_config_add_handle(dmi_context_t *context, const char *value);
static bool dmi_filter_config_add_type(dmi_context_t *context, const char *value);

dmi_filter_config_t dmi_filter_config =
{
    .filter = {}
};

const dmi_option_set_t dmi_filter_options =
{
    .options = (const dmi_option_t[]){
        {
            .short_names = "H",
            .long_names  = (const char *[]){ "handle", nullptr },
            .description = "Only display the entries of given handle(s)",
            .handler     = dmi_filter_config_add_handle,
            .argument    = {
                .name     = "HANDLE",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {
            .short_names = "T",
            .long_names  = (const char *[]){ "type", nullptr },
            .description = "Only display the entries of given type(s)",
            .handler     = dmi_filter_config_add_type,
            .argument    = {
                .name     = "TYPE",
                .type     = DMI_ARGUMENT_TYPE_STRING,
                .required = true
            }
        },
        {}
    }
};

dmi_handle_t dmi_parse_handle(const char *str)
{
    char *ep;
    unsigned long value;

    errno = 0;
    value = strtoul(str, &ep, 16);

    if ((*str == 0) or (*ep != 0)) {
        dmi_command_message("Invalid handle value: %s\n", str);
        return DMI_HANDLE_INVALID;
    }

    if (((errno == ERANGE) and (value == ULONG_MAX)) or (value >= DMI_HANDLE_INVALID)) {
        dmi_command_message("Handle is out of range: %s\n", str);
        return DMI_HANDLE_INVALID;
    }

    return (dmi_handle_t)value;
}

dmi_type_t dmi_parse_type(dmi_context_t *context, const char *str)
{
    char *ep;
    long value;

    if (*str == 0) {
        dmi_command_message("Empty type value: %s\n", str);
        return DMI_TYPE_INVALID;
    }

    if ((*str == '+') or (*str == '-')) {
        dmi_command_message("Invalid type value: %s\n", str);
        return DMI_TYPE_INVALID;
    }

    errno = 0;
    value = strtol(str, &ep, 10);

    if (*ep != 0) {
        value = dmi_type_find(context, str);
        if (value == DMI_TYPE_INVALID)
            dmi_command_message("Unknown type code: %s\n", str);

        return value;
    }

    if (((errno == ERANGE) and ((value == LONG_MIN) or (value == LONG_MAX))) or
        (value < 0) or (value > DMI_TYPE_MAX))
    {
        dmi_command_message("Type is out of range: %s\n", str);
        return DMI_TYPE_INVALID;
    }

    return (dmi_type_t)value;
}

void dmi_print_all(dmi_context_t *context, const dmi_format_t *format)
{
    void *session;
    dmi_registry_iter_t iter;
    dmi_entity_t *entity;

    session = format->handlers.initialize(context, stdout);
    if (not session)
        return;

    if (format->handlers.dump_start != nullptr)
        format->handlers.dump_start(session);

    format->handlers.entry(session);

    if (format->handlers.table_start != nullptr)
        format->handlers.table_start(session);

    dmi_registry_iter_init(&iter, context->registry, &dmi_filter_config.filter);
    while ((entity = dmi_registry_iter_next(&iter)) != nullptr) {
        dmi_print_entity(format, entity, session);
    }

    if (format->handlers.table_end != nullptr)
        format->handlers.table_end(session);

    if (format->handlers.dump_end != nullptr)
        format->handlers.dump_end(session);

    format->handlers.finalize(session);
}

void dmi_print_entity(
        const dmi_format_t *format,
        const dmi_entity_t *entity,
        void               *session)
{
    assert(format != nullptr);
    assert(entity != nullptr);
    assert(session != nullptr);

    const dmi_entity_spec_t *spec = entity->spec;
    const dmi_attribute_t   *attr = nullptr;

    format->handlers.entity_start(session, entity);

    if (entity->info) {
        if (format->handlers.entity_attrs_start != nullptr)
            format->handlers.entity_attrs_start(session, entity);

        for (attr = spec->attributes; attr->params.name; attr++) {
            const dmi_data_t *value = dmi_member_ptr(entity->info, attr->value, dmi_data_t);

            // Check attribute level
            if (attr->params.level != DMI_VERSION_NONE) {
                if (entity->level < attr->params.level)
                    continue;
            }

            format->handlers.entity_attr(session, entity, attr, value);
        }

        if (format->handlers.entity_attrs_end != nullptr)
            format->handlers.entity_attrs_end(session, entity);
    } else if (entity->type != DMI_TYPE_END_OF_TABLE) {
        format->handlers.entity_data(session, entity);
        format->handlers.entity_strings(session, entity);
    }

    format->handlers.entity_end(session, entity);
}

static bool dmi_filter_config_add_handle(dmi_context_t *context, const char *value)
{
    dmi_handle_t handle;

    assert(value != nullptr);
    dmi_unused(context);

    handle = dmi_parse_handle(value);
    if (handle == DMI_HANDLE_INVALID)
        return false;

    if (not dmi_filter_add_handle(&dmi_filter_config.filter, handle))
        return false;

    return true;
}

static bool dmi_filter_config_add_type(dmi_context_t *context, const char *value)
{
    dmi_type_t type;

    assert(value != nullptr);

    type = dmi_parse_type(context, value);
    if (type == DMI_TYPE_INVALID)
                return false;

    if (not dmi_filter_add_type(&dmi_filter_config.filter, type))
        return false;

    return true;
}
