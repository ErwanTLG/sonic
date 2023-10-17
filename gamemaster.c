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

// this function is meant to be called when you want the player to select a cell
// it returns the position of the selected cell
pos_t game_select_cell(board_t* b, int dice, char* message) {
    char input;
    pos_t highlighted_pos = {.line = 0, .row = 0};
    pos_t selected_pos = {.line = -1, .row = -1};
    do {
        system("clear");
        board_print(b, dice, highlighted_pos, selected_pos); 
        printf("%s", message);
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
            case '\n':  // we select the currently highlighted cell
                selected_pos = highlighted_pos;
                break;
            case 27:    // ESC pressed, we unselect the cell
                selected_pos = (pos_t) {.line = -1, .row = -1};
                break;
        }
    } while(input != 32); // we stop when SPACE is pressed

    return selected_pos;
}

// TODO maybe move this to a player.c
void game_horizontal_move(board_t* b, char player, int dice) {
    char message[100];
    sprintf(message, "This is %c's turn. Currently selecting a hedgehog who can change line.\n", player);
    pos_t selected_pos = game_select_cell(b, dice, message); 
    
    if(selected_pos.line == -1) {
        // the player is not moving any hedgehog, we suggest he should do otherwise
        printf("You have not selected any hedgehog to move. Do you want to proceed (NO: ESC, YES: any other key)\n");
        char input = getchar();
        if(input == 27)     // input == ESC
            game_horizontal_move(b, player, dice);
    } else {
        // check if the hedgehog belongs to the player
        if(board_top(b, selected_pos.line, selected_pos.row) != player) {
            // if not, we print a message and restart the process
            printf("Sorry, this hedgehog is not controlled by the current player. (press any key to continue)\n");
            getchar();
            game_horizontal_move(b, player, dice);
        } else {
            // we can ask the player where he wants to move the hedgehog to
            sprintf(message, "This is %c's turn. Currently selecting a line to move the hedgehog from (%d, %d) to.\n", player, selected_pos.line, selected_pos.row);
            pos_t destintation = game_select_cell(b, dice, message);

            // we check if the move is now valid (i.e. different line, same row)
            if (selected_pos.line != destintation.line && selected_pos.row == destintation.row) {
                char hedgehog = board_pop(b, selected_pos.line, selected_pos.row);
                board_push(b, destintation.line, destintation.row, hedgehog);
            } else {
                printf("Sorry, this is not a valid move. You have to move the hedgehog from (%d, %d) to a cell positioned on the same row and on a different line.\n", selected_pos.line, selected_pos.row);
                getchar();
            }
        }
    } 
}

void game_vertical_move(board_t* b, char player, int dice) {
    char message[100];
    sprintf(message, "This is %c's turn. Currently selecting a hedgehog who will be pushed one row further\n", player);
    pos_t selected_pos = game_select_cell(b, dice, message);
    if(selected_pos.line == -1) {
        // the player must move a hedgehog, we remind him of that
        printf("Sorry, you have to select a hedgehog on the yellow line to be moved.\n");
        getchar();
        game_vertical_move(b, player, dice);
    } else {
        // we check if the selected hedgehog exists and is on the dice line and if it can move (trapped rule)
        // TODO check trap
        if(selected_pos.line == dice && 0 < board_height(b, selected_pos.line, selected_pos.row) && selected_pos.row != WIDTH - 1) {
            char hedgehog = board_pop(b, selected_pos.line, selected_pos.row);
            board_push(b, selected_pos.line, selected_pos.row + 1, hedgehog);
        } else {
            printf("Sorry, this is not a valid move.\n");
            getchar();
            game_vertical_move(b, player, dice);
        }
    }
}

void game_player_turn(board_t* b, char player, int dice) {
    // TODO check if player has any hedgehog to move, if not then skip this step
    game_horizontal_move(b, player, dice);
    game_vertical_move(b, player, dice);
}
