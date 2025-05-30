#include "Game.h"
#include "PlayingState.h"
#include "MoveCommand.h"
#include <iostream>

void Game::initialize(std::unique_ptr<ui::Renderer> renderer, std::unique_ptr<ui::InputHandler> input_handler) {
    renderer_ = std::move(renderer);
    input_handler_ = std::move(input_handler);
    board_ = std::make_unique<Board>();
    board_->initializeBoard();
    state_ = std::make_unique<PlayingState>();
}

void Game::addNotifier(std::shared_ptr<UINotifier> notifier) {
    notifiers_.push_back(notifier);
}

void Game::executeCommand(std::unique_ptr<Command> command) {
    command->execute();
    command_history_.push(std::move(command));
}

void Game::undoLastMove() {
    if (!command_history_.empty()) {
        command_history_.top()->undo();
        command_history_.pop();
    }
}

void Game::setState(std::unique_ptr<GameState> state) {
    state_ = std::move(state);
}

void Game::switchTurn() {
    currentTurn_ = (currentTurn_ == Color::White) ? Color::Black : Color::White;
}

void Game::updateState() {
    state_->handle(*this);
}

void Game::start() {
    while (true) {
        renderer_->render(*board_);
        std::cout << "State: " << state_->getStateName() << "\n";
        if (state_->getStateName() == "Checkmate") {
            break;
        }
        std::cout << (currentTurn_ == Color::White ? "White" : "Black") << "'s turn\n";
        auto [from, to] = input_handler_->getMove();
        try {
            auto piece = board_->getPiece(from);
            if (!piece || piece->getColor() != currentTurn_) {
                std::cerr << "Invalid piece selection for this turn!\n";
                continue;
            }
            auto command = std::make_unique<MoveCommand>(*board_, from, to);
            if (board_->isValidMove(from, to)) {
                executeCommand(std::move(command));
                for (auto& notifier : notifiers_) {
                    notifier->notifyMove(from, to);
                }
                renderer_->highlightMove(from, to);
                switchTurn();
                updateState();
            } else {
                std::cerr << "Invalid move!\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}
