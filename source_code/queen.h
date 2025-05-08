// queen.h
#ifndef QUEEN_H
#define QUEEN_H

#include "chess_piece.h"
#include <vector>
class Queen : public ChessPiece
{
public:
    Queen(Color color, const Position &pos);

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;
};

#endif