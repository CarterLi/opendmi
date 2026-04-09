//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_MODULE_H
#define OPENDMI_MODULE_H

#pragma once

#include <opendmi/entity.h>

typedef struct dmi_module dmi_module_t;

/**
 * @brief DMI extension module.
 */
struct dmi_module
{
    const char *code;
    const char *name;
    const dmi_entity_spec_t **entities;
    dmi_module_t *next;
};

extern dmi_module_t *dmi_modules;

__BEGIN_DECLS

/**
 * @brief Registers an extension module in the global module registry.
 *
 * Prepends @p module to the global `dmi_modules` linked list via its `next`
 * field. The module must remain valid for the lifetime of the program; it is
 * not copied. Modules are typically statically allocated and registered from a
 * constructor function.
 *
 * @param module Extension module to register; must not be @c NULL.
 */
void dmi_module_register(dmi_module_t *module);

/**
 * @brief Looks up a registered extension module by its code.
 *
 * Searches the global `dmi_modules` list for the first module whose `code`
 * field equals @p code.
 *
 * @param code Null-terminated module identifier string; must not be @c NULL.
 * @return Pointer to the matching module, or @c NULL if no module with the
 *         given code is registered.
 */
const dmi_module_t *dmi_module_find(const char *code);

__END_DECLS

#endif // !OPENDMI_MODULE_H
