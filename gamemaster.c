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

void game_player_turn(board_t* b, char player, int dice) {
    char input;
    pos_t highlighted_pos = {.line = 0, .row = 0};
    pos_t selected_pos = {.line = -1, .row = -1};
    do {
        system("clear");
        board_print(b, dice, highlighted_pos, selected_pos); 
        printf("This is %c's turn : currently moving one hedgehog to another line\n", player);
        input = getchar();
        switch(input) {
            case 'z':
                highlighted_pos.line = (highlighted_pos.line - 1 + HEIGHT) % HEIGHT;
                break;
            case 's':
                highlighted_pos.line = (highlighted_pos.line + 1) % HEIGHT;
                break;
            case 'd':
                highlighted_pos.row = (highlighted_pos.row + 1) % WIDTH;
                break;
            case 'q':
                highlighted_pos.row = (highlighted_pos.row - 1 + WIDTH) % WIDTH;
                break;
            case '\n':
                if(selected_pos.line == -1) // not selected
                    selected_pos = highlighted_pos;
                else
                    selected_pos = (pos_t) {.line = -1, .row = -1};
            break;
        }
    } while(input != 27);
}

vert_move_t game_get_vert_move(board_t* b) {
    printf("Please enter the line, column and dir you want to play in\n");
    int line, row, dir;
    scanf("%d %d %d", &line, &row, &dir);
    
    // TODO test if input is valid here
    return (vert_move_t) { line, row, dir };
}

int game_get_horiz_move(board_t* b) {
    printf("Please enter the row of the hedgehog you want to move\n");
    int row;
    scanf("%d", &row);
    
    // TODO move verification

    return row;
}
