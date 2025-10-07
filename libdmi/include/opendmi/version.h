//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_VERSION_H
#define OPENDMI_VERSION_H

#pragma once

/**
 * @brief SMBIOS version number.
 */
typedef unsigned int dmi_version_t;

/**
 * @brief Construct SMBIOS version number from its components.
 *
 * @param major Major version number.
 * @param minor Minor version number.
 * @param patch Patch version number.
 *
 * @return Version number.
 */
static inline dmi_version_t dmi_version(unsigned int major,
                                        unsigned int minor,
                                        unsigned int patch)
{
    return ((major & 0xFFU) << 16) | ((minor & 0xFFU) << 8) | (patch & 0xFFU);
}

/**
 * @brief Get major component of SMBIOS version number.
 *
 * @param version Version number.
 * @return Major version number.
 */
static inline unsigned int dmi_version_major(dmi_version_t version)
{
    return (version & 0xFF0000U) >> 16;
}

/**
 * @brief Get minor component of SMBIOS version number.
 *
 * @param version Version number.
 * @return Minor version number.
 */
static inline unsigned int dmi_version_minor(dmi_version_t version)
{
    return (version & 0x00FF00U) >> 8;
}

/**
 * @brief Get patch component of SMBIOS version number.
 *
 * @param version Version number.
 * @return Patch version number.
 */
static inline unsigned int dmi_version_patch(dmi_version_t version)
{
    return version & 0x0000FFU;
}

#endif // !OPENDMI_VERSION_H
