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

#ifndef MOCKTERM_DISPLAY_h
#define MOCKTERM_DISPLAY_h

#include <mk_core.h>

/* SDL2 Includes */
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <mk_term_colors.h>
#include <mk_terminal.h>

typedef struct __mockterm_window_properties_t mockterm_window_properties_t;

typedef struct __mockterm_display_t {
    SDL_Window*                   sdl_window;
    SDL_Renderer*                 sdl_renderer;

    mockterm_terminal_t*          terminal;
    mockterm_window_properties_t* win_prop;
    mockterm_window_colors_t*     win_colors;
    bool                          win_loop;
    unsigned long                 win_frames;
    unsigned long                 win_fps;
    clock_t                       win_last_tick; 
    TTF_Font*                     win_font;
    
    char*                         buffer;         
    char*                         input;
    size_t                        buffer_size;   
    size_t                        input_size;
    SDL_Texture*                  term_texture;
} mockterm_display_t;

typedef struct __mockterm_window_properties_t {
    const char* title;
    int         width;
    int         height;
} mockterm_window_properties_t;

mockterm_display_t* mk_display_init();

void mk_display_create_window(mockterm_display_t* display, mockterm_window_properties_t properties);
void mk_display_run(mockterm_display_t* display);
void mk_display_attach_colors(mockterm_display_t* display);

#endif /* MOCKTERM_DISPLAY_h */