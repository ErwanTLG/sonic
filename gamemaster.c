#include "gamemaster.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "rule.h"
#include "player.h"
//#include "utils.h"

gamestate_t game_init(board_t* b) {
    // TODO get players
    init_board(b);
    
    // hedgehogs init
    for(int i = 0; i < MAX_PLAYER; ++i) {
        for(int j = 0; j < MAX_HEDGEHOG; ++j) {
            board_push(b, rand() % HEIGHT, 0, 'a' + i);
        }
    }

    for(int i = 0; i < HEIGHT; ++i) {
        //array_shuffle(b->content[i][0].stack, b->content[i][0].top + 1);
    }
    
    return (gamestate_t) {.player = 'a', .board = b, .doped = false};
}

gamestate_t game_player_turn(gamestate_t state) {
    // phase 1 of the turn, moving one hedgehog vertically
    if(rule_has_existing_vertical_move(state)) {
        vert_move_t move = player_vertical_move(state.board, state.player, state.dice);
        if(move.dir != 0) {
            char hedgehog = board_pop(state.board, move.line, move.row);
            board_push(state.board, move.line + move.dir, move.row, hedgehog);
        }
    }

    // phase 2 of the turn, pushing one hedgehog horizontally
    if(rule_has_existing_horizontal_move(state)) {
        horiz_move_t move = player_horizontal_move(state.board, state.player, state.dice);
        char hedgehog = board_pop(state.board, state.dice, move.row);
        board_push(state.board, state.dice, move.row + 1, hedgehog);
    }

    // we return the new gamestate, ready for the next turn to be started
    if(++state.player == 'a' + MAX_PLAYER)
        state.player = 'a';
    state.dice = rand() % HEIGHT;
    return state;
}

void game_play(gamestate_t state) {
    while (rule_winner(state.board) == 0) {
        state = game_player_turn(state);
    }
    
    char winner = rule_winner(state.board);
    system("clear");
    printf("CONGRATULATIONS, player %c won !\n", winner);
}
