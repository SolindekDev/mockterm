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
#include <mk_msg.h>

#ifdef __linux__
#include <pty.h>
#elif __MACH__
#include <util.h>
#else
#error "missing pty.h"
#endif 

mockterm_terminal_t* 
mk_create_terminal()
{
    mockterm_terminal_t* terminal = calloc(1, sizeof(mockterm_terminal_t));

    // terminal->display = display;

    return terminal;
}

void 
mk_create_pseudo_terminal(mockterm_terminal_t* terminal)
{
    terminal->pid = forkpty(&terminal->master_fd, NULL, NULL, NULL);
    
    if (terminal->pid == -1) 
    {
        perror("forkpty");
        MK_ERROR("forkpty failed");
    } 

    if (terminal->pid == 0) 
    {
        execl(MOCKTERM_DEFAULT_SHELL, MOCKTERM_DEFAULT_SHELL, NULL);
        perror("execl");
        exit(1);
    }
}

// void
// mk_terminal_check_fd(mockterm_display_t* display, mockterm_terminal_t* terminal)
// {
//     if (select(terminal->master_fd + 1, &terminal->read_fds, NULL, NULL, &terminal->timeout) > 0) {
//         if (FD_ISSET(terminal->master_fd, &terminal->read_fds)) {
//             ssize_t nread = read(terminal->master_fd, display->buffer, 4048 - 1);
//             if (nread > 0)
//                 display->buffer[nread] = '\0';
//         }
//     }
// }

bool mk_terminal_check_fd(mockterm_display_t *display, mockterm_terminal_t *terminal) {
    if (select(terminal->master_fd + 1, &terminal->read_fds, NULL, NULL, &terminal->timeout) > 0) 
    {
        if (FD_ISSET(terminal->master_fd, &terminal->read_fds)) 
        {
            char temp_buffer[4048];
            ssize_t nread = read(terminal->master_fd, temp_buffer, sizeof(temp_buffer) - 1);
            if (nread > 0) 
            {
                temp_buffer[nread] = '\0';

                // Calculate the new buffer size needed
                size_t new_data_length = display->buffer_size + nread;
                display->buffer = realloc(display->buffer, new_data_length + 1);
                if (display->buffer == NULL) {
                    // Handle allocation failure
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }

                // Copy the new data to the end of the buffer
                memcpy(display->buffer + display->buffer_size, temp_buffer, nread + 1);
                display->buffer_size = new_data_length;
                return true;
            }
        }
    }

    return false;
}