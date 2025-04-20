
// bishop.cpp
#include "bishop.h"
#include "chess_board.h"
#include <cmath>

Bishop::Bishop(Color color, const Position &pos)
    : ChessPiece(PieceType::BISHOP, color, pos) {}

std::vector<Position> Bishop::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // Four diagonal directions
    const int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (const auto &dir : directions)
    {
        for (int i = 1; i < 8; ++i)
        { // Maximum 7 squares in any direction
            Position newPos(_position._row + i * dir[0], _position._col + i * dir[1]);
            if (!newPos.isValid())
            {
                break; // Off the board
            }

            ChessPiece *pieceAtDest = board.getPiece(newPos);
            if (pieceAtDest == nullptr)
            {
                moves.push_back(newPos); // Empty square
            }
            else
            {
                if (pieceAtDest->getColor() != _color)
                {
                    moves.push_back(newPos); // Capture opponent's piece
                }
                break; // Can't move beyond a piece
            }
        }
    }

    return moves;
}

bool Bishop::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = dest._row - _position._row;
    int colDiff = dest._col - _position._col;

    // Bishop moves only diagonally (equal row and column change)
    if (std::abs(rowDiff) != std::abs(colDiff) || (rowDiff == 0 && colDiff == 0))
    {
        return false;
    }

    // Check if path is clear
    int rowStep = (rowDiff > 0) ? 1 : -1;
    int colStep = (colDiff > 0) ? 1 : -1;

    for (int i = 1; i < std::abs(rowDiff); ++i)
    {
        Position checkPos(_position._row + i * rowStep, _position._col + i * colStep);
        if (board.getPiece(checkPos) != nullptr)
        {
            return false; // Path is blocked
        }
    }

    // Check destination: empty or opponent's piece
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color;
}
