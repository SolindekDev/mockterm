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

#include <mk_terminal.h>
#include <mk_config.h>
#include <mk_input.h>
#include <mk_msg.h>

#include <util.h>

int glyph_w, glyph_h;

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
    display->sdl_renderer = SDL_CreateRenderer(display->sdl_window, -1, SDL_RENDERER_ACCELERATED);

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
mk_display_render_cursor(mockterm_display_t* display, int character_width, int character_height)
{

}

void
mk_display_resize_term_texture(mockterm_display_t* display, int offset_y)
{
    int old_width, old_height = 0;
    SDL_QueryTexture(display->term_texture, NULL, NULL, &old_width, &old_height);

    int new_width  = old_width;
    int new_height = offset_y; 

    SDL_Texture* resized_texture = SDL_CreateTexture(
        display->sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, new_width, new_height);

    SDL_SetRenderTarget(display->sdl_renderer, resized_texture);
    SDL_Rect dstrect = { 0, 0, old_width, old_height };
    SDL_RenderCopy(display->sdl_renderer, display->term_texture, NULL, &dstrect);

    SDL_SetRenderTarget(display->sdl_renderer, NULL);
    SDL_RenderCopy(display->sdl_renderer, resized_texture, NULL, &dstrect);

    SDL_DestroyTexture(display->term_texture);
    display->term_texture = resized_texture;
}

bool
mk_display_render_on_texture(mockterm_display_t* display)
{
    SDL_Color fg_color = { 
        (display->win_colors->foreground >> 24) & 0xFF, 
        (display->win_colors->foreground >> 16) & 0xFF,
        (display->win_colors->foreground >> 8 ) & 0xFF,  
        (display->win_colors->foreground      ) & 0xFF
    };

    bool was_offseted = false;

    int x_offset = 0;
    int y_offset = 0;

    int window_height;
    SDL_GetWindowSize(display->sdl_window, NULL, &window_height);

    int term_texture_h = 0;

    int start_buffer = 0;
    if (display->buffer_size > 1536)
        start_buffer = display->buffer_size - 1536;

    for (int i = start_buffer; i < display->buffer_size; i++)
    {
        SDL_QueryTexture(display->term_texture, NULL, NULL, NULL, &term_texture_h);

        if (display->buffer[i] == '\n')
        {
            y_offset += MOCKTERM_WINDOW_COLUMN_SIZE * 1.5;

            if (y_offset > term_texture_h)
            {
                y_offset += MOCKTERM_WINDOW_COLUMN_SIZE * 2;
                mk_display_resize_term_texture(display, y_offset);
                was_offseted = true;
            }

            x_offset  = 0;
            continue;
        }

        if (y_offset < (term_texture_h - window_height))
        {
            continue;
        }

        SDL_Surface* glyph_surface = TTF_RenderGlyph_Blended(display->win_font, display->buffer[i], fg_color);
        SDL_Texture* glyph_texture = SDL_CreateTextureFromSurface(display->sdl_renderer, glyph_surface);
        
        SDL_QueryTexture(glyph_texture, NULL, NULL, &glyph_w, &glyph_h);
        SDL_Rect dstrect = { 
            MOCKTERM_WINDOW_MARGIN_LEFT + x_offset, MOCKTERM_WINDOW_MARGIN_TOP + y_offset, glyph_w, glyph_h 
        };

        x_offset += MOCKTERM_WINDOW_COLUMN_SIZE - 4;

        SDL_SetRenderTarget(display->sdl_renderer, display->term_texture);
        SDL_RenderCopy(display->sdl_renderer, glyph_texture, NULL, &dstrect);
        SDL_SetRenderTarget(display->sdl_renderer, NULL);
    }

    return was_offseted;
}

void
mk_display_reset_term_texture(mockterm_display_t* display)
{
    int tex_format, tex_access, tex_w, tex_h;
    SDL_QueryTexture(display->term_texture, &tex_format, &tex_access, &tex_w, &tex_h);
    display->term_texture = SDL_CreateTexture(display->sdl_renderer, tex_format, tex_access, tex_w, tex_h);
}

void
mk_display_render(mockterm_display_t* display)
{
    bool was_offseted = mk_display_render_on_texture(display);

    if (was_offseted)
    {
        // Rerender it casue some text is not rendering properly after
        // offseting y
        mk_display_reset_term_texture(display);
        mk_display_render_on_texture(display);
    }

    int texture_width, texture_height, window_height;
    SDL_QueryTexture(display->term_texture, NULL, NULL, &texture_width, &texture_height);
    SDL_GetWindowSize(display->sdl_window, NULL, &window_height);

    SDL_Rect dstrect = { 0, (window_height - texture_height), texture_width, texture_height };
    SDL_RenderCopy(display->sdl_renderer, display->term_texture, NULL, &dstrect);
    mk_display_reset_term_texture(display);
    // mk_display_render_cursor(display);
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

    SDL_Delay(1000 / 144);
}

void 
mk_display_run(mockterm_display_t* display)
{
    display->terminal = mk_create_terminal();
    mk_create_pseudo_terminal(display->terminal);
    
    display->buffer = calloc(sizeof(char), 512);
    display->input  = calloc(sizeof(char), 512);

    int window_w, window_h;
    SDL_GetWindowSize(display->sdl_window, &window_w, &window_h);

    display->term_texture = SDL_CreateTexture(
        display->sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, window_w, window_h);

    while (!display->win_loop)
    {
        FD_ZERO(&display->terminal->read_fds);
        FD_SET(display->terminal->master_fd, &display->terminal->read_fds);
        display->terminal->timeout.tv_sec  = 0;
        display->terminal->timeout.tv_usec = 10;

        bool change_1 = mk_events_input(display);
        bool change_2 = mk_terminal_check_fd(display, display->terminal);

        if (change_1 == true || change_2 == true)
        {
            mk_display_clear(display);
            mk_display_render(display);
            mk_display_swap_buffer(display);

            // if (display->buffer_size > 1024)
            // {
            //     display->buffer
            // }
        }

        mk_display_fps(display);
    }
}