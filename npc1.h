#ifndef NPC_H
#define NPC_H

#include "board.h"
#include "gamemaster.h"

typedef struct move_list {
    int x;
    int y;
    int dir;
    struct move_list* next;
} move_list_t;

int distance(board_t* b, int x, int y);
int cell_heuristic(board_t* b, int x, int y);
int team_sign(char team, char hhog);

int heuristic(board_t* b, char team);

double min_max(gamestate_t state, vert_move_t* next_vert_mv, horiz_move_t* next_hor_mv, bool edit_mv, char initial_team, int depth);

#endif