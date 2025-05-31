#include "chess/Game.h"
#include "ui/RendererFactory.h"
#include "ui/ConsoleInputHandler.h"

int main() {
    auto renderer = ui::RendererFactory::createRenderer("highlighted");
    auto input_handler = std::make_unique<ui::ConsoleInputHandler>();
    auto& game = Game::getInstance();
    game.initialize(std::move(renderer), std::move(input_handler));
    game.start();
    return 0;
}
