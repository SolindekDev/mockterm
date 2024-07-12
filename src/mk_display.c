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
#include <mk_display.h>

#include <mk_config.h>
#include <mk_input.h>
#include <mk_msg.h>

void
mk_display_init_libraries()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        MK_ERROR("failed to initialize SDL");

    if (TTF_Init() != 0)
        MK_ERROR("failed to initialize SDL TTF");

    MK_DEBUG("successfully initialized all SDL libraries");
}

mockterm_display_t* 
mk_display_init()
{
    mk_display_init_libraries();

    mockterm_display_t* display = calloc(1, sizeof(mockterm_display_t));
    if (display == NULL)
        MK_ERROR("couldn't allocate memory for mockterm_display_t");

    return display;
}

void 
mk_display_create_window(mockterm_display_t* display, 
                         mockterm_window_properties_t properties)
{
    display->sdl_window   = SDL_CreateWindow(properties.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                             properties.width  + MOCKTERM_WINDOW_MARGIN_LEFT + MOCKTERM_WINDOW_MARGIN_RIGHT, 
                                             properties.height + MOCKTERM_WINDOW_MARGIN_TOP  + MOCKTERM_WINDOW_MARGIN_BOTTOM, 0x00);
    display->sdl_renderer = SDL_CreateRenderer(display->sdl_window, -1, 0);

    display->win_loop   = false;
    display->win_frames = 0;
    display->win_fps    = 0;

    display->win_prop   = calloc(1, sizeof(mockterm_window_properties_t));
    memcpy(display->win_prop, &properties, sizeof(mockterm_window_properties_t));
}

void 
mk_display_clear(mockterm_display_t* display)
{
    SDL_SetRenderDrawColor(display->sdl_renderer, (display->win_colors->background >> 24) & 0xFF, (display->win_colors->background >> 16) & 0xFF,
                                                  (display->win_colors->background >> 8) & 0xFF ,  display->win_colors->background & 0xFF);
    SDL_RenderClear(display->sdl_renderer);
}

void 
mk_display_attach_colors(mockterm_display_t* display)
{
    display->win_colors   = calloc(1, sizeof(mockterm_window_colors_t));
    display->win_colors->background = MOCKTERM_COLORS_BACKGROUND;
    display->win_colors->foreground = MOCKTERM_COLORS_FOREGROUND;

    display->win_colors->black   = MOCKTERM_COLORS_BLACK;
    display->win_colors->red     = MOCKTERM_COLORS_RED;
    display->win_colors->green   = MOCKTERM_COLORS_GREEN;
    display->win_colors->yellow  = MOCKTERM_COLORS_YELLOW;
    display->win_colors->blue    = MOCKTERM_COLORS_BLUE;
    display->win_colors->magenta = MOCKTERM_COLORS_MAGENTA;
    display->win_colors->cyan    = MOCKTERM_COLORS_CYAN;
    display->win_colors->white   = MOCKTERM_COLORS_WHITE;
}

void
mk_display_render(mockterm_display_t* display)
{

}

void
mk_display_swap_buffer(mockterm_display_t* display)
{
    SDL_RenderPresent(display->sdl_renderer);
}

void 
mk_display_fps(mockterm_display_t* display)
{
    clock_t now = clock();
    display->win_frames++;

    if (now > (display->win_last_tick + CLOCKS_PER_SEC)) 
    {           
        display->win_fps       = display->win_frames;
        display->win_frames    = 0;
        display->win_last_tick = now;

        MK_DEBUG("fps: %lu", display->win_fps);
    }
}

void 
mk_display_run(mockterm_display_t* display)
{
    while (!display->win_loop)
    {
        if (display->win_frames % 5 == 0)
        {
            mk_display_clear(display);
            mk_events_input(display);

            mk_display_render(display);
            mk_display_swap_buffer(display);
        }

        mk_display_fps(display);
    }
}