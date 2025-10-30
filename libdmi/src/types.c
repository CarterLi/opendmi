//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/utils.h>

static const char *dmi_type_names[__DMI_TYPE_COUNT] =
{
    [DMI_TYPE_FIRMWARE]                = "Platform firmware information",
    [DMI_TYPE_SYSTEM]                  = "System information",
    [DMI_TYPE_BASEBOARD]               = "Baseboard or module information",
    [DMI_TYPE_CHASSIS]                 = "System enclosure or chassis",
    [DMI_TYPE_PROCESSOR]               = "Processor information",
    [DMI_TYPE_MEMORY_CONTROLLER]       = "Memory controller information",
    [DMI_TYPE_MEMORY_MODULE]           = "Memory module information",
    [DMI_TYPE_CACHE]                   = "Cache information",
    [DMI_TYPE_PORT_CONNECTOR]          = "Port connector information",
    [DMI_TYPE_SYSTEM_SLOTS]            = "System slots",
    [DMI_TYPE_ONBOARD_DEVICE]          = "Onboard devices information",
    [DMI_TYPE_OEM_STRINGS]             = "OEM strings",
    [DMI_TYPE_SYSTEM_CONFIG_OPTIONS]   = "System configuration options",
    [DMI_TYPE_FIRMWARE_LANGUAGE]       = "Firmware language information",
    [DMI_TYPE_GROUP_ASSOC]             = "Group associations",
    [DMI_TYPE_SYSTEM_EVENT_LOG]        = "System event log",
    [DMI_TYPE_MEMORY_ARRAY]            = "Physical memory array",
    [DMI_TYPE_MEMORY_DEVICE]           = "Memory device",
    [DMI_TYPE_MEMORY_ERROR_32]         = "32-bit memory error information",
    [DMI_TYPE_MEMORY_ARRAY_ADDR]       = "Memory array mapped address",
    [DMI_TYPE_MEMORY_DEVICE_ADDR]      = "Memory device mapped address",
    [DMI_TYPE_POINTING_DEVICE]         = "Built-in pointing device",
    [DMI_TYPE_PORTABLE_BATTERY]        = "Portable battery",
    [DMI_TYPE_SYSTEM_RESET]            = "System reset",
    [DMI_TYPE_HARDWARE_SECURITY]       = "Hardware security",
    [DMI_TYPE_SYSTEM_POWER_CONTROLS]   = "System power controls",
    [DMI_TYPE_VOLTAGE_PROBE]           = "Voltage probe",
    [DMI_TYPE_COOLING_DEVICE]          = "Cooling device",
    [DMI_TYPE_TEMPERATURE_PROBE]       = "Temperature probe",
    [DMI_TYPE_CURRENT_PROBE]           = "Electrical current probe",
    [DMI_TYPE_OOB_REMOTE_ACCESS]       = "Out-of-band remote access",
    [DMI_TYPE_BIS_ENTRY_POINT]         = "Boot Integrity Services (BIS) entry point",
    [DMI_TYPE_SYSTEM_BOOT]             = "System boot information",
    [DMI_TYPE_MEMORY_ERROR_64]         = "64-bit memory error information",
    [DMI_TYPE_MGMT_DEVICE]             = "Management device",
    [DMI_TYPE_MGMT_DEVICE_COMPONENT]   = "Management device component",
    [DMI_TYPE_MGMT_DEVICE_THRESHOLD]   = "Management device threshold data",
    [DMI_TYPE_MEMORY_CHANNEL]          = "Memory channel",
    [DMI_TYPE_IPMI_DEVICE]             = "IPMI device information",
    [DMI_TYPE_SYSTEM_POWER_SUPPLY]     = "System power supply",
    [DMI_TYPE_ADDITIONAL_INFO]         = "Additional information",
    [DMI_TYPE_ONBOARD_DEVICE_EX]       = "Onboard devices extended information",
    [DMI_TYPE_MGMT_CONTROLLER_HOST_IF] = "Management controller host information",
    [DMI_TYPE_TPM_DEVICE]              = "TPM device",
    [DMI_TYPE_PROCESSOR_EX]            = "Processor additional information",
    [DMI_TYPE_FIRMWARE_INVENTORY]      = "Firmware inventory information",
    [DMI_TYPE_STRING_PROPERTY]         = "String property",
    [DMI_TYPE_INACTIVE]                = "Inactive",
    [DMI_TYPE_END_OF_TABLE]            = "End of table",
};

const char *dmi_type_name(dmi_type_t value)
{
    const char *name = dmi_name(dmi_type_names, value, __DMI_TYPE_COUNT);

    if (name == nullptr)
        name = value > 0x7F ? "OEM-specific" : "Unknown";

    return name;
}
