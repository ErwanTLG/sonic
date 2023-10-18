#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "board.h"
#include <stdbool.h>

gamestate_t game_init(board_t* b);
void game_play(gamestate_t state);
#endif // GAMEMASTER_H
