//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_FORMAT_XML_HANDLERS_H
#define OPENDMI_FORMAT_XML_HANDLERS_H

#pragma once

#include <opendmi/format/xml/types.h>

__BEGIN_DECLS

void *dmi_xml_initialize(dmi_context_t *context, FILE *stream);

bool dmi_xml_dump_start(void *asession);
bool dmi_xml_entry(void *asession);
bool dmi_xml_entity_start(void *asession, const dmi_entity_t *entity);
bool dmi_xml_entity_attrs_start(void *asession, const dmi_entity_t *entity);

bool dmi_xml_entity_attr(
        void                  *asession,
        const dmi_entity_t     *entity,
        const dmi_attribute_t *attr,
        const void            *data);

bool dmi_xml_entity_attr_array(
        void                  *asession,
        const dmi_attribute_t *attr,
        const dmi_data_t      *info,
        const void            *value);

bool dmi_xml_entity_attr_struct(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value);

bool dmi_xml_entity_attr_value(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value);

bool dmi_xml_entity_attr_set(
        void                  *asession,
        const dmi_attribute_t *attr,
        const void            *value);

bool dmi_xml_entity_attrs_end(void *asession, const dmi_entity_t *entity);
bool dmi_xml_entity_data(void *asession, const dmi_entity_t *entity);
bool dmi_xml_entity_strings(void *asession, const dmi_entity_t *entity);
bool dmi_xml_entity_end(void *asession, const dmi_entity_t *entity);
bool dmi_xml_dump_end(void *asession);

void dmi_xml_finalize(void *asession);

__END_DECLS

#endif // !OPENDMI_FORMAT_XML_HANDLERS_H
