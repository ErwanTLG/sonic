#ifndef NPC_H
#define NPC_H

typedef struct move_list {
    // TODO
    int x;
    int y;
    int dir;
    move_list_t* next;
} move_list_t

int distance(board_t* b, int x, int y);
int cell_horizontal_heuristic(board_t* b, int x, int y);
int team_sign(char team, char hhog);

int heuristic(board_t* b, char team);

double min_max(game_state_t state, vert_move_t* next_vert_mv, hor_move_t* next_hor_mv, bool edit_mv, char initial_team, int diced_line, int depth) {

#endif