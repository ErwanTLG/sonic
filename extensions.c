// This file is used to manage the enabling and disabling of extensions

#include "extensions.h"
#include "board.h"
#include "rule.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool extensions[END];

bool extensions_enabled(extensions_e e) {
    return extensions[e];
}

void parse_extensions(int argc, char** argv) {
    for(int i = 1; i < argc; ++i) {
        if(!(strcmp("2", argv[i]) && strcmp("spies", argv[i])))
            extensions[SPIES] = true;
        else if(!(strcmp("3", argv[i]) && strcmp("doping", argv[i])))
            extensions[DOPING] = true;
        else if(!(strcmp("4", argv[i]) && strcmp("lifting", argv[i])))
            extensions[LIFTING] = true;
    }

    printf("Starting a new game with the following extensions:\n");
    if(extensions[SPIES])
        printf("- spies (#2)\n");
    if(extensions[DOPING])
        printf("- doping (#3)\n");
    if(extensions[LIFTING])
        printf("- fizzy lifting (#4)\n");

    printf("\n press any key to continue\n");
    getchar();
}

gamestate_t extensions_doping(gamestate_t state) {
    // there is already a piece which got disqualified
    if (state.doped)
        return state;

    for(int i = 0; i < HEIGHT; ++i) {
        if(board_top(state.board, i, WIDTH - 1) != ' ') {
            // there is a piece which reached the last row first, it gets disqualified
            board_pop(state.board, i, WIDTH - 1);
            state.doped = true;
            return state;
        }
    }
    return state;
}
