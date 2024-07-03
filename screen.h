#pragma once

typedef struct {
    int size;
    char **text;
} section_t;

char *_asprintf(char *fmt, ...);

void clear_section (section_t *section);

void add_section (section_t *section, char *text);

section_t *init_section ();

void update_screen (int clear, char *board, section_t *above, section_t *below);