#pragma once

typedef struct {
    char player_char;
    char system_char;
    int player_matrix[3][3];
    int system_matrix[3][3];
    int markers_left;
} game_t;

typedef struct {
    int x;
    int y;
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

game_status_t game_analysis (game_t *game, player_type_t pt);

char *render_board (game_t *game);

int availability_check (game_t *game, pos_t pos);

int place_marker (game_t *game, pos_t pos, player_type_t pt);

void run_game (game_t *game);

game_t *init (char player_char);