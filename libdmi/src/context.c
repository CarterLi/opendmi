//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <string.h>
#include <stdlib.h>

#include <opendmi/context.h>
#include <opendmi/entry.h>
#include <opendmi/table.h>

#include <opendmi/table/firmware.h>
#include <opendmi/table/firmware-inventory.h>
#include <opendmi/table/firmware-language.h>
#include <opendmi/table/system.h>
#include <opendmi/table/system-boot.h>
#include <opendmi/table/system-config.h>
#include <opendmi/table/system-event-log.h>
#include <opendmi/table/system-reset.h>
#include <opendmi/table/baseboard.h>
#include <opendmi/table/chassis.h>
#include <opendmi/table/processor.h>
#include <opendmi/table/memory.h>
#include <opendmi/table/cache.h>
#include <opendmi/table/port.h>
#include <opendmi/table/slot.h>
#include <opendmi/table/onboard-device.h>
#include <opendmi/table/oem-strings.h>
#include <opendmi/table/system-config.h>
#include <opendmi/table/group-assoc.h>
#include <opendmi/table/system-event-log.h>
#include <opendmi/table/memory-array.h>
#include <opendmi/table/memory-device.h>
#include <opendmi/table/memory-error.h>
#include <opendmi/table/pointing-device.h>
#include <opendmi/table/battery.h>
#include <opendmi/table/probe.h>
#include <opendmi/table/cooler.h>

#include <opendmi/backend/dump.h>
#if defined(__linux__)
#include <opendmi/backend/linux.h>
#define DMI_BACKEND dmi_linux_backend
#elif defined(__APPLE__)
#include <opendmi/backend/darwin.h>
#define DMI_BACKEND dmi_darwin_backend
#elif defined(__FreeBSD__)
#include <opendmi/backend/freebsd.h>
#define DMI_BACKEND dmi_freebsd_backend
#elif defined(__WINNT__)
#include <opendmi/backend/windows.h>
#define DMI_BACKEND dmi_windows_backend
#else
#error "Unsupported OS type"
#endif

static bool dmi_open_ex(dmi_context_t *context, dmi_backend_t *backend, const void *arg);

/**
 * @internal
 * @brief Fixup DMI version number.
 */
static void dmi_version_fixup(dmi_context_t *context);

/**
 * @brief Last error code (thread-local).
 */
static __thread dmi_error_t dmi_last_error = DMI_OK;

/**
 * @brief Backend handle.
 */
static dmi_backend_t *dmi_backend = &DMI_BACKEND;

/**
 * @brief Predefined table specifications map.
 */
static const dmi_table_spec_t *dmi_table_specs[__DMI_TYPE_COUNT] =
{
    [DMI_TYPE_FIRMWARE]              = &dmi_firmware_table,
    [DMI_TYPE_SYSTEM]                = &dmi_system_table,
    [DMI_TYPE_BASEBOARD]             = &dmi_baseboard_table,
    [DMI_TYPE_CHASSIS]               = &dmi_chassis_table,
    [DMI_TYPE_PROCESSOR]             = &dmi_processor_table,
    [DMI_TYPE_MEMORY_CONTROLLER]     = &dmi_memory_controller_table,
    [DMI_TYPE_MEMORY_MODULE]         = &dmi_memory_module_table,
    [DMI_TYPE_CACHE]                 = &dmi_cache_table,
    [DMI_TYPE_PORT_CONNECTOR]        = &dmi_port_table,
    [DMI_TYPE_SYSTEM_SLOTS]          = &dmi_slot_table,
    [DMI_TYPE_ONBOARD_DEVICE]        = &dmi_onboard_device_table,
    [DMI_TYPE_OEM_STRINGS]           = &dmi_oem_strings_table,
    [DMI_TYPE_SYSTEM_CONFIG]         = &dmi_system_config_table,
    [DMI_TYPE_FIRMWARE_LANGUAGE]     = &dmi_firmware_language_table,
    [DMI_TYPE_GROUP_ASSOC]           = &dmi_group_assoc_table,
    [DMI_TYPE_SYSTEM_EVENT_LOG]      = &dmi_system_event_log_table,
    [DMI_TYPE_MEMORY_ARRAY]          = &dmi_memory_array_table,
    [DMI_TYPE_MEMORY_DEVICE]         = &dmi_memory_device_table,
    [DMI_TYPE_MEMORY_ERROR_32]       = &dmi_memory_error_32_table,
    [DMI_TYPE_MEMORY_ARRAY_ADDR]     = &dmi_memory_array_addr_table,
    [DMI_TYPE_MEMORY_DEVICE_ADDR]    = &dmi_memory_device_addr_table,
    [DMI_TYPE_POINTING_DEVICE]       = &dmi_pointing_device_table,
    [DMI_TYPE_PORTABLE_BATTERY]      = &dmi_battery_table,
    [DMI_TYPE_SYSTEM_RESET]          = &dmi_system_reset_table,
    // ..
    [DMI_TYPE_VOLTAGE_PROBE]         = &dmi_voltage_probe_table,
    [DMI_TYPE_COOLING_DEVICE]        = &dmi_cooler_table,
    [DMI_TYPE_TEMPERATURE_PROBE]     = &dmi_temperature_probe_table,
    [DMI_TYPE_CURRENT_PROBE]         = &dmi_current_probe_table,
    // ..
    [DMI_TYPE_SYSTEM_BOOT]           = &dmi_system_boot_table,
    // ..
    [DMI_TYPE_FIRMWARE_INVENTORY]    = &dmi_firmware_inventory_table
};

dmi_context_t *dmi_create(void)
{
    dmi_context_t *context = nullptr;

    // Allocate context descriptor
    context = malloc(sizeof(dmi_context_t));
    if (context == nullptr) {
        dmi_set_error(nullptr,  DMI_ERROR_OUT_OF_MEMORY);
        return nullptr;
    }

    // Initialize context
    memset(context, 0, sizeof(dmi_context_t));

    return context;
}

bool dmi_open(dmi_context_t *context)
{
    return dmi_open_ex(context, dmi_backend, nullptr);
}

bool dmi_dump_load(dmi_context_t *context, const char *path)
{
    if (path == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    dmi_info(context, "Loading DMI dump: %s...", path);

    return dmi_open_ex(context, &dmi_dump_backend, path);
}

bool dmi_dump_save(dmi_context_t *context, const char *path)
{
    if ((context == nullptr) || (path == nullptr)) {
        dmi_set_error(context, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    return true;
}

const dmi_table_spec_t *dmi_type_spec(dmi_context_t *context, dmi_type_t type)
{
    const dmi_table_spec_t *spec = nullptr;

    // TODO: Check bounds
    if (context != nullptr)
        spec = context->type_map[type];
    
    if (spec == nullptr)
        spec = dmi_table_specs[type];

    return spec;
}

bool dmi_set_logger(dmi_context_t *context, dmi_log_handler_t logger)
{
    if (context == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    context->logger = logger;

    return true;
}

void dmi_set_error(dmi_context_t *context, dmi_error_t error)
{
    if (context != nullptr)
        context->last_error = error;
    else
        dmi_last_error = error;
}

dmi_error_t dmi_get_error(const dmi_context_t *context)
{
    if (context == nullptr)
        return dmi_last_error;

    return context->last_error;
}

bool dmi_close(dmi_context_t *context)
{
    if (context == nullptr) {
        dmi_set_error(nullptr, DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }

    dmi_registry_destroy(context->registry);

    if (context->backend) {
        if (context->session != nullptr)
            context->backend->close(context);
    }

    memset(context, 0, sizeof(*context));

    return true;
}

void dmi_destroy(dmi_context_t *context)
{
    if (context == nullptr)
        return;

    // Close and free context
    dmi_close(context);
    free(context);
}

static bool dmi_open_ex(dmi_context_t *context, dmi_backend_t *backend, const void *arg)
{
    if (context == nullptr) {
        dmi_set_error(nullptr,  DMI_ERROR_INVALID_ARGUMENT);
        return false;
    }
    if ((context->backend != nullptr) || (context->session != nullptr)) {
        dmi_set_error(nullptr,  DMI_ERROR_INVALID_STATE);
        return false;
    }

    dmi_info(context, "Opening DMI context...");
    dmi_info(context, "Using backend: %s", backend->name);

    // Initialize context
    bool success = false;
    do {
        context->backend = backend;

        // Initialize backend
        if (!context->backend->open(context, arg)) {
            dmi_error(context, "Unable to open backend: %s", dmi_error_message(context->last_error));
            break;
        }

        // Read and decode entry point
        dmi_info(context, "Reading DMI entry point...");
        context->entry_data = context->backend->read_entry(context, &context->entry_size);
        if (context->entry_data == nullptr)
            break;
        if (!dmi_entry_decode(context, context->entry_data, context->entry_size))
            break;

        // Fixup SMBIOS version number
        dmi_version_fixup(context);
        dmi_info(context, "SMBIOS %u.%u.%u present",
                 dmi_version_major(context->smbios_version),
                 dmi_version_minor(context->smbios_version),
                 dmi_version_revision(context->smbios_version));

        // Read and decode SMBIOS tables
        // TODO: Use separate variable for size
        dmi_info(context, "Reading DMI tables...");
        context->table_data = context->backend->read_tables(context, &context->table_area_size);
        if (context->table_data == nullptr)
            break;

        // Create registry
        dmi_info(context, "Initializing registry...");
        context->registry = dmi_registry_create(context, 0);
        if (!context->registry)
            break;

        success = true;
    } while (false);

    if (!success) {
        dmi_error(context, "Unable to open DMI context");
        dmi_set_error(context, context->last_error);
        dmi_close(context);
    }

    return success;
}

static void dmi_version_fixup(dmi_context_t *context)
{
    unsigned int major    = dmi_version_major(context->smbios_version);
    unsigned int minor    = dmi_version_minor(context->smbios_version);
    unsigned int revision = dmi_version_revision(context->smbios_version);

    if (major != 2)
        return;

    // Some BIOS report weird SMBIOS version, fix that up
    switch (minor) {
    case 0x1F:
    case 0x21:
        minor = 3;
        break;

    case 0x33:
        minor = 6;
        break;

    default:
        return;
    }

    context->smbios_version = dmi_version(major, minor, revision);
}
