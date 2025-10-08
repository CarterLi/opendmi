//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_PROBE_H
#define OPENDMI_PROBE_H

#pragma once

/**
 * @brief Probe locations.
 */
enum dmi_probe_location
{
};

/**
 * @brief Probe status values.
 */
enum dmi_probe_status
{
    DMI_PROBE_STATUS_OTHER           = 0x01, //< Other
    DMI_PROBE_STATUS_UNKNOWN         = 0x02, //< Unknown
    DMI_PROBE_STATUS_OK              = 0x03, //< OK
    DMI_PROBE_STATUS_NON_CRITICAL    = 0x04, //< Non-critical
    DMI_PROBE_STATUS_CRITICAL        = 0x05, //< Critical
    DMI_PROBE_STATUS_NON_RECOVERABLE = 0x06, //< Non-recoverable
    __DMI_PROBE_STATUS_COUNT
};

#endif // !OPENDMI_PROBE_H
