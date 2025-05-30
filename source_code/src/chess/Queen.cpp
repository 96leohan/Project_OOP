#include "Queen.h"
#include "QueenValidator.h"

Queen::Queen(Color color) : Piece(color, std::make_unique<QueenValidator>()) {}

std::unique_ptr<Piece> Queen::clone() const {
    return std::make_unique<Queen>(color_);
}

std::string Queen::getSymbol() const {
    return (color_ == Color::White) ? "♕" : "♛";
}
