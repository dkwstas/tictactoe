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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "display.h"

void clear_section (section_t *section) {
    int i;

    for (i=0; i < section->size; i++) {
        free((section->text)[i]);
    }
    free(section->text);
    section->text = NULL;
    section->size = 0;
}

int add_to_section (section_t *section, char *text) {
    void *temp_addr = NULL;

    /*Extending text array by one*/
    temp_addr = (char **)realloc(section->text, (section->size + 1) * sizeof(char *));
    if (temp_addr != NULL) {
        section->text = temp_addr;
    } else {
        return(-1);
    }

    /*Allocating memory to store a copy of text*/
    section->text[section->size] = (char *)malloc((strlen(text) + 1) * sizeof(char));
    if (section->text[section->size] == NULL) {
        return(-1);
    }

    strcpy(section->text[section->size], text);
    (section->size)++;

    return(0);
}

section_t *init_section () {
    section_t *section = NULL;

    /*Allocating and initialising section*/
    section = (section_t *)malloc(sizeof(section_t));
    if (section != NULL) {
        section->size = 0;
        section->text = NULL;
    }

    return(section);
}

void clear_display (display_t *display) {
    int i;
    
    for (i=0; i < display->size; i++) {
        free(display->sections[i]);
    }
    free(display->sections);
    display->size = 0;
    display->clear = 0;
}

int add_to_display (display_t *display, section_t *section) {
    void *temp_addr = NULL;

    temp_addr = (section_t **)realloc(display->sections, (display->size + 1) * sizeof(section_t *));
    if (temp_addr != NULL) {
        display->sections = temp_addr;
    } else {
        return(-1);
    }

    display->sections[display->size] = section;
    (display->size)++;

    return(0);
}

display_t *init_display () {
    display_t *display = NULL;

    /*Allocating and initialising display*/
    display = (display_t *)malloc(sizeof(display_t));
    if (display != NULL) {
        display->clear = 0;
        display->size = 0;
        display->sections = NULL;
    }

    return(display);
}

int update_display (display_t *display) {
    int i, j, size;
    char *buffer = NULL;

    /*Clearing terminal if set in display*/
    if (display->clear) {
        system("clear");
    }

    /*Writing the display contents to the stdout file descriptor*/
    for (i=0; i < display->size; i++) {
        for (j=0; j < display->sections[i]->size; j++) {
            buffer = display->sections[i]->text[j];
            size = write(STDOUT_FILENO, buffer, strlen(buffer));
            if (size != strlen(buffer)) {
                return(-1);
            }
        }
    }

    return(0);
}