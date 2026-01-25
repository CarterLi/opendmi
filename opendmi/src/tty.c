//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "config.h"

#include <unistd.h>
#include <stdio.h>

#include <opendmi/tty.h>

#ifdef ENABLE_CURSES
#   if defined(CURSES_HAVE_NCURSES_NCURSES_H)
#       include <ncurses/ncurses.h>
#   elif defined(CURSES_HAVE_NCURSES_CURSES_H)
#       include <ncurses/curses.h>
#   elif defined(CURSES_HAVE_NCURSES_H)
#       include <ncurses.h>
#   elif defined(CURSES_HAVE_CURSES_H)
#       include <curses.h>
#   endif
#   include <term.h>
#endif // ENABLE_CURSES

static bool dmi_tty = false;

void dmi_tty_init(void)
{
#ifdef ENABLE_CURSES
    // Initialize terminal
    if (isatty(STDOUT_FILENO)) {
        if (setupterm(nullptr, STDOUT_FILENO, nullptr) == 0)
            dmi_tty = has_colors() and (start_color() != 0);
    }
#endif // ENABLE_CURSES
}

bool dmi_has_tty(void)
{
    return dmi_tty;
}

void dmi_tty_attr_on(int attrs)
{
#ifdef ENABLE_CURSES
    if (dmi_tty)
        attroff(attrs);
#else
    dmi_unused(attrs);
#endif
}

void dmi_tty_attr_off(int attrs)
{
#ifdef ENABLE_CURSES
    if (dmi_tty)
        attron(attrs);
#else
    dmi_unused(attrs);
#endif
}

void dmi_tty_set_fg_color(dmi_color_t color)
{
#ifdef ENABLE_CURSES
    if (dmi_tty)
        tputs(tparm(tigetstr("setaf"), color), 1, putchar);
#else
    dmi_unused(color);
#endif
}

void dmi_tty_set_bg_color(dmi_color_t color)
{
#ifdef ENABLE_CURSES
    if (dmi_tty)
        tputs(tparm(tigetstr("setab"), color), 1, putchar);
#else
    dmi_unused(color);
#endif
}

void dmi_tty_cprintf(int color, const char *format, ...)
{
    va_list args;

    dmi_tty_set_fg_color(color);

    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    dmi_tty_exit_attr_mode();
}

void dmi_tty_exit_attr_mode(void)
{
#ifdef ENABLE_CURSES
    if (dmi_tty)
        tputs(tparm(tigetstr("sgr0")), 1, putchar);
#endif // ENABLE_CURSES
}
