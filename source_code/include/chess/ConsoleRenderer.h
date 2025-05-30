#pragma once
#include "Renderer.h"

namespace ui {
    class ConsoleRenderer : public Renderer {
    public:
        void render(const Board& board) override;
        void highlightMove(const Position& from, const Position& to) override;
    private:
        void clearScreen() const;
    };
}
