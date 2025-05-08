// knight.h
#ifndef KNIGHT_H
#define KNIGHT_H

#include "chess_piece.h"
#include <vector>

class Knight : public ChessPiece
{
public:
    Knight(Color color, const Position &pos);

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;
};

#endif