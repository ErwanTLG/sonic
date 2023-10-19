#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "board.h"
#include <stdbool.h>

gamestate_t game_init(board_t* b);
void game_play(gamestate_t state);
gamestate_t game_exec_vert_move(gamestate_t state, vert_move_t move);
gamestate_t game_exec_hor_move(gamestate_t state, horiz_move_t move);

#endif // GAMEMASTER_H
