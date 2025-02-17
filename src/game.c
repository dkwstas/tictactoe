/*
 * Tictactoe game engine.
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
#include <stdlib.h>
#include "display.h"
#include "game.h"
#include "msg.h"
#include "utils.h"

game_status_t game_analysis (game_t *game, player_type_t pt) {
	int i, j, (*matrix)[3] = NULL, markers_row = 0, markers_col = 0,
		markers_main_diag = 0, markers_sec_diag = 0;

	/*Setting an alias to pt_matrix*/
	if (pt == PLAYER) {
		matrix = game->player_matrix;
	} else {
		matrix = game->system_matrix;
	}

	/*Iterating through matrix searching for a winning combination*/
	for (i=0; (i < 3) && (markers_row < 3) && (markers_col < 3); i++) {
		markers_row = 0;
		markers_col = 0;

		for (j=0; (j < 3) && (markers_row < 3) && (markers_col < 3); j++) {
			if (matrix[i][j] == 1) {
				markers_row++;
			}
			if (matrix[j][i] == 1) {
				markers_col++;
			}
		}
	}

	/*Counting markers on both diagonals*/
	markers_main_diag = matrix[0][0] + matrix[1][1] + matrix[2][2];
	markers_sec_diag = matrix[0][2] + matrix[1][1] + matrix[2][0];

	/*Checking if there is any winning combination*/
	if (markers_row == 3 || markers_col == 3 || markers_main_diag == 3 ||
			markers_sec_diag == 3) {

		if (pt == PLAYER) {
			return(PLAYER_WON);
		} else {
			return(SYSTEM_WON);
		}
	}

	return(RUNNING);
}

void render_board (game_t *game, char **output) {
	int i, j, size;
	char *board = NULL;

	board = (char *)malloc(9 * sizeof(char));

	for (i=0; i < 3; i++) {
		for (j=0; j < 3; j++) {
			if (game->player_matrix[i][j] == 1) {
				board[(3 * i) + j] = game->player_char;
			} else if (game->system_matrix[i][j] == 1) {
				board[(3 * i) + j] = game->system_char;
			} else {
				board[(3 * i) + j] = '-';
			}
		}
	}

	size = asprintf(output, BOARD_MSG,
			board[0], board[1], board[2],
			board[3], board[4], board[5],
			board[6], board[7], board[8]);

	free(board);

	if (size == -1) {
		free(*output);
	}
}

int availability_check (game_t *game, pos_t pos) {
	if (game->player_matrix[pos.x][pos.y] == 1 ||
			game->system_matrix[pos.x][pos.y] == 1) {

		return(-1);
	} else {
		return(0);
	}
}

int place_marker (game_t *game, pos_t pos, player_type_t pt) {
	if (availability_check(game, pos) == -1) {
		return(-1);
	}

	if (pt == PLAYER) {
		game->player_matrix[pos.x][pos.y] = 1;
	} else {
		game->system_matrix[pos.x][pos.y] = 1;
	}

	(game->markers_left)--;

	return(0);
}

pos_t *get_threat_pos (game_t *game, player_type_t pt) {
	int i, j, (*main_matrix)[3] = NULL, (*sec_matrix)[3] = NULL,
		markers_row = 0, markers_col = 0, markers_main_diag = 0,
		markers_sec_diag = 0;
	pos_t *pos = NULL;

	if (pt == PLAYER) {
		main_matrix = game->player_matrix;
		sec_matrix = game->system_matrix;
	} else {
		main_matrix = game->system_matrix;
		sec_matrix = game->player_matrix;
	}

	pos = (pos_t *)malloc(sizeof(pos_t));

	for (i=0; i < 3; i++) {
		markers_row = 0;
		markers_col = 0;

		/*Searching for two collinear markers in the matrix*/
		for (j=0; (markers_row < 2) && (markers_col < 2) && (j < 3); j++) {
			if (main_matrix[i][j] == 1) {
				markers_row++;
			}
			if (main_matrix[j][i] == 1) {
				markers_col++;
			}
		}

		if (markers_row == 2) {
			for (j=0; j < 3; j++) {
				/* 
				 * Checking if there is a collinear empty spot with the two
				 * markers which means that it's a threat for the other player
				 */
				if ((main_matrix[i][j] == 0) && (sec_matrix[i][j] == 0)) {
					pos->x = i;
					pos->y = j;
					return(pos);
				}
			}
		}

		if (markers_col == 2) {
			for (j=0; j < 3; j++) {
				/*Same as above, but for columns*/
				if ((main_matrix[j][i] == 0) && (sec_matrix[j][i] == 0)) {
					pos->x = j;
					pos->y = i;
					return(pos);
				}
			}
		}
	}

	/*Same process for diagonals*/
	markers_main_diag = main_matrix[0][0] + main_matrix[1][1] +
		main_matrix[2][2];

	markers_sec_diag = main_matrix[0][2] + main_matrix[1][1] +
		main_matrix[2][0];

	if (markers_main_diag == 2) {
		for (j=0; j < 3; j++) {
			if ((main_matrix[j][j] == 0) && (sec_matrix[j][j] == 0)) {
				pos->x = j;
				pos->y = j;
				return(pos);
			}
		}
	}

	if (markers_sec_diag == 2) {
		for (i=0, j=2; i < 3; i++, j--) {
			if ((main_matrix[i][j] == 0) && (sec_matrix[i][j] == 0)) {
				pos->x = i;
				pos->y = j;
				return(pos);
			}
		}
	}

	free(pos);

	return(NULL);
}

pos_t *system_play (game_t *game) {
	pos_t *pos = NULL;

	/*Checking if system can win with a move*/
	if ((pos = get_threat_pos(game, SYSTEM)) != NULL) {
		if (place_marker(game, *pos, SYSTEM) == -1) {
			return(NULL);
		}
		/*Checking if the player can win with a move and blocking them*/
	} else if ((pos = get_threat_pos(game, PLAYER)) != NULL) {
		if (place_marker(game, *pos, SYSTEM) == -1) {
			return(NULL);
		}
	} else {
		/*TODO: Add functionality to place next to previous markers*/
		/*Placing a marker randomly*/
		pos = (pos_t *)malloc(sizeof(pos_t));

		do {
			pos->x = rand() % 3;
			pos->y = rand() % 3;
		} while (place_marker(game, *pos, SYSTEM) == -1);
	}

	return(pos);
}

void run_game (game_t *game) {
	char temp, *output = NULL, *board = NULL;
	pos_t pos, *s_pos = NULL;
	section_t *section = NULL;
	display_t *display = NULL;

	/*Initialising the display*/
	section = init_section();
	display = init_display();
	add_to_display(display, section);

	while (game->markers_left > 0) {
		do {
			while (scanf("%d %d", &pos.x, &pos.y) != 2) {
				/*Cleaning stdin from garbage*/
				add_to_section(section, INVALID_MOVE_MSG);
				update_display(display);
				while ((temp = getchar()) != EOF && temp != '\n') {}
				continue;
			}

			(pos.x)--;
			(pos.y)--;

			if (pos.x < 0 || pos.x > 2 || pos.y < 0 || pos.y > 2) {
				add_to_section(section, INVALID_MOVE_MSG);
				update_display(display);
			} else {
				break;
			}
		} while (pos.x < 0 || pos.x > 2 || pos.y < 0 || pos.y > 2);

		if (place_marker(game, pos, PLAYER) == -1) {
			add_to_section(section, INVALID_MOVE_MSG);
			update_display(display);
			continue;
		}

		clear_section(section);
		display->clear = 1;

		/*Running game analysis to check if player won*/
		if ((game->markers_left <= 4) &&
				(game_analysis(game, PLAYER) == PLAYER_WON)) {

			render_board(game, &board);
			add_to_section(section, board);
			add_to_section(section, PLAYER_WON_MSG);
			update_display(display);
			break;
			/*Checking if all the markers have been used*/
		} else if (game->markers_left == 0) {
			break;
		} else {
			s_pos = system_play(game);

			/*Running game analysis to check if system won*/
			if ((game->markers_left <= 4) &&
					(game_analysis(game, SYSTEM) == SYSTEM_WON)) {

				asprintf(&output, OPPONENT_PLAYS_MSG,
						(s_pos->x) + 1, (s_pos->y) + 1);

				add_to_section(section, output);
				render_board(game, &board);
				add_to_section(section, board);
				add_to_section(section, OPPONENT_WON_MSG);
				update_display(display);
				break;
			}
		}

		asprintf(&output, OPPONENT_PLAYS_MSG, (s_pos->x) + 1, (s_pos->y) + 1);
		add_to_section(section, output);
		asprintf(&output, PLAYING_AS_MSG, game->player_char);
		add_to_section(section, output);
		render_board(game, &board);
		add_to_section(section, board);
		add_to_section(section, NEXT_MOVE_MSG);
		update_display(display);

		free(s_pos);
	}

	if (game->markers_left == 0) {
		clear_section(section);
		render_board(game, &board);
		add_to_section(section, board);
		add_to_section(section, DRAW);
		update_display(display);
	}

	clear_section(section);
	clear_display(display);
	multi_free(section, display, board, output, NULL);
}

game_t *init (char player_char) {
	int i, j;
	game_t *game = NULL;

	game = (game_t *)malloc(sizeof(game_t));
	game->player_char = player_char;

	if (game->player_char == 'X') {
		game->system_char = 'O';
	} else {
		game->system_char = 'X';
	}

	for (i=0; i < 3; i++) {
		for (j=0; j < 3; j++) {
			game->player_matrix[i][j] = 0;
			game->system_matrix[i][j] = 0;
		}
	}

	game->markers_left = 9;

	return(game);
}
