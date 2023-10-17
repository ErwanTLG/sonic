#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// this function is used to replicate the trap placement at different dimensions
int trap_line(int line) {
    switch(line % 6){
        case 0 :
            return WIDTH / 3;
        case 1 :
            return 7 * WIDTH / 9;
        case 2 :
            return 5 * WIDTH / 9;
        case 3 :
            return 2 * WIDTH / 9;
        case 4 :
            return 4 * WIDTH / 9;
        case 5 :
            return 8 * WIDTH / 9;
    }
    return 0;
}

void init_board(board_t* b) {
    for(int i = 0; i < HEIGHT; ++i) {
        int trap_i = trap_line(i);
		for(int j = 0; j < WIDTH; ++j) {
			b->content[i][j].top = -1;
            if(j == trap_i) {
                b->content[i][j].isTrapped = true;
            } else {
                b->content[i][j].isTrapped = false;
            }
		}
	}
}

void board_push(board_t* b, int line, int row, char ctn) {
	int i_top = b->content[line][row].top;
	b->content[line][row].stack[i_top+1] = ctn;
	++b->content[line][row].top;
}

char board_pop(board_t* b, int line, int row) {
	int i_top = b->content[line][row].top;
	char top = b->content[line][row].stack[i_top];
	--b->content[line][row].top;
	//Not having the deleted cell reseted does not bother the rest of the program
	return top;
}

int board_height(board_t* b, int line, int row) {
	return b->content[line][row].top+1;
}

char board_top(board_t* b, int line, int row) {
	int i_top = b->content[line][row].top;
	if(0 <= i_top) { return b->content[line][row].stack[i_top]+'A'-'a'; }
	else { return ' '; }
}

char board_peek(board_t* b, int line, int row, int pos) {
	int i_top = b->content[line][row].top;

	if(0 <= i_top - pos) 
        return b->content[line][row].stack[i_top - pos];
	else 
        return ' '; 
}

void cell_print_trapped(board_t* b, int line, int row, int slice) { 
	char top_hedgehog = board_top(b, line, row);
	char snd_hedgehog = board_peek(b, line, row, 1);
	char thd_hedgehog = board_peek(b, line, row, 2);
	char fth_hedgehog = board_peek(b, line, row, 3);

	int nb_hedgehog = board_height(b, line, row);

    switch(slice) {
        case 0 :
            printf(" vvv ");
            break;
        case 1 :
            printf(">%c%c%c<", top_hedgehog, top_hedgehog, top_hedgehog);
            break;
        case 2 :
            printf(">%c%c%c<", snd_hedgehog, thd_hedgehog, fth_hedgehog);
            break;
        case 3 :
            printf(" ^%d^ ",nb_hedgehog);
            break;
        default :
            printf("Index out of bound\n");
            break;
    }
}

void cell_print_default(board_t* b, int line, int row, int slice) {
	char top_hedgehog = board_top(b, line, row);
	char snd_hedgehog = board_peek(b, line, row, 1);
	char thd_hedgehog = board_peek(b, line, row, 2);
	char fth_hedgehog = board_peek(b, line, row, 3);

	int nb_hedgehog = board_height(b, line, row);

    switch(slice) {
        case 0 :
            printf(" --- ");
            break;
        case 1 :
            printf("|%c%c%c|", top_hedgehog, top_hedgehog, top_hedgehog);
            break;
        case 2 :
            printf("|%c%c%c|", snd_hedgehog, thd_hedgehog, fth_hedgehog);
            break;
        case 3 :
            printf(" -%d- ", nb_hedgehog);
            break;
        default :
            printf("Index out of bound\n");
            break;
    }
}

void cell_print(board_t* b, int line, int row, int slice) {
    if(b->content[line][row].isTrapped)
        cell_print_trapped(b, line, row, slice);
    else
        cell_print_default(b, line, row, slice);
}

void board_print(board_t* b, int dice, pos_t highlighted_pos, pos_t selected_pos) {
	printf("     ");
	for(int i = 0; i < WIDTH; ++i) {
		printf(" row  ");
	}
	printf("\n");

	printf("     ");
	for(int i = 0; i < WIDTH; ++i) {
		printf("  %c   ", 'a'+i);
	}
	printf("\n");

	for(int i = 0; i < HEIGHT; ++i) {
        bool is_dice_line = i == dice;

        // we draw the dice line using yellow
        if(is_dice_line)
            printf(ANSI_COLOR_YELLOW);
     
		for(int slice = 0; slice < 4; ++slice) {
			switch(slice) {
				case 0 :
				case 3 :
					printf("     ");
				break;
				case 1 :
					printf("line ");
				break;
				case 2 :
					printf("  %d  ", i+1);
				break;
			}

			for(int j = 0; j < WIDTH; ++j) {
                bool is_highlighted_cell = i == highlighted_pos.line && j == highlighted_pos.row;
                bool is_selected_cell = i == selected_pos.line && j == selected_pos.row;

                // we draw the highlighted cell using blue and the selected one using green
                if(is_selected_cell)
                    printf(ANSI_COLOR_GREEN);
                else if(is_highlighted_cell)
                    printf(ANSI_COLOR_CYAN);

                cell_print(b, i, j, slice);
               
                // resets the color
                if(is_dice_line)
                    printf(ANSI_COLOR_YELLOW);
                else
                    printf(ANSI_COLOR_RESET);

				printf(" ");
			}
			printf("\n");
		} 
		printf(ANSI_COLOR_RESET "\n");
	}
}
