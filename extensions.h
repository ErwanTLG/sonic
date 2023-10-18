#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <stdbool.h>

typedef enum extensions {
    SPIES,      // see #2
    DOPING,     // see #3
    LIFTING,    // see #4

    END         // used to know how many extensions there is
} extensions_e;

bool extensions_enabled(extensions_e e);
void parse_extensions(int argc, char** argv);

#endif  // EXTENSIONS_H
