#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "screen.h"
#include "game.h"
#include "msg.h"

int main (void) {
    int random;
    char input[2] = {'\0'}, *output = NULL;
    pos_t pos;
    game_t *game = NULL;
    section_t *above = NULL, *below = NULL;

    srand(time(NULL));

    above = init_section();
    below = init_section();

    add_section(above, WELCOME_MSG);
    update_screen(1, NULL, above, NULL);

    do {
        scanf("%1s", input);
        if (strcasecmp(input, "X") && strcasecmp(input, "O")) {
            printf("%s",INVALID_CHAR_SELECTION_MSG);
        }
    } while (strcasecmp(input, "X") && strcasecmp(input, "O"));

    game = init(TO_CAP(input[0]));

    random = rand() % 2;
    if (random == 0) {
        pos.x = rand() % 3;
        pos.y = rand() % 3;

        place_marker(game, pos, SYSTEM);
        //game->system_matrix[pos.x][pos.y] = 1;
        
        output = _asprintf(OPPONENT_PLAYS_MSG, (pos.x) + 1, (pos.y) + 1);
        clear_section(above);
        add_section(above, output);
        add_section(below, NEXT_MOVE_MSG);
        update_screen(1, render_board(game), above, below);

//        printf("DEBUG %dx%d", r_vector[0], r_vector[1]);
        run_game(game);
    } else {
        output = _asprintf(PLAYING_AS_MSG, game->player_char);
        clear_section(above);
        add_section(above, output);
        add_section(below, NEXT_MOVE_MSG);
        update_screen(1, render_board(game), above, below);
        run_game(game);
    }

    free(game);

    return(0);
}