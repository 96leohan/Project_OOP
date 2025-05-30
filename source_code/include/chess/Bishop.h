#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Color color);
    std::unique_ptr<Piece> clone() const override;
    std::string getSymbol() const override;
};
