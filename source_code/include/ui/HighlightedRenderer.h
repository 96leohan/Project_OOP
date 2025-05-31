#pragma once
#include "Renderer.h"

namespace ui {
    class HighlightedRenderer : public Renderer {
    public:
        HighlightedRenderer(std::unique_ptr<Renderer> renderer);
        void render(const Board& board) override;
        void highlightMove(const Position& from, const Position& to) override;

    private:
        std::unique_ptr<Renderer> wrapped_renderer_;
        Position last_from_;
        Position last_to_;
        bool has_last_move_;
    };
}
