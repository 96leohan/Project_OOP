#pragma once
#include "../chess/Board.h"
#include <memory>

namespace ui {
    class Renderer {
    public:
        virtual ~Renderer() = default;
        virtual void render(const Board& board) = 0;
        virtual void highlightMove(const Position& from, const Position& to) = 0;
    };
}
