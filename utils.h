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

#ifndef __UTILS_H__
#define __UTILS_H__

/* Replica of GNU extension. See man asprintf.
 * Gets a pointer to a string, a string and additional arguments.
 * Inserts the values provided in the additional arguments into the
 * corresponding positions in fmt. Allocates enough memory for the new
 * string and returns it to strp. Returns the amount of written bytes.
 */
int asprintf(char **restrict strp, char *restrict fmt, ...);

/* Gets a memory address and a string. Checks if the address is NULL
 * prints the string and exits the program if needed. Returns nothing.
 */
void address_check (void *address, char *context);

#endif
