#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "display.h"
#include "utils.h"
#include "game.h"
#include "msg.h"

int main (void) {
    int random;
    char input[2] = {'\0'}, *output = NULL, *board = NULL;
    pos_t pos;
    game_t *game = NULL;
    section_t *section = NULL;
    display_t *display;

    srand(time(NULL));

    section = init_section();
    display = init_display();
    
    display->clear = 1;

    add_to_section(section, WELCOME_MSG);
    add_to_display(display, section);
    update_display(display);

    do {
        scanf("%1s", input);
        if (strcasecmp(input, "X") && strcasecmp(input, "O")) {
            printf(INVALID_CHAR_SELECTION_MSG);
        }
    } while (strcasecmp(input, "X") && strcasecmp(input, "O"));

    game = init(TO_CAP(input[0]));

    random = rand() % 2;
    if (random == 0) {
        pos.x = rand() % 3;
        pos.y = rand() % 3;

        place_marker(game, pos, SYSTEM);
        //game->system_matrix[pos.x][pos.y] = 1;

        asprintf(&output, OPPONENT_PLAYS_MSG, (pos.x) + 1, (pos.y) + 1);
        clear_section(section);
        add_to_section(section, output);
        asprintf(&output, PLAYING_AS_MSG, game->player_char);
        add_to_section(section, output);
        board = render_board(game);
        add_to_section(section, board);
        add_to_section(section, NEXT_MOVE_MSG);
        update_display(display);

        run_game(game);
    } else {
        asprintf(&output, PLAYING_AS_MSG, game->player_char);
        clear_section(section);
        add_to_section(section, output);
        board = render_board(game);
        add_to_section(section, board);
        add_to_section(section, NEXT_MOVE_MSG);
        update_display(display);
        run_game(game);
    }

    free(game);

    return(0);
}