#ifndef BOARD_H
#define BOARD_H
#define MAX_PLAYER 26
#define MAX_HEDGEHOG 4
#define HEIGHT 6
#define WIDTH 9

typedef struct cell {
    char stack[MAX_HEDGEHOG*MAX_PLAYER];
    int top;
} cell_t;

typedef struct board {
    cell_t content[HEIGHT][WIDTH];
} board_t;

void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos);
void cell_print(board_t* b, int line, int row, int slice);
void board_print(board_t* b, int highlighted_line);

#endif