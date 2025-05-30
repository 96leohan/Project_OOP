#pragma once
#include "Board.h"
#include "ui/Renderer.h"
#include "ui/InputHandler.h"
#include "UINotifier.h"
#include <memory>
#include <vector>

class Game {
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    void initialize(std::unique_ptr<ui::Renderer> renderer, std::unique_ptr<ui::InputHandler> input_handler);
    void addNotifier(std::shared_ptr<UINotifier> notifier);
    void start();

private:
    Game() = default;
    std::unique_ptr<Board> board_;
    std::unique_ptr<ui::Renderer> renderer_;
    std::unique_ptr<ui::InputHandler> input_handler_;
    std::vector<std::shared_ptr<UINotifier>> notifiers_;
};
