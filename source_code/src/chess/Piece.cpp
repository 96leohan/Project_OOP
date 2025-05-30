#include "Piece.h"

Piece::Piece(Color color, std::unique_ptr<MoveValidator> validator)
    : color_(color), validator_(std::move(validator)) {}

bool Piece::validateMove(const Position& from, const Position& to, const Board& board) const {
    return validator_->isValid(from, to, board);
}
