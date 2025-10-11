//
// OpenDMI: DMI/SMBIOS library
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
    [DMI_TYPE_SYS_CHASSIS]             = "System enclosure or chassis",
    [DMI_TYPE_PROCESSOR]               = "Processor information",
    [DMI_TYPE_MEM_CONTROLLER]          = "Memory controller information",
    [DMI_TYPE_MEM_MODULE]              = "Memory module information",
    [DMI_TYPE_CACHE]                   = "Cache information",
    [DMI_TYPE_PORT_CONNECTOR]          = "Port connector information",
    [DMI_TYPE_SYS_SLOTS]               = "System slots",
    [DMI_TYPE_ONBOARD_DEVICE]          = "Onboard devices information",
    [DMI_TYPE_OEM_STRINGS]             = "OEM strings",
    [DMI_TYPE_SYS_CONFIG_OPTIONS]      = "System configuration options",
    [DMI_TYPE_FIRMWARE_LANGUAGE]       = "Firmware language information",
    [DMI_TYPE_GROUP_ASSOC]             = "Group associations",
    [DMI_TYPE_SYS_EVENT_LOG]           = "System event log",
    [DMI_TYPE_MEM_ARRAY]               = "Physical memory array",
    [DMI_TYPE_MEM_DEVICE]              = "Memory device",
    [DMI_TYPE_MEM_ERROR_32]            = "32-bit memory error information",
    [DMI_TYPE_MEM_ARRAY_MAPPED_ADDR]   = "Memory array mapped address",
    [DMI_TYPE_MEM_DEVICE_MAPPED_ADDR]  = "Memory device mapped address",
    [DMI_TYPE_POINTING_DEVICE]         = "Built-in pointing device",
    [DMI_TYPE_PORTABLE_BATTERY]        = "Portable battery",
    [DMI_TYPE_SYS_RESET]               = "System reset",
    [DMI_TYPE_HARDWARE_SECURITY]       = "Hardware security",
    [DMI_TYPE_SYS_POWER_CONTROLS]      = "System power controls",
    [DMI_TYPE_VOLTAGE_PROBE]           = "Voltage probe",
    [DMI_TYPE_COOLING_DEVICE]          = "Cooling device",
    [DMI_TYPE_TEMPERATURE_PROBE]       = "Temperature probe",
    [DMI_TYPE_CURRENT_PROBE]           = "Electrical current probe",
    [DMI_TYPE_OOB_REMOTE_ACCESS]       = "Out-of-band remote access",
    [DMI_TYPE_BIS_ENTRY_POINT]         = "Boot Integrity Services (BIS) entry point",
    [DMI_TYPE_SYS_BOOT]                = "System boot information",
    [DMI_TYPE_MEM_ERROR_64]            = "64-bit memory error information",
    [DMI_TYPE_MGMT_DEVICE]             = "Management device",
    [DMI_TYPE_MGMT_DEVICE_COMPONENT]   = "Management device component",
    [DMI_TYPE_MGMT_DEVICE_THRESHOLD]   = "Management device threshold data",
    [DMI_TYPE_MEM_CHANNEL]             = "Memory channel",
    [DMI_TYPE_IPMI_DEVICE]             = "IPMI device information",
    [DMI_TYPE_SYS_POWER_SUPPLY]        = "System power supply",
    [DMI_TYPE_ADDITIONAL_INFO]         = "Additional information",
    [DMI_TYPE_ONBOARD_DEVICE_EX]       = "Onboard devices extended information",
    [DMI_TYPE_MGMT_CONTROLLER_HOST_IF] = "Management controller host information",
    [DMI_TYPE_TPM_DEVICE]              = "TPM device",
    [DMI_TYPE_PROCESSOR_EX]            = "Processor additional information",
    [DMI_TYPE_FIRMWARE_INVENTORY]      = "Firmware inventory information",
    [DMI_TYPE_STRING_PROPERTY]         = "String property",

    [DMI_TYPE_INACTIVE]     = "Inactive",
    [DMI_TYPE_END_OF_TABLE] = "End of table",

    [DMI_TYPE_INTEL_RSD_NIC]                 = "Intel: RSD NIC information",
    [DMI_TYPE_INTEL_RSD_PCIE]                = "Intel: RSD PCIe information",
    [DMI_TYPE_INTEL_RSD_PROCESSOR_CPUID]     = "Intel: RSD Processor CPUID information",
    [DMI_TYPE_INTEL_RSD_STORAGE_DEVICE]      = "Intel: RSD Storage device information",
    [DMI_TYPE_INTRL_RSD_TPM]                 = "Intel: RSD TPM information",
    [DMI_TYPE_INTEL_RSD_TXT]                 = "Intel: RSD Trusted Execution Technology (TXT) information",
    [DMI_TYPE_INTEL_RSD_MEMORY_DEVICE_EX]    = "Intel: RSD Memory device extended information",
    [DMI_TYPE_INTEL_RSD_FPGA]                = "Intel: RSD Field-Programmable Gate Array (FPGA) information",
    [DMI_TYPE_INTEL_RSD_CABLED_PCIE]         = "Intel: RSD Cabled PCIe port information",
    [DMI_TYPE_INTEL_RSD_PHYS_DEVICE_MAPPING] = "Intel: RSD SMBIOS Physical device mapping",

    [DMI_TYPE_DELL_INDEXED_IO]        = "Dell: Indexed IO",
	[DMI_TYPE_DELL_PROTECTED_AREA_1]  = "Dell: Protected Area Type 1",
	[DMI_TYPE_DELL_PROTECTED_AREA_2]  = "Dell: Protected Area Type 2",
	[DMI_TYPE_DELL_CALLING_INTERFACE] = "Dell: Calling interface"
};

const char *dmi_type_name(dmi_type_t value)
{
    const char *name = dmi_name(dmi_type_names, value, __DMI_TYPE_COUNT);

    if (name == nullptr)
        name = value > 0x7F ? "OEM-specific" : "Unknown";

    return name;
}
