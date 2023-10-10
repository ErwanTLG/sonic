#include <stdio.h>
#include "board.h"


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

	if(0 <= i_top) { return b->content[line][row].stack[i_top]; }
	else { return ' '; }
}

char board_peek(board_t* b, int line, int row, int pos) {
	int i_top = b->content[line][row].top;

	if(0 <= i_top - pos) { return b->content[line][row].stack[i_top - pos]; }
	else { return ' '; };
}

void cell_print(board_t* b, int line, int row, int slice) {
	char top_hedgehog = board_top(b, line, row)+'A'-'a';
	char snd_hedgehog = board_peek(b, line, row, 1);
	char thd_hedgehog = board_peek(b, line, row, 2);
	char fth_hedgehog = board_peek(b, line, row, 3);

	int nb_hedgehog = board_height(b, line, row);
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
			printf(" -%d- ",nb_hedgehog);
			break;
		default :
			printf("Index out of bound\n");
			break;
	}
}

void board_print(board_t* b, int highlighted_line) {
	printf("     row  row  row  row  row  row  row  row  row \n");
	printf("      a    b    c    d    e    f    g    h    i  \n");
	for(int i = 0; i < 6; ++i) {
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
			for(int j = 0; j < 9; ++j) {
				cell_print(b, i, j, slice);
			}
			printf("\n");
		}
		printf("\n");
	}
}

int main(int argc, char** argv) {
	board_t test;
	for(int i = 0; i < HEIGHT; ++i){
		for(int j = 0; j < WIDTH; ++j){
			test.content[i][j].top = -1;
			board_push(&test, i, j, 'a');
			board_push(&test, i, j, 'b');
			board_push(&test, i, j, 'c');
		}
	}
	board_print(&test, 1);
	return 0;
}
