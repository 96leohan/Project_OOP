#ifndef KING_H
#define KING_H

#include "chess_piece.h"

class King : public ChessPiece
{
public:
    bool _hasMoved;

    King(Color color, const Position &pos);

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;
    bool hasMoved() const;

    // Các phương thức cho nhập thành
    bool canCastleKingside(const ChessBoard &board) const;
    bool canCastleQueenside(const ChessBoard &board) const;
    bool isCastlingMove(const Position &dest) const;
};

#endif