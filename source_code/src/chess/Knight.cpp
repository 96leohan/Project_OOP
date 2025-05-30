#include "Knight.h"
#include "KnightValidator.h"

Knight::Knight(Color color) : Piece(color, std::make_unique<KnightValidator>()) {}

std::unique_ptr<Piece> Knight::clone() const {
    return std::make_unique<Knight>(color_);
}

std::string Knight::getSymbol() const {
    return (color_ == Color::White) ? "♘" : "♞";
}
