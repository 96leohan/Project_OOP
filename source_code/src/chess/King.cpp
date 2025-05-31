#include "King.h"
#include "KingValidator.h"

King::King(Color color) : Piece(color, std::make_unique<KingValidator>()) {}

std::unique_ptr<Piece> King::clone() const {
    return std::make_unique<King>(color_);
}

std::string King::getSymbol() const {
    return (color_ == Color::White) ? "♔" : "♚";
}
