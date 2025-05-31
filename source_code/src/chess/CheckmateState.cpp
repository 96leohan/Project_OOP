#include "CheckmateState.h"
#include <iostream>

void CheckmateState::handle(Game& game) {
    std::cout << (game.getCurrentTurn() == Color::White ? "Black" : "White") << " wins by checkmate!\n";
}
