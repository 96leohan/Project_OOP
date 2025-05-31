#include "Bishop.h"
#include "BishopValidator.h"

Bishop::Bishop(Color color) : Piece(color, std::make_unique<BishopValidator>()) {}

std::unique_ptr<Piece> Bishop::clone() const {
    return std::make_unique<Bishop>(color_);
}

std::string Bishop::getSymbol() const {
    return (color_ == Color::White) ? "♗" : "♝";
}
