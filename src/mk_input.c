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

bool
mk_input_key_codes(mockterm_display_t* display, SDL_Event event)
{
    unsigned int keysym = event.key.keysym.sym;

    if (keysym == SDLK_BACKSPACE)
    {
        write(display->terminal->master_fd, "\x7f", 1); 
        return true;
    }
    else if (keysym == SDLK_RETURN) 
    {
        write(display->terminal->master_fd, "\n", 1);
        return true;
    }
    else if (keysym == SDLK_TAB)
    {
        write(display->terminal->master_fd, "\t", 1); 
        return true;
    }
    else if (keysym == SDLK_ESCAPE) 
    {
        write(display->terminal->master_fd, "\x1b", 1);
        return true;
    }
}

bool
mk_events_input(mockterm_display_t* display)
{
    SDL_Event event; 
 
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_QUIT:
                display->win_loop = true;
                return false;
                break;
            case SDL_TEXTINPUT:
                // display->input_size += 1;
                // display->input = realloc(display->input, display->input_size + 2);
                strcat(display->input, event.text.text);
                write(display->terminal->master_fd, event.text.text, strlen(event.text.text));
                return true;
            case SDL_KEYDOWN:
                return mk_input_key_codes(display, event);;
            default:
                break;
        }
    }

    return false;
}