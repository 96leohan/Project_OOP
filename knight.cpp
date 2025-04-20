
// knight.cpp
#include "knight.h"
#include "chess_board.h"
#include <cmath>

Knight::Knight(Color color, const Position &pos)
    : ChessPiece(PieceType::KNIGHT, color, pos) {}

std::vector<Position> Knight::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // All possible knight moves (L-shape: 2 squares in one direction, 1 square perpendicular)
    const int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (const auto &move : knightMoves)
    {
        Position newPos(_position._row + move[0], _position._col + move[1]);
        if (newPos.isValid())
        {
            ChessPiece *pieceAtDest = board.getPiece(newPos);
            if (pieceAtDest == nullptr || pieceAtDest->getColor() != _color)
            {
                moves.push_back(newPos);
            }
        }
    }

    return moves;
}

bool Knight::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = std::abs(dest._row - _position._row);
    int colDiff = std::abs(dest._col - _position._col);

    // Knight moves in L-shape: 2 squares in one direction and 1 in perpendicular
    bool isKnightMove = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);

    if (!isKnightMove)
    {
        return false;
    }

    // Check destination: empty or opponent's piece
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color;
}
