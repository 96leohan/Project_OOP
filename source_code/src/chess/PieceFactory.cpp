#include "PieceFactory.h"
#include "Pawn.h"

std::unique_ptr<Piece> PieceFactory::createPiece(PieceType type, Color color) {
    switch (type) {
        case PieceType::Pawn:
            return std::make_unique<Pawn>(color);
        // Add other piece types as needed
        default:
            return nullptr;
    }
}
