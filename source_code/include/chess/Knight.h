#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(Color color);
    std::unique_ptr<Piece> clone() const override;
    std::string getSymbol() const override;
};
