//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_VOLTAGE_PROBE_H
#define OPENDMI_ENTITY_VOLTAGE_PROBE_H

#pragma once

#include <opendmi/entity/probe.h>

#ifndef DMI_VOLTAGE_PROBE_T
#define DMI_VOLTAGE_PROBE_T
typedef struct dmi_probe dmi_voltage_probe_t;
#endif // !DMI_VOLTAGE_PROBE_T

/**
 * @brief Voltage probe entity specification.
 */
extern const dmi_entity_spec_t dmi_voltage_probe_spec;

#endif // !OPENDMI_ENTITY_VOLTAGE_PROBE_H
