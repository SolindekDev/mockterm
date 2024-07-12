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

#include <mk_core.h>
#include <mk_main.h>

#include <mk_config.h>
#include <mk_input.h>
#include <mk_display.h>
#include <mk_font.h>

mockterm_window_properties_t window_prop = {
    .title  = MOCKTERM_WINDOW_TITLE,
    .width  = MOCKTERM_WINDOW_COLUMNS * MOCKTERM_WINDOW_COLUMN_SIZE,
    .height = MOCKTERM_WINDOW_ROWS * MOCKTERM_WINDOW_ROW_SIZE,
};

int 
main(int argc, char** argv)
{
    mockterm_display_t* display = mk_display_init();

    printf("font name: %s\n", MOCKTERM_FONT_NAME);
    mk_font_find_path(MOCKTERM_FONT_NAME);

    mk_display_create_window(display, window_prop);
    mk_display_attach_colors(display);
    mk_display_run(display);
}