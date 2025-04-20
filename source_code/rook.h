
#ifndef ROOK_H
#define ROOK_H

#include "chess_piece.h"

class Rook : public ChessPiece
{
private:
    bool _hasMoved;

public:
    Rook(Color color, const Position &pos);

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;
    bool hasMoved() const;
};

#endif