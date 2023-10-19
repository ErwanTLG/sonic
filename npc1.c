#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

#include "npc1.h"
#include "board.h"
#include "gamemaster.h"

// struct list methods

move_list_t* concat(move_list_t* lst, int nx, int ny, int ndir) {
    move_list_t* n_lst = malloc(sizeof(move_list_t));
    n_lst->next = lst;
    n_lst->x = nx;
    n_lst->y = ny;
    n_lst->dir = ndir;
    return n_lst;
}

void free_list(move_list_t* lst) {
    if(lst != NULL) {
        if(lst->next != NULL) {
            free_list(lst->next);
            free(lst);
        } else {
            free(lst);
        }
    }
}

// heuristic

int distance(board_t* b, int x, int y) {
    if(0 <= x && x < HEIGHT && 0 <= y && y < WIDTH) {
        if(board_height(b,x,trap_line(x)) != 0) {
            return WIDTH - trap_line(x);
        } else {
            return WIDTH - y;
        }
    } else {
        return 0;
    }
}

int cell_heuristic(board_t* b, int x, int y) {
    int cell_heur = distance(b, x, y) << WIDTH;
    for(int d = 1; d < WIDTH; ++d) {
        cell_heur += (distance(b, x + d, y) + distance(b, x - d, y)) << (WIDTH-d);
    }
    return (cell_heur >> WIDTH);
}

int team_sign(char team, char hhog) { return (team == hhog) ? 1 : -1; }

int heuristic(board_t* b, char team) {
    // TODO add consideration if the game is already finished
    int final_heur = 0;
    for(int x = 0; x < HEIGHT; ++x) {
        for(int y = 0; y < WIDTH; ++y) {
            int cell_total_score = 0;
            int cell_depth = board_height(b, x, y);
            for(int i = 0; i < cell_depth; ++i) {
                int absolute_heur = team_sign(team, board_peek(b, x, y, cell_depth-i)) * cell_horizontal_heuristic(b, x, y);
                cell_total_score += absolute_heur << (cell_depth - i);
            }
            final_heur += (cell_total_score >> cell_depth);
        }
    }
    return final_heur;
}

// computing possible moves

void possible_vertical_moves(board_t* b, move_list_t* possible_moves, char team) {
    for(int x = 0; x < HEIGHT; ++x) {
        for(int y = 0; y < WIDTH - 1; ++y) {
            // Up
            if(0 <= x-1 && board_height(b, x, y) != 0 && board_top(b, x, y) == team) {
                concat(possible_moves, x, y, -1);
            }
            // Down
            if(x+1 <= HEIGHT && board_height(b, x, y) != 0) {
                concat(possible_moves, x, y, 1);
            }
        }
    }
}

void possible_horizontal_moves(board_t* b, move_list_t* possible_moves, char team, int line) {
    for(int y = 0; y < WIDTH - 1; ++y) {
        if(board_top(b, line, y) == team) {
            concat(possible_moves, line, y, 0);
        }
    }
}

// min-max

double min_max(gamestate_t state, vert_move_t* next_vert_mv, horiz_move_t* next_hor_mv, bool edit_mv, char initial_team, int depth) {
    if(depth == 0) {
        return (double)heuristic(state.board, state.player);
    } else {
        // Processing vertical moves
        move_list_t* vert_moves = malloc(sizeof(move_list_t));
        // Adding the idle move
        vert_moves->x = -1;
        vert_moves->y = -1;
        vert_moves->dir = 0;
        possible_vertical_moves(state.board, vert_moves, state.player);

        // Processing horizontal moves
        move_list_t* hor_moves = malloc(sizeof(move_list_t));
        // Adding the idle move
        hor_moves->x = -1;
        hor_moves->y = -1;
        hor_moves->dir = 0;

        move_list_t* cur_vert_move = vert_moves;
        move_list_t* cur_hor_move = hor_moves;

        board_t future_board;
        double future_board_score;

        double opt_score;
        if(state.player == initial_team) {
            opt_score = -DBL_MAX;
        } else {
            opt_score = DBL_MAX;
        }
        int opt_vert_x;
        int opt_vert_y;
        int opt_vert_dir;
        int opt_hor_y;
        do {
            cur_hor_move = hor_moves;
            while(cur_hor_move != NULL) {
                board_cpy(state.board, &future_board);
                gamestate_t future_state;
                future_state.board = &future_board;
                vert_move_t tmp_v_move;
                tmp_v_move.line = cur_vert_move->x;
                tmp_v_move.row = cur_vert_move->y;
                tmp_v_move.dir = cur_vert_move->dir;
                horiz_move_t tmp_h_move;
                tmp_h_move.row = cur_vert_move->y;
                future_state = game_exec_vert_move(future_state, tmp_v_move);
                future_state = game_exec_hor_move(future_state, tmp_h_move);
                future_board_score = 0;
                future_state.player = ((state.player - 'a' + 1) % MAX_PLAYER) + 'a';
                for(int possible_line = 0; possible_line < HEIGHT; ++possible_line) {
                    future_state.dice = possible_line;
                    // TODO **maybe** replace the mean by the median value
                    future_board_score += min_max(future_state, next_vert_mv, next_hor_mv, false, initial_team, depth-1) / 6;
                }

                // We act as the opposing players are a whole
                // making up for the opponent in a 2-player game
                if(state.player == initial_team) {
                    if(opt_score < future_board_score) {
                        opt_score = future_board_score;
                        opt_vert_x = cur_vert_move->x;
                        opt_vert_y = cur_vert_move->y;
                        opt_vert_dir = cur_vert_move->dir;
                        opt_hor_y = cur_hor_move->y;
                    }
                } else {
                    if(future_board_score < opt_score) {
                        opt_score = future_board_score;
                        opt_vert_x = cur_vert_move->x;
                        opt_vert_y = cur_vert_move->y;
                        opt_vert_dir = cur_vert_move->dir;
                        opt_hor_y = cur_hor_move->y;
                    }
                }
                cur_hor_move = cur_hor_move->next;
            }
            cur_vert_move = cur_vert_move->next;
        } while(cur_vert_move != NULL);
        free_list(cur_vert_move);
        free_list(cur_hor_move);
        if(edit_mv) {
            next_vert_mv->line = opt_vert_x;
            next_vert_mv->row = opt_vert_y;
            next_vert_mv->dir = opt_vert_dir;
            next_hor_mv->row = opt_hor_y;
        }
        return opt_score;
    }
}

// npc turn

gamestate_t game_npc_turn(gamestate_t state) {
    //vert_move_t v_move;
    //horiz_move_t h_move;

    //min_max(state, &v_move, &h_move, true, state.player, 1);
    
    //state = game_exec_vert_move(state, v_move);
    //state = game_exec_hor_move(state, h_move);
    return state;
}