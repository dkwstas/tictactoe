/*
 * Tictactoe game.
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
#include <time.h>
#include "display.h"
#include "game.h"
#include "main.h"
#include "msg.h"
#include "utils.h"

int main (void) {
	int random;
	char input[2] = {'\0'}, *output = NULL, *board = NULL;
	pos_t pos;
	game_t *game = NULL;
	section_t *section = NULL;
	display_t *display = NULL;

	srand(time(NULL));

	/*Initialising the display driver and printing the welcome message*/
	section = init_section();
	display = init_display();

	display->clear = 1;

	add_to_section(section, WELCOME_MSG);
	add_to_display(display, section);
	update_display(display);

	/*Asking the user for their character*/
	do {
		scanf("%1s", input);
		if (strcasecmp(input, "X") && strcasecmp(input, "O")) {
			add_to_section(section, INVALID_CHAR_SELECTION_MSG);
			update_display(display);
		}
	} while (strcasecmp(input, "X") && strcasecmp(input, "O"));

	/*Initialising the game*/
	game = init(TO_CAP(input[0]));

	/*Generating a random number to decide if the player plays first*/
	random = rand() % 2;
	if (random == 0) {
		/*Generating a random position as system plays first*/
		pos.x = rand() % 3;
		pos.y = rand() % 3;

		place_marker(game, pos, SYSTEM);

		asprintf(&output, OPPONENT_PLAYS_MSG, (pos.x) + 1, (pos.y) + 1);
		clear_section(section);
		add_to_section(section, output);
		asprintf(&output, PLAYING_AS_MSG, game->player_char);
		add_to_section(section, output);
		render_board(game, &board);
		add_to_section(section, board);
		add_to_section(section, NEXT_MOVE_MSG);
		update_display(display);

        /*Releasing excessive memory before moving on*/
        clear_section(section);
        clear_display(display);
        multi_free(section, display, output, board, NULL);

		run_game(game);
	} else {
		asprintf(&output, PLAYING_AS_MSG, game->player_char);
		clear_section(section);
		add_to_section(section, output);
		render_board(game, &board);
		add_to_section(section, board);
		add_to_section(section, NEXT_MOVE_MSG);
		update_display(display);

        clear_section(section);
        clear_display(display);
        multi_free(section, display, output, board, NULL);

		run_game(game);
	}

	free(game);

	return(0);
}
