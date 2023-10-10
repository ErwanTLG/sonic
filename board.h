#define MAX_PLAYER 26
#define MAX_HEDGEHOG 4
#define HEIGHT 6
#define WIDTH 9

typedef struct cell {
    char stack[MAX_HEDGEHOG*MAX_PLAYER];
    int top;
} cell_t;

typedef struct board {
    cell_t t[HEIGHT][WIDTH];
} board_t;
