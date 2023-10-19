#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#define MAX_PLAYER 4
#define MAX_HEDGEHOG 4
#define HEIGHT 3
#define WIDTH 3

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

typedef struct gamestate{
    char player;    // the player whose turn it is
    board_t* board; // the current board
    int dice;       // the result of the dice roll
    bool doped;     // whether or not a piece has reached the goal, see #3
} gamestate_t;

typedef struct vert_move {
    int line;
    int row;
    int dir;    // if dir = 0, on bouge pas, sinon dir vaut 1 ou -1
} vert_move_t;

typedef struct horiz_move {
    int row;
} horiz_move_t;

int trap_line(int line);
void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos);
void board_print(board_t* b, int dice, pos_t highlighted_pos, pos_t selected_pos);
void init_board(board_t* b);
void board_cpy(board_t* src, board_t* goal);

#endif  // BOARD_H
