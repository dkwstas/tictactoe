/*
 * Utilities for tictactoe game.
 * 
 * Copyright (C) 2024  Kostas Drakontidis
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utils.h"

int asprintf(char **restrict strp, char *restrict fmt, ...) {
    int size = 0;
    va_list arguments;

    /*Initialising va_list*/
    va_start(arguments, fmt);

    /*Counting the size of memory that needs to be allocated including \0*/
    size = vsnprintf(NULL, 0, fmt, arguments) + sizeof(char);
    *strp = (char *)realloc(*strp, size * sizeof(char));
    *strp = (char *)memset(*strp, '\0', size * sizeof(char));

    va_end(arguments);

    /*Resetting va_list*/
    va_start(arguments, fmt);
    vsprintf(*strp, fmt, arguments);
    
    va_end(arguments);

    return(size);
}

void address_check (void *address, char *context) {
    if (address == NULL) {
        fprintf(stderr, "Memory allocation failed at :%s\nQuitting...\n", context);
        exit(-1);
    }
}