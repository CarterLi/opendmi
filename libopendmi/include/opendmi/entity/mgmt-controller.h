//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTITY_MGMT_CONTROLLER_H
#define OPENDMI_ENTITY_MGMT_CONTROLLER_H

#pragma once

#include <opendmi/entity.h>

/**
 * @brief Management protocol types.
 */
typedef enum dmi_mgmt_protocol {
    DMI_MGMT_PROTOCOL_IPMI            = 0x02, ///< IPMI: Intelligent Platform Management Interface
    DMI_MGMT_PROTOCOL_MCTP            = 0x03, ///< MCTP: Management Component Transport Protoco
    DMI_MGMT_PROTOCOL_REDFISH_OVER_IP = 0x04, ///< Redfish over IP
    DMI_MGMT_PROTOCOL_OEM             = 0xF0  ///< OEM-defined
} dmi_mgmt_protocol_t;

/**
 * @brief Management controller host interface entity specification.
 */
extern const dmi_entity_spec_t dmi_mgmt_controller_host_if_spec;

#endif // !OPENDMI_ENTITY_MGMT_CONTROLLER_H
