#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "gamemaster.h"

int main(int argc, char** argv) {
    system("stty cbreak");

    board_t board;
    game_init(&board);
    game_player_turn(&board, 'A', 1);

    system("stty cooked");
	return 0;
}
