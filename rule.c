// This file contains all the functions related to the special rules of the game
// For example win condition, trap rules...
// See the associated header file for a description of what each function does

#include "rule.h"
#include "board.h"
#include <stdbool.h>

char rule_winner(board_t* b) {
    int num_finished[MAX_PLAYER] = {};  // num_finished['a'] contains the number of hedgehogs controlled by player 'a' who finished
    for(int i = 0; i < HEIGHT; ++i) {
        for(int k = 0; k < board_height(b, i, WIDTH - 1); ++k) {
            char player = board_peek(b, i, WIDTH - 1, k);
            if (3 <= ++num_finished[player - 'a'])
                return player;
        }
    }
    return 0;
}

bool rule_is_blocked(board_t* b, pos_t pos) {
    if(!b->content[pos.line][pos.row].isTrapped)
        return false;

    for(int j = 0; j < pos.row; ++j) {
        if(0 < board_height(b, pos.line, j))
            return true;
    }
    return false;
} 

bool rule_can_move(board_t* b, pos_t pos) {
    // checks if a hedgehogs is located on pos
    if(board_height(b, pos.line, pos.row) == 0)
        return false;

    // checks if the hedgehog is located on the last row
    if(pos.row == WIDTH - 1)
        return false;

    return !rule_is_blocked(b, pos);
}

bool rule_has_existing_vertical_move(gamestate_t state) {
    for(int i = 0; i < HEIGHT; ++i) {
        for(int j = 0; j < WIDTH - 1; ++j) {
            if(board_top(state.board, i, j) == state.player && !rule_is_blocked(state.board, (pos_t) {.line = i, .row = j}))
                return true;
        }
    }
    return false;
}

bool rule_has_existing_horizontal_move(gamestate_t state) {
    for (int j = 0; j < WIDTH - 1; ++j) {
        if (rule_can_move(state.board, (pos_t) {.line = state.dice, .row = j}))
            return true;
    }
    return false;
}
