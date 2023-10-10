#include "gamemaster.h"

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

vert_move_t game_get_vert_move(board_t* b) {
    board_print(b, 0);
    printf("Please enter the line, column and dir you want to play in\n");
    int line, row, dir;
    scanf("%d %d %d", &line, &row, &dir);
    
    // TODO test if input is valid here
    return (vert_move_t) { line, row, dir };
}

int game_get_horiz_move(board_t* b) {
    board_print(b, 0);
    printf("Please enter the row of the hedgehog you want to move\n");
    int row;
    scanf("%d", &row);
    
    // TODO move verification

    return row;
}
