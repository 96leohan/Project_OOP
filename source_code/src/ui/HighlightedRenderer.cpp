#include "HighlightedRenderer.h"
#include <iostream>

ui::HighlightedRenderer::HighlightedRenderer(std::unique_ptr<Renderer> renderer)
    : wrapped_renderer_(std::move(renderer)), has_last_move_(false) {}

void ui::HighlightedRenderer::render(const Board& board) {
    wrapped_renderer_->render(board);
    if (has_last_move_) {
        std::cout << "Last move highlighted: " << last_from_.toString() << " -> " << last_to_.toString() << "\n";
    }
}

void ui::HighlightedRenderer::highlightMove(const Position& from, const Position& to) {
    wrapped_renderer_->highlightMove(from, to);
    last_from_ = from;
    last_to_ = to;
    has_last_move_ = true;
}
