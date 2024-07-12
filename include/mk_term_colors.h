/*
 *  Mockterm - terminal emulator for unix-like systems
 *  Copyright (C) 2024 SolindekDev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef MOCKTERM_TERM_COLORS_h
#define MOCKTERM_TERM_COLORS_h

#include <mk_core.h>

#define HEX_TO_RGB(hex)                                                                       \
    (unsigned char)(((hex >> 16) & 0xFF) / 255), (unsigned char)(((hex >> 8) & 0xFF) / 255),  \
    (unsigned char)(((hex      ) & 0xFF) / 255),                                        255   \


typedef struct __mockterm_window_colors_t {
    unsigned long background;
    unsigned long foreground;

    unsigned long black;
    unsigned long red;
    unsigned long green;
    unsigned long yellow;
    unsigned long blue;
    unsigned long magenta;
    unsigned long cyan;
    unsigned long white;
} mockterm_window_colors_t;

#endif /* MOCKTERM_DISPLAY */