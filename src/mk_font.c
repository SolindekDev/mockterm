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
 *k
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <mk_font.h>
#include <mk_core.h>

#include <mk_config.h>
#include <mk_msg.h>

#include <SDL2/SDL_ttf.h>

const char* search_font_in_directory(const char* directory, const char* font_name) {
    DIR *dp = opendir(directory);

    if (dp == NULL) 
        return NULL;

    struct dirent* entry;
    while ((entry = readdir(dp))) 
    {
        if (entry->d_type == DT_REG || entry->d_type == DT_LNK) 
        {
            if (strstr(entry->d_name, font_name) && strstr(entry->d_name, ".ttf")) 
            {
                static char font_path[1024];
                snprintf(font_path, sizeof(font_path), "%s/%s", directory, entry->d_name);
                closedir(dp);
                return font_path;
            }
        }
    }

    closedir(dp);
    return NULL;
}

// Main function to find the font path
const char* mk_font_find_path(const char* font_name) {
    const char* font_directories[] = {
        "/usr/share/fonts",
        "/usr/local/share/fonts",
        "~/.fonts",
        "/Users/bruno/System/Library/Fonts",
        "/Users/bruno/Library/Fonts",
        NULL
    };

    for (int i = 0; font_directories[i] != NULL; ++i) 
    {
        const char* path = search_font_in_directory(font_directories[i], font_name);
        if (path != NULL) 
            return path;
    }

    return NULL;
}

void
mk_font_open(mockterm_display_t* display, char* font_path)
{
    TTF_Font* font = TTF_OpenFont(font_path, MOCKTERM_WINDOW_COLUMN_SIZE + 2);
    
    if (font == NULL)
        MK_ERROR("couldn't open a font from '%s'\n", font_path);

    display->win_font = font;
    MK_DEBUG("succesfully open a font from '%s'\n", font_path);
}