#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Color color);
    std::unique_ptr<Piece> clone() const override;
    std::string getSymbol() const override;
};
