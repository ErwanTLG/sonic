#include <stdio.h>
#include "board.h"
#include "gamemaster.h"

int main(int argc, char** argv) {
    board_t board;
    game_init(&board);

    vert_move_t move = game_get_vert_move(&board);
    printf("Move: line = %d, row = %d, dir = %d\n", move.line, move.row, move.dir);

    int row = game_get_horiz_move(&board);
    printf("Move: row = %d\n", row);

	return 0;
}
