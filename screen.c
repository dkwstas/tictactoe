#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "screen.h"
#include "game.h"
#include "msg.h"

char *_asprintf(char *fmt, ...) {
    unsigned int size = 0;
    char *output = NULL;
    va_list arguments;

    va_start(arguments, fmt);
    size = vsnprintf(NULL, 0, fmt, arguments) + 1;
    output = (char *)malloc(size * sizeof(char));
    output = (char *)memset(output, '\0', size * sizeof(char));

    va_start(arguments, fmt);
    vsprintf(output, fmt, arguments);

    return(output);
}

void clear_section (section_t *section) {
    free(section->text);
    section->text = NULL;
    section->size = 0;
}

void add_section (section_t *section, char *text) {
    section->text = (char **)realloc(section->text, (section->size + 1) * sizeof(char *));
    section->text[section->size] = text;
    (section->size)++;
}

section_t *init_section () {
    section_t *section = NULL;

    section = (section_t *)malloc(sizeof(section_t));
    section->size = 0;
    section->text = NULL;

    return(section);
}

void update_screen (int clear, char *board, section_t *above, section_t *below) {
    int i;

    if (clear) {
        system("clear");
    }

    for (i=0; (above != NULL) && (i < above->size); i++) {
        write(STDOUT_FILENO, above->text[i], strlen(above->text[i]));
    }

    if (board != NULL) {
        printf(BOARD_MSG, board[0], board[1], board[2],
                      board[3], board[4], board[5],
                      board[6], board[7], board[8]);
    }

    for (i=0; (below != NULL) && (i < below->size); i++) {
        write(STDOUT_FILENO, below->text[i], strlen(below->text[i]));
    }
}