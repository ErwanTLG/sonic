#include "gamemaster.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
//#include "utils.h"

void game_init(board_t* b) {
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
}
