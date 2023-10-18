// This file is used to manage the enabling and disabling of extensions

#include "extensions.h"
#include <stdbool.h>
#include <string.h>

bool extensions[END];

bool extensions_enabled(extensions_e e) {
    return extensions[e];
}

void parse_extensions(int argc, char** argv) {
    for(int i = 1; i < argc; ++i) {
        if(strcmp("2", argv[i]) && strcmp("spies", argv[i]))
            extensions[SPIES] = true;
        else if(strcmp("3", argv[i]) && strcmp("doping", argv[i]))
            extensions[DOPING] = true;
        else if(strcmp("4", argv[i]) && strcmp("lifting", argv[i]))
            extensions[LIFTING] = true;
    }
}
