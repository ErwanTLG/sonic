#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "board.h"
#include <stdbool.h>

typedef struct gamestate{
    char player;    // the player whose turn it is
    board_t* board; // the current board
    int dice;       // the result of the dice roll
    bool doped;     // whether or not a piece has reached the goal, see #3
} gamestate_t;

typedef struct vert_move {
    int line;
    int row;
    int dir;    // if dir = 0, on bouge pas, sinon dir vaut 1 ou -1
} vert_move_t;

typedef struct horiz_move {
    int row;
} horiz_move_t;

gamestate_t game_init(board_t* b);
void game_play(gamestate_t state);
#endif // GAMEMASTER_H
