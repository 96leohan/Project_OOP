
// bishop.h
#ifndef BISHOP_H
#define BISHOP_H

#include "chess_piece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(Color color, const Position &pos);

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;
};

#endif