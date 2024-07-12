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
#include <mk_input.h>
#include <mk_display.h>

void
mk_events_input(mockterm_display_t* display)
{
    SDL_Event event;
 
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_QUIT:
                display->win_loop = true;
                break;
            default:
                break;
        }
    }
}