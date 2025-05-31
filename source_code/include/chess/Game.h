// source_code/include/chess/Game.h
#pragma once
#include "Board.h"
#include "ui/Renderer.h"
#include "ui/InputHandler.h"
#include "UINotifier.h"
#include "GameState.h"
#include "Command.h"
#include <memory>
#include <vector>
#include <stack>

class Game {
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    void initialize(std::unique_ptr<ui::Renderer> renderer, std::unique_ptr<ui::InputHandler> input_handler);
    void addNotifier(std::shared_ptr<UINotifier> notifier);
    void start();
    void executeCommand(std::unique_ptr<Command> command);
    void undoLastMove();
    void setState(std::unique_ptr<GameState> state);
    Color getCurrentTurn() const { return currentTurn_; }
    Board& getBoard() { return *board_; }

private:
    Game() : currentTurn_(Color::White) {}
    std::unique_ptr<Board> board_;
    std::unique_ptr<ui::Renderer> renderer_;
    std::unique_ptr<ui::InputHandler> input_handler_;
    std::vector<std::shared_ptr<UINotifier>> notifiers_;
    std::stack<std::unique_ptr<Command>> command_history_;
    std::unique_ptr<GameState> state_;
    Color currentTurn_;
    void switchTurn();
    void updateState();
};
