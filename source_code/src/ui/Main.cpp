#include "chess/Game.h"
#include "ui/ConsoleRenderer.h"
#include "ui/ConsoleInputHandler.h"

int main() {
    auto renderer = std::make_unique<ui::ConsoleRenderer>();
    auto input_handler = std::make_unique<ui::ConsoleInputHandler>();
    auto& game = Game::getInstance();
    game.initialize(std::move(renderer), std::move(input_handler));
    game.start();
    return 0;
}
