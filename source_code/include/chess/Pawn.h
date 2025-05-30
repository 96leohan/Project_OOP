#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(Color color);
    std::unique_ptr<Piece> clone() const override;
    std::string getSymbol() const override;
};
