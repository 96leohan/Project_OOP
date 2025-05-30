#include "Game.h"
#include <iostream>

void Game::initialize(std::unique_ptr<ui::Renderer> renderer, std::unique_ptr<ui::InputHandler> input_handler) {
    renderer_ = std::move(renderer);
    input_handler_ = std::move(input_handler);
    board_ = std::make_unique<Board>();
    board_->initializeBoard();
}

void Game::addNotifier(std::shared_ptr<UINotifier> notifier) {
    notifiers_.push_back(notifier);
}

void Game::start() {
    while (true) {
        renderer_->render(*board_);
        auto [from, to] = input_handler_->getMove();
        try {
            if (board_->movePiece(from, to)) {
                for (auto& notifier : notifiers_) {
                    notifier->notifyMove(from, to);
                }
                renderer_->highlightMove(from, to);
            } else {
                std::cerr << "Invalid move!\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}
