
#ifndef PAWN_H
#define PAWN_H

#include "chess_piece.h"

class Pawn : public ChessPiece
{
public:
    bool _hasMoved;
    bool _enPassantVulnerable;

    Pawn(Color color, const Position &pos);

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;

    // Kiểm tra nếu quân tốt đã đến hàng cuối cùng để phong cấp
    bool canPromote() const;
};

#endif