//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_YAML_HELPERS_H
#define OPENDMI_FORMAT_YAML_HELPERS_H

#pragma once

#include <opendmi/format/yaml/types.h>

__BEGIN_DECLS

bool dmi_yaml_label(dmi_yaml_session_t *session, const char *value);
bool dmi_yaml_scalar(dmi_yaml_session_t *session, const char *value, yaml_scalar_style_t style);

bool dmi_yaml_sequence_start(dmi_yaml_session_t *session, yaml_sequence_style_t style);
bool dmi_yaml_sequence_end(dmi_yaml_session_t *session);

bool dmi_yaml_mapping_start(dmi_yaml_session_t *session, yaml_mapping_style_t style);
bool dmi_yaml_mapping_end(dmi_yaml_session_t *session);

__END_DECLS

#endif // !OPENDMI_FORMAT_YAML_HELPERS_H
