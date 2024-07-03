/*
 * A display manager using sections of text.
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

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/*Contents of section*/
typedef struct {
    int size;       /*Number of strings in section*/
    char **text;    /*Array of strings*/
} section_t;

/*Contents of display*/
typedef struct {
    int clear;              /*Defines whether to clear the terminal on update*/
    int size;               /*Number of sections in display*/
    section_t **sections;   /*Array of sections*/
} display_t;

/*
 * Gets a pointer to a section and clears the contents of the section.
 * Returns nothing.
 */
void clear_section (section_t *section);

/*
 * Gets a pointer to a display and a string.
 * Adds the string to the display. Returns 0 on success, -1 on error.
 */
int add_to_section (section_t *section, char *text);

/*Creates, initialises and returns a section. Returns NULL on error.*/
section_t *init_section ();

/*
 * Gets a pointer to a display and clears the contents of the display.
 * It will NOT clear section contents. Returns nothing.
 */
void clear_display (display_t *display);

/*
 * Gets a pointer to a display and a pointer to a section.
 * Adds the section to the display. Returns 0 on success, -1 on error.
 */
int add_to_display (display_t *display, section_t *section);

/*Creates, initialises and returns a display. Returns NULL on error.*/
display_t *init_display ();

/*
 *Gets a pointer to a display, updates the terminal output.
 * Returns 0 on success, -1 on error.
 */
int update_display (display_t *display);

#endif