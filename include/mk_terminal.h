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

#ifndef MOCKTERM_TERMINAL_h
#define MOCKTERM_TERMINAL_h

#include <mk_core.h>
#include <mk_display.h>

typedef struct __mockterm_terminal_t {
    fd_set                  read_fds;
    struct timeval          timeout;

    int                     master_fd;
    pid_t                   pid;
} mockterm_terminal_t;

typedef struct __mockterm_display_t mockterm_display_t;

mockterm_terminal_t* mk_create_terminal();

void mk_create_pseudo_terminal(mockterm_terminal_t* terminal);
bool mk_terminal_check_fd(mockterm_display_t* display, mockterm_terminal_t* terminal);

#endif /* MOCKTERM_TERMINAL_h */