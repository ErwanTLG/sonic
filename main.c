#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "gamemaster.h"
#include "player.h"
#include "extensions.h"

int main(int argc, char** argv) {
    // print help messages if wanted
    if(1 < argc && !(strcmp("help", argv[1]) && strcmp("h", argv[1]))) {
        printf("help message");  // TODO fill help message
        return 0;
    }

    system("stty cbreak");
    
    parse_extensions(argc, argv);

    board_t board;
    gamestate_t state = game_init(&board);
    game_play(state);

    system("stty cooked");
	return 0;
}
