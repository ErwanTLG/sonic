#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "gamemaster.h"

int main(int argc, char** argv) {
    system("stty cbreak");

    board_t board;
    game_init(&board);
    int player = 0;
    while(true) { // TODO win condition, move from main
        game_player_turn(&board, 'A' + player, rand() % HEIGHT);
        player = (player + 1) % MAX_PLAYER;
}

system("stty cooked");
	return 0;
}
