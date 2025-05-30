#pragma once
#include "Piece.h"
#include <memory>

class PieceFactory {
public:
    static std::unique_ptr<Piece> createPiece(PieceType type, Color color);
};
