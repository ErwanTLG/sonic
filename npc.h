#ifndef NPC_H
#define NPC_H

#include "board.h"

int distance(board_t* b, int x, int y);
int cell_horizontal_heuristic(board_t* b, int x, int y);
int team_sign(char team, char hhog);

int horizontal_heuristic(board_t* b, char team);

#endif  // NPC_H
