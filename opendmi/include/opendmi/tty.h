//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_TTY_H
#define OPENDMI_TTY_H

#pragma once

#include <opendmi/defs.h>

/**
 * @brief Xterm system colors.
 */
typedef enum dmi_color
{
    DMI_COLOR_BLACK   = 0,
    DMI_COLOR_MAROON  = 1,
    DMI_COLOR_GREEN   = 2,
    DMI_COLOR_OLIVE   = 3,
    DMI_COLOR_NAVY    = 4,
    DMI_COLOR_PURPLE  = 5,
    DMI_COLOR_TEAL    = 6,
    DMI_COLOR_SILVER  = 7,
    DMI_COLOR_GREY    = 8,
    DMI_COLOR_RED     = 9,
    DMI_COLOR_LIME    = 10,
    DMI_COLOR_YELLOW  = 11,
    DMI_COLOR_BLUE    = 12,
    DMI_COLOR_FUCHSIA = 13,
    DMI_COLOR_AQUA    = 14,
    DMI_COLOR_WHITE   = 15
} dmi_color_t;

__BEGIN_DECLS

void dmi_tty_init(void);
bool dmi_has_tty(void);

void dmi_tty_attr_on(int attrs);
void dmi_tty_attr_off(int attrs);
void dmi_tty_set_fg_color(dmi_color_t color);
void dmi_tty_set_bg_color(dmi_color_t color);

void dmi_tty_cprintf(int color, const char *format, ...);

void dmi_tty_exit_attr_mode(void);

__END_DECLS

#endif // !OPENDMI_TTY_H
