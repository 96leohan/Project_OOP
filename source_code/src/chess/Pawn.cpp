#include "Pawn.h"
#include "PawnValidator.h"

Pawn::Pawn(Color color) : Piece(color, std::make_unique<PawnValidator>(color)) {}

std::unique_ptr<Piece> Pawn::clone() const {
    return std::make_unique<Pawn>(color_);
}

std::string Pawn::getSymbol() const {
    return (color_ == Color::White) ? "♙" : "♟";
}
