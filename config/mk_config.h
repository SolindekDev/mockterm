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

#ifndef MOCKTERM_CONFIG
#define MOCKTERM_CONFIG


/* ===============================
 *  MOCKTERM - Window properties
 * ===============================
 */

#define MOCKTERM_WINDOW_TITLE "Mockterm"

#define MOCKTERM_WINDOW_COLUMNS (80)
#define MOCKTERM_WINDOW_ROWS    (48)

#define MOCKTERM_WINDOW_COLUMN_SIZE 16
#define MOCKTERM_WINDOW_ROW_SIZE    16

#define MOCKTERM_WINDOW_MARGIN_LEFT   12
#define MOCKTERM_WINDOW_MARGIN_RIGHT  12
#define MOCKTERM_WINDOW_MARGIN_TOP    12
#define MOCKTERM_WINDOW_MARGIN_BOTTOM 12


/* ===============================
 *  MOCKTERM - Terminal colors
 * ===============================
 */

#define MOCKTERM_COLORS_BACKGROUND 0x1A1D23FF
#define MOCKTERM_COLORS_FOREGROUND 0x9B9FA9FF

#define MOCKTERM_COLORS_BLACK   0x111317FF
#define MOCKTERM_COLORS_RED     0xF8747EFF
#define MOCKTERM_COLORS_GREEN   0x75AD47FF
#define MOCKTERM_COLORS_YELLOW  0xD09214FF
#define MOCKTERM_COLORS_BLUE    0x50A4E9FF
#define MOCKTERM_COLORS_MAGENTA 0xCC83E3FF
#define MOCKTERM_COLORS_CYAN    0x00B298FF
#define MOCKTERM_COLORS_WHITE   0xADB0BBFF

/* ===============================
 *  MOCKTERM - Terminal Font
 * ===============================
 */

/* Font should be in .ttf extension in directories:
 *  - "/usr/share/fonts", 
 *  - "/usr/local/share/fonts", 
 */
#define MOCKTERM_FONT_NAME "Terminus"

#endif /* MOCKTERM_CONFIG */