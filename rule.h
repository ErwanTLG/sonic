#ifndef RULE_H
#define RULE_H

#include "board.h"
#include <stdbool.h>

/// returns the player who won the game. Returns `0` if no player won yet
char rule_winner(board_t* b);

/// verifies if the hedgehog located on pos is blocked because located on a trap with others behind him
/// we assume that there is a hedgehog on pos
bool rule_is_blocked(board_t* b, pos_t pos);

/// verifies if the hedgehogs (if it exists) located on pos can be pushed by 1 
/// if no hedgehogs is located on pos, returns false
bool rule_can_move(board_t* b, pos_t pos);

#endif  // RULE_H
