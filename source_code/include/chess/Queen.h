#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(Color color);
    std::unique_ptr<Piece> clone() const override;
    std::string getSymbol() const override;
};
