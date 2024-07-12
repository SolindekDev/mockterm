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
 
#ifndef MOCKTERM_MSG_h
#define MOCKTERM_MSG_h

#include <mk_core.h>

#define __mk_ERROR_HEADER "\e[0;34m%p\e[0;0m %s: \e[0;31merror\e[0;0m: "
#define __mk_DEBUG_HEADER "\e[0;34m%p\e[0;0m %s: \e[0;32mdebug\e[0;0m: "

#define MK_ERROR(fmt, ...) ({         \
    printf(__mk_ERROR_HEADER,         \
           __FUNCTION__,              \
           __PRETTY_FUNCTION__);      \
    printf(fmt, ##__VA_ARGS__);       \
    printf("\n");                     \
    exit(1);                          \
})

#define MK_ERROR_NO_EXIT(fmt, ...) ({         \
    printf(__mk_ERROR_HEADER,                 \
           __FUNCTION__,                      \
           __PRETTY_FUNCTION__);              \
    printf(fmt, ##__VA_ARGS__);               \
    printf("\n");                             \
})

#define MK_DEBUG(fmt, ...) ({         \
    printf(__mk_DEBUG_HEADER,         \
           __FUNCTION__,              \
           __PRETTY_FUNCTION__);      \
    printf(fmt, ##__VA_ARGS__);       \
    printf("\n");                     \
})

#endif /* MOCKTERM_MSG_h */