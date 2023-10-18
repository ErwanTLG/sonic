#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

vert_move_t player_vertical_move(board_t* b, char player, int dice);
horiz_move_t player_horizontal_move(board_t* b, char player, int dice);

#endif  // PLAYER_H
