//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MGMT_DEVICE_COMPONENT_H
#define OPENDMI_ENTITY_MGMT_DEVICE_COMPONENT_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_mgmt_device_component_data dmi_mgmt_device_component_data_t;

/**
 * @brief Management device component structure (type 35).
 */
DMI_PACKED_STRUCT(dmi_mgmt_device_component_data)
{
    /**
     * @brief SMBIOS structure header.
     */
    dmi_header_t header;

    /**
     * @brief Number of the string that contains additional descriptive
     * information about the component.
     */
    dmi_string_t description;

    /**
     * @brief Handle, or instance number, of the management device that
     * contains this component.
     */
    dmi_handle_t device_handle;

    /**
     * @brief Handle, or instance number, of the probe or cooling device that
     * defines this component.
     */
    dmi_handle_t component_handle;

    /**
     * @brief Handle, or instance number, associated with the device
     * thresholds.
     */
    dmi_handle_t threshold_handle;
};

typedef struct dmi_mgmt_device_component dmi_mgmt_device_component_t;

struct dmi_mgmt_device_component
{
    /**
     * @brief String that contains additional descriptive information about
     * the component.
     */
    const char *description;

    /**
     * @brief Handle, or instance number, of the management device that
     * contains this component.
     */
    dmi_handle_t device_handle;

    /**
     * @brief Reference to the management device that contains this component.
     */
    dmi_entity_t *device;

    /**
     * @brief Handle, or instance number, of the probe or cooling device that
     * defines this component.
     */
    dmi_handle_t component_handle;

    /**
     * @brief Reference to the probe or cooling device that defines this
     * component.
     */
    dmi_entity_t *component;

    /**
     * @brief Handle, or instance number, associated with the device
     * thresholds.
     */
    dmi_handle_t threshold_handle;

    /**
     * @brief Reference to the device thresholds structure.
     */
    dmi_entity_t *threshold;
};

/**
 * @brief Manangement device component entity specification.
 */
extern const dmi_entity_spec_t dmi_mgmt_device_component_spec;

__BEGIN_DECLS

/**
 * @internal
 */
dmi_mgmt_device_component_t *dmi_mgmt_device_component_decode(const dmi_entity_t *entity, dmi_version_t *plevel);

/**
 * @internal
 */
bool dmi_mgmt_device_component_link(dmi_entity_t *entity);

/**
 * @internal
 */
void dmi_mgmt_device_component_free(dmi_mgmt_device_component_t *info);

__END_DECLS

#endif // !OPENDMI_ENTITY_MGMT_DEVICE_COMPONENT_H
