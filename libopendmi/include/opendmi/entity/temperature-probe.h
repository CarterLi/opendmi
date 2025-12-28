//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_TEMPERATURE_PROBE_H
#define OPENDMI_ENTITY_TEMPERATURE_PROBE_H

#pragma once

#include <opendmi/entity/probe.h>

typedef struct dmi_probe dmi_temperature_probe_t;

/**
 * @brief Temperature probe entity specification.
 */
extern const dmi_entity_spec_t dmi_temperature_probe_spec;

#endif // !OPENDMI_ENTITY_TEMPERATURE_PROBE_H
