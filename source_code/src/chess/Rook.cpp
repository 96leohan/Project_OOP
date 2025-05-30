#include "Rook.h"
#include "RookValidator.h"

Rook::Rook(Color color) : Piece(color, std::make_unique<RookValidator>()) {}

std::unique_ptr<Piece> Rook::clone() const {
    return std::make_unique<Rook>(color_);
}

std::string Rook::getSymbol() const {
    return (color_ == Color::White) ? "♖" : "♜";
}
