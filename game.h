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

#ifndef __GAME_H__
#define __GAME_H__

/*Represents a game of tictactoe*/
typedef struct {
	char player_char;
	char system_char;
	int player_matrix[3][3];
	int system_matrix[3][3];
	int markers_left;
} game_t;

/*A position in a matrix*/
typedef struct {
	int x;          /*Row value*/
	int y;          /*Column value*/
} pos_t;

typedef enum {
	PLAYER,
	SYSTEM
} player_type_t;

typedef enum {
	RUNNING,
	PLAYER_THREAT,
	SYSTEM_THREAT,
	PLAYER_WON,
	SYSTEM_WON
} game_status_t;

/*
 * Gets a pointer to a game and the type of player. Checks if pt_matrix has a
 * winning combination. Returns pt_WON on win, RUNNING if not.
 */
game_status_t game_analysis (game_t *game, player_type_t pt);

/* 
 * Gets a pointer to a game. Converts and returns both matrices as a string.
 * Returns NULL on error.
 */
char *render_board (game_t *game);

/*
 * Gets a pointer to a game and a position. Checks if the position is occupied
 * in the combination of both matrices. Returns 0 if free, -1 if not.
 */
int availability_check (game_t *game, pos_t pos);

/*
 * Gets a pointer to a game, a position and the type of player. Sets the value
 * at position pos in pt_matrix to 1 indicating that a marker is placed by pt.
 * Returns 0 on success, -1 if pos is occupied (See availability_check()).
 */
int place_marker (game_t *game, pos_t pos, player_type_t pt);

/*
 * Gets a pointer to a game and the type of player. Searches pt_matrix checking
 * if there is a threatening combination for the opponent. Returns the position
 * of the threat or NULL if there is not one.
 */
pos_t *get_threat_pos (game_t *game, player_type_t pt);

/*
 * Gets a pointer to a game. Imitates an opponent by calculating the position
 * of its next move, trying to win and not lose. Returns a pointer to the
 * position of the move. On error NULL is returned, this indicates a serious
 * bug that will end up to an imbalanced game.
 */
pos_t *system_play (game_t *game);

/*Gets a pointer to a game. This is the game core. Returns nothing.*/
void run_game (game_t *game);

/* Gets a character representing the character of the player, based on their
 * selection. Initialises and returns the game. Returns NULL on error.
 */
game_t *init (char player_char);

#endif
