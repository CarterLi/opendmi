//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_BACKEND_H
#define OPENDMI_BACKEND_H

#pragma once

#include <opendmi/types.h>

#ifndef DMI_BACKEND_T
#define DMI_BACKEND_T
typedef struct dmi_backend dmi_backend_t;
#endif // !DMI_BACKEND_T

/**
 * @brief DMI backend specification.
 */
struct dmi_backend
{
    /**
     * @brief Backend name.
     */
    char *name;

    bool (*open)(dmi_context_t *context, const void *arg);
    dmi_data_t *(*read_entry)(dmi_context_t *context, size_t *plength);
    dmi_data_t *(*read_tables)(dmi_context_t *context, size_t *plength);
    bool (*close)(dmi_context_t *context);
};

#endif // !OPENDMI_BACKEND_H
