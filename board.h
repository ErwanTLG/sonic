#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#define MAX_PLAYER 4
#define MAX_HEDGEHOG 4
#define HEIGHT 7
#define WIDTH 9

typedef struct cell {
    char stack[MAX_HEDGEHOG*MAX_PLAYER];
    int top;
    bool isTrapped;
} cell_t;

typedef struct board {
    cell_t content[HEIGHT][WIDTH];
} board_t;

typedef struct pos {
    int line;
    int row;
} pos_t;

void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos);
void board_print(board_t* b, int dice, pos_t highlighted_pos, pos_t selected_pos);
void init_board(board_t* b);

#endif  // BOARD_H
