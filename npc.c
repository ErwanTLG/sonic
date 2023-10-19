#include <stdbool.h>

#include "npc.h"
#include "board.h"

int distance(board_t* b, int x, int y) {
    if(0 <= x && x < HEIGHT && 0 <= y && y < WIDTH) {
        if(b[x][trap_line(x)]->top != -1) {
            return WIDTH - trap_line(x);
        } else {
            return WIDTH - y;
        }
    } else {
        return 0;
    }
}

int cell_heuristic(board_t* b, int x, int y) {
    int cell_heur = distance(b, x, y) << n;
    for(int d = 1; d < WIDTH; ++d) {
        cell_heur += (distance(b, x + d, y) + distance(b, x - d, y)) << (n-k);
    }
    return hor_heur >> n;
}

int team_sign(char team, char hhog) { return (team == hhog) ? 1 : -1; }

int heuristic(board_t* b, char team) {
    int final_heur = 0;
    for(int x = 0; x < HEIGHT; ++x) {
        for(int y = 0; y < WIDTH; ++y) {
            int cell_total_score = 0;
            int cell_depth = b[x][y]->top + 1;
            for(int i = 0; i < cell_depth; ++i) {
                int absolute_heur = team_sign(team, b[x][y]->stack[i]) * cell_horizontal_heuristic(b, x, y);
                cell_total_score += absolute_heur << (cell_depth - i);
            }
            final_heur += (cell_total_score >> cell_depth);
        }
    }
    return heuristic;
}