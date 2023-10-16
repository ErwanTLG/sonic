#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "board.h"
#include <stdbool.h>

typedef struct player {
    char id;
    bool is_ai;
} player_t;

typedef struct vert_move {
    int line;
    int row;
    int dir;    // if dir = 0, on bouge pas, sinon dir vaut 1 ou -1
} vert_move_t;

void game_init(board_t* b);
void game_player_turn(board_t* b, char player, int dice);
vert_move_t game_get_vert_move(board_t* b);
int game_get_horiz_move(board_t* b);


#endif /* GAMEMASTER_H */
