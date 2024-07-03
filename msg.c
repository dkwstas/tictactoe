/*
 * Predefined strings for tictactoe game.
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

char *WELCOME_MSG = "Welcome to tic tac toe.\n Please select a character: X, O.\n";

char *INVALID_CHAR_SELECTION_MSG = "Invalid selection.\n Please select a character: X, O.\n";

char *PLAYING_AS_MSG = "It's your turn. You are playing as %c.\n";

char *OPPONENT_PLAYS_MSG = "Opponent played at %d %d.\n";

char *BOARD_MSG = "\n   |  1  |  2  |  3  "   \
              "\n___|_____|_____|_____"   \
              "\n   |     |     |     "   \
              "\n 1 |  %c  |  %c  |  %c  "\
              "\n___|_____|_____|_____"   \
              "\n   |     |     |     "   \
              "\n 2 |  %c  |  %c  |  %c  "\
              "\n___|_____|_____|_____"   \
              "\n   |     |     |     "   \
              "\n 3 |  %c  |  %c  |  %c  "\
              "\n   |     |     |     \n" ;

char *NEXT_MOVE_MSG = "\nEnter your next move.\n";

char *INVALID_MOVE_MSG = "You can't place a marker here. Enter your next move.\n";

char *PLAYER_WON_MSG = "You won the game!\n";

char *OPPONENT_WON_MSG = "\nYou lost. The opponent won the game, good luck next time.\n";

char *DRAW = "\nYou run out of markers. It's a draw.\n";