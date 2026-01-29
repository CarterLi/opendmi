//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/entity/pointing-device.h>

typedef struct dmi_pointing_device_data dmi_pointing_device_data_t;

dmi_packed_struct(dmi_pointing_device_data)
{
    /**
     * @brief Structure header.
     */
    dmi_header_t header;

    /**
     * @brief Type of pointing device.
     */
    dmi_byte_t type;

    /**
     * @brief Interface type for the pointing device.
     */
    dmi_byte_t interface;

    /**
     * @brief Number of buttons on the pointing device. If the device has
     * three buttons, the field value is 0x03.
     */
    dmi_byte_t button_count;
};

static bool dmi_pointing_device_test_min_length(dmi_context_t *context);
static bool dmi_pointing_device_test_empty(dmi_context_t *context);

static bool dmi_pointing_device_test_types(dmi_context_t *context);
static bool dmi_pointing_device_test_types_value(dmi_context_t *context, int value);
static bool dmi_pointing_device_test_ifaces(dmi_context_t *context);
static bool dmi_pointing_device_test_ifaces_value(dmi_context_t *context, int value);
static bool dmi_pointing_device_test_buttons(dmi_context_t *context);
static bool dmi_pointing_device_test_buttons_value(dmi_context_t *context, int value);

int main(void)
{
    int rv;
    dmi_context_t *context;

    context = dmi_create(DMI_CONTEXT_FLAG_RELAXED);
    if (context == nullptr)
        return EXIT_FAILURE;

    rv = EXIT_FAILURE;
    do {
        if (!dmi_pointing_device_test_min_length(context))
            break;
        if (!dmi_pointing_device_test_empty(context))
            break;

        if (!dmi_pointing_device_test_types(context))
            break;
        if (!dmi_pointing_device_test_ifaces(context))
            break;
        if (!dmi_pointing_device_test_buttons(context))
            break;

        rv = EXIT_SUCCESS;
    } while (false);

    dmi_destroy(context);

    return rv;
}

static bool dmi_pointing_device_test_min_length(dmi_context_t *context)
{
    struct {
        dmi_pointing_device_data_t data;
        dmi_word_t terminator;
    } envelope = {
        .data = {
            .header = {
                .type   = dmi_encode((dmi_byte_t)DMI_TYPE_POINTING_DEVICE),
                .length = dmi_encode((dmi_byte_t)(sizeof(dmi_pointing_device_data_t) - 1)),
                .handle = dmi_encode(DMI_HANDLE_TEST)
            },
            0
        },
        .terminator = 0
    };

    dmi_entity_t *entity = dmi_entity_create(context, &envelope);
    if (entity == nullptr)
        return false;

    bool result = false;
    do {
        if (dmi_entity_decode(entity))
            break;

        const dmi_error_t *error = dmi_error_get_last(context);
        if (error->reason != DMI_ERROR_INVALID_ENTITY_LENGTH)
            break;

        result = true;
    } while (false);

    dmi_entity_destroy(entity);

    return result;
}

static bool dmi_pointing_device_test_empty(dmi_context_t *context)
{
    struct {
        dmi_pointing_device_data_t data;
        dmi_word_t terminator;
    } envelope = {
        .data = {
            .header = {
                .type   = dmi_encode((dmi_byte_t)DMI_TYPE_POINTING_DEVICE),
                .length = dmi_encode((dmi_byte_t)sizeof(dmi_pointing_device_data_t)),
                .handle = dmi_encode(DMI_HANDLE_TEST)
            },
            0
        }
    };

    dmi_entity_t *entity = dmi_entity_create(context, &envelope);
    if (entity == nullptr)
        return false;

    bool result = false;
    do {
        if (not dmi_entity_decode(entity))
            break;

        if (entity->type != DMI_TYPE_POINTING_DEVICE)
            break;
        if (entity->spec == nullptr)
            break;
        if (entity->spec->type != DMI_TYPE_POINTING_DEVICE)
            break;
        if (entity->handle != DMI_HANDLE_TEST)
            break;

        if (entity->total_length != sizeof(dmi_pointing_device_data_t) + sizeof(dmi_word_t))
            break;
        if (entity->body_length != sizeof(dmi_pointing_device_data_t))
            break;
        if (entity->extra_length != sizeof(dmi_word_t))
            break;
        if (entity->string_count != 0)
            break;

        if (entity->level != DMI_VERSION(2, 1, 0))
            break;

        dmi_pointing_device_t *info = dmi_entity_info(entity, DMI_TYPE_POINTING_DEVICE);
        if (info == nullptr)
            break;

        if (info->type != DMI_POINTING_DEVICE_TYPE_UNSPEC)
            break;
        if (info->interface != DMI_POINTING_DEVICE_IFACE_UNSPEC)
            break;
        if (info->button_count != 0)
            break;

        result = true;
    } while (false);

    dmi_entity_destroy(entity);

    return result;
}

static bool dmi_pointing_device_test_types(dmi_context_t *context)
{
    int value;

    for (value = 0; value < __DMI_POINTING_DEVICE_TYPE_COUNT; value++) {
        if (!dmi_pointing_device_test_types_value(context, value))
            return false;
    }

    return true;
}

static bool dmi_pointing_device_test_types_value(dmi_context_t *context, int value)
{
    struct {
        dmi_pointing_device_data_t data;
        dmi_word_t terminator;
    } envelope = {
        .data = {
            .header = {
                .type   = dmi_encode((dmi_byte_t)DMI_TYPE_POINTING_DEVICE),
                .length = dmi_encode((dmi_byte_t)sizeof(dmi_pointing_device_data_t)),
                .handle = dmi_encode(DMI_HANDLE_TEST)
            },
            .type         = dmi_encode((dmi_byte_t)value),
            .interface    = 0,
            .button_count = 0
        },
        .terminator = 0
    };

    dmi_entity_t *entity = dmi_entity_create(context, &envelope);
    if (entity == nullptr)
        return false;

    bool result = false;
    do {
        if (not dmi_entity_decode(entity))
            break;

        dmi_pointing_device_t *info = dmi_entity_info(entity, DMI_TYPE_POINTING_DEVICE);
        if (info == nullptr)
            break;

        if (info->type != (typeof(info->type))value)
            break;

        result = true;
    } while (0);

    dmi_entity_destroy(entity);

    return result;
}

static bool dmi_pointing_device_test_ifaces(dmi_context_t *context)
{
    int value;

    for (value = 0; value < __DMI_POINTING_DEVICE_IFACE_COUNT; value++) {
        if ((value >= __DMI_POINTING_DEVICE_IFACE_UNASSIGNED_START) and
            (value <= __DMI_POINTING_DEVICE_IFACE_UNASSIGNED_END))
            continue;

        if (!dmi_pointing_device_test_ifaces_value(context, value))
            return false;
    }

    return true;
}

static bool dmi_pointing_device_test_ifaces_value(dmi_context_t *context, int value)
{
    struct {
        dmi_pointing_device_data_t data;
        dmi_word_t terminator;
    } envelope = {
        .data = {
            .header = {
                .type   = dmi_encode((dmi_byte_t)DMI_TYPE_POINTING_DEVICE),
                .length = dmi_encode((dmi_byte_t)sizeof(dmi_pointing_device_data_t)),
                .handle = dmi_encode(DMI_HANDLE_TEST)
            },
            .type         = 0,
            .interface    = dmi_encode((dmi_byte_t)value),
            .button_count = 0
        },
        .terminator = 0
    };

    dmi_entity_t *entity = dmi_entity_create(context, &envelope);
    if (entity == nullptr)
        return false;

    bool result = false;
    do {
        if (not dmi_entity_decode(entity))
            break;

        dmi_pointing_device_t *info = dmi_entity_info(entity, DMI_TYPE_POINTING_DEVICE);
        if (info == nullptr)
            break;

        if (info->interface != (typeof(info->interface))value)
            break;

        result = true;
    } while (0);

    dmi_entity_destroy(entity);

    return result;
}

static bool dmi_pointing_device_test_buttons(dmi_context_t *context)
{
    int value;

    for (value = 0; value < 16; value++) {
        if (!dmi_pointing_device_test_buttons_value(context, value))
            return false;
    }

    return true;
}

static bool dmi_pointing_device_test_buttons_value(dmi_context_t *context, int value)
{
    struct {
        dmi_pointing_device_data_t data;
        dmi_word_t terminator;
    } envelope = {
        .data = {
            .header = {
                .type   = dmi_encode((dmi_byte_t)DMI_TYPE_POINTING_DEVICE),
                .length = dmi_encode((dmi_byte_t)sizeof(dmi_pointing_device_data_t)),
                .handle = dmi_encode(DMI_HANDLE_TEST)
            },
            .type         = 0,
            .interface    = 0,
            .button_count = dmi_encode((dmi_byte_t)value)
        },
        .terminator = 0
    };

    dmi_entity_t *entity = dmi_entity_create(context, &envelope);
    if (entity == nullptr)
        return false;

    bool result = false;
    do {
        if (not dmi_entity_decode(entity))
            break;

        dmi_pointing_device_t *info = dmi_entity_info(entity, DMI_TYPE_POINTING_DEVICE);
        if (info == nullptr)
            break;

        if (info->button_count != (typeof(info->button_count))value)
            break;

        result = true;
    } while (0);

    dmi_entity_destroy(entity);

    return result;
}
