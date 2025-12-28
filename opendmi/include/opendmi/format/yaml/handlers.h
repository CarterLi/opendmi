//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_YAML_HANDLERS_H
#define OPENDMI_FORMAT_YAML_HANDLERS_H

#pragma once

#include <opendmi/format/yaml/types.h>

__BEGIN_DECLS

void *dmi_yaml_initialize(dmi_context_t *context, FILE *stream);

bool dmi_yaml_dump_start(void *asession);
bool dmi_yaml_entry(void *asession);
bool dmi_yaml_table_start(void *asession);
bool dmi_yaml_entity_start(void *asession, const dmi_entity_t *entity);

bool dmi_yaml_entity_attr(
        void                  *asession,
        const dmi_entity_t     *entity,
        const dmi_attribute_t *attr,
        const void            *data);

bool dmi_yaml_entity_data(void *asession, const dmi_entity_t *entity);
bool dmi_yaml_entity_strings(void *asession, const dmi_entity_t *entity);
bool dmi_yaml_entity_end(void *asession, const dmi_entity_t *entity);
bool dmi_yaml_table_end(void *asession);
bool dmi_yaml_dump_end(void *asession);

void dmi_yaml_finalize(void *asession);

__END_DECLS

#endif // !OPENDMI_FORMAT_YAML_HANDLERS_H
