//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/system-event-log.h>

const dmi_attribute_t dmi_system_event_log_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_system_event_log_table =
{
    .code        = "system-event-log",
    .name        = "System event log",
    .type        = DMI_TYPE_SYSTEM_EVENT_LOG,
    .min_version = DMI_VERSION(2, 0, 0),
    .min_length  = 0x14,
    .attributes  = dmi_system_event_log_attrs
};
