// source_code/src/chess/PieceFactory.cpp
#include "PieceFactory.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

std::unique_ptr<Piece> PieceFactory::createPiece(PieceType type, Color color) {
    switch (type) {
        case PieceType::Pawn:
            return std::make_unique<Pawn>(color);
        case PieceType::Knight:
            return std::make_unique<Knight>(color);
        case PieceType::Bishop:
            return std::make_unique<Bishop>(color);
        case PieceType::Rook:
            return std::make_unique<Rook>(color);
        case PieceType::Queen:
            return std::make_unique<Queen>(color);
        case PieceType::King:
            return std::make_unique<King>(color);
        default:
            return nullptr;
    }
}
