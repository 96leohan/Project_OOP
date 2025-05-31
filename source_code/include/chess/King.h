#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(Color color);
    std::unique_ptr<Piece> clone() const override;
    std::string getSymbol() const override;
};
