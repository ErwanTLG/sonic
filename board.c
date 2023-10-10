#include "board.h"
#include <stdio.h>

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

void cell_print(board_t* b, int line, int row, int slice) {
	char top_hedgehog = board_top(b, line, row);
	char snd_hedgehog = board_peek(b, line, row, 1);
	char thd_hedgehog = board_peek(b, line, row, 2);
	char fth_hedgehog = board_peek(b, line, row, 3);

	int nb_hedgehog = board_height(b, line, row);
    if(b->content[line][row].isTrapped){
        switch(slice){
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
    } else {
        switch(slice){
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
}

void board_print(board_t* b, int highlighted_line) {
	printf("     ");
	for(int i = 0; i < WIDTH; ++i) {
		printf(" row  ");
	}
	printf("\n");
	printf("     ");
	for(int i = 0; i < WIDTH; ++i) {
		printf("  %c   ",'a'+i);
	}
	printf("\n");
	for(int i = 0; i < HEIGHT; ++i) {
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
					printf("  %d  ",i+1);
				break;
			}
			for(int j = 0; j < WIDTH; ++j) {
				cell_print(b, i, j, slice);
				printf(" ");
			}
			printf("\n");
		}
		printf("\n");
	}
}
