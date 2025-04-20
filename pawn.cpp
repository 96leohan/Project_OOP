// pawn.cpp
#include "pawn.h"
#include "chess_board.h"
#include <cmath>

Pawn::Pawn(Color color, const Position &pos)
    : ChessPiece(PieceType::PAWN, color, pos), _hasMoved(false) {}

std::vector<Position> Pawn::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;
    int direction = (_color == Color::WHITE) ? -1 : 1; // White pawns move up (-1 in rows), black down (+1)

    // One square forward
    Position oneForward(_position._row + direction, _position._col);
    if (oneForward.isValid() && board.getPiece(oneForward) == nullptr)
    {
        moves.push_back(oneForward);

        // Two squares forward from starting position
        if (!_hasMoved)
        {
            Position twoForward(_position._row + 2 * direction, _position._col);
            if (twoForward.isValid() && board.getPiece(twoForward) == nullptr)
            {
                moves.push_back(twoForward);
            }
        }
    }

    // Capture diagonally
    for (int colOffset : {-1, 1})
    {
        Position capturePos(_position._row + direction, _position._col + colOffset);
        if (capturePos.isValid())
        {
            ChessPiece *pieceAtDest = board.getPiece(capturePos);
            if (pieceAtDest != nullptr && pieceAtDest->getColor() != _color)
            {
                moves.push_back(capturePos);
            }
        }
    }

    return moves;
}

bool Pawn::isValidMove(const ChessBoard &board, const Position &dest) const
{
    // Calculate move direction and distances
    int direction = (_color == Color::WHITE) ? -1 : 1;
    int rowDiff = dest._row - _position._row;
    int colDiff = dest._col - _position._col;

    // Forward movement (no capture)
    if (colDiff == 0)
    {
        // One square forward
        if (rowDiff == direction)
        {
            return board.getPiece(dest) == nullptr;
        }
        // Two squares forward from starting position
        else if (rowDiff == 2 * direction && !_hasMoved)
        {
            Position intermediate(_position._row + direction, _position._col);
            return board.getPiece(intermediate) == nullptr && board.getPiece(dest) == nullptr;
        }
    }
    // Diagonal capture
    else if (std::abs(colDiff) == 1 && rowDiff == direction)
    {
        ChessPiece *pieceAtDest = board.getPiece(dest);
        return pieceAtDest != nullptr && pieceAtDest->getColor() != _color;
    }

    return false; // Invalid move
}

// phương thức để kiểm tra phong cấp
bool Pawn::canPromote() const
{
    // Quân tốt trắng đến hàng 0 hoặc quân tốt đen đến hàng 7
    return (_color == Color::WHITE && _position._row == 0) ||
           (_color == Color::BLACK && _position._row == 7);
}