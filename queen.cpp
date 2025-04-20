
// queen.cpp
#include "queen.h"
#include "chess_board.h"
#include <cmath>

Queen::Queen(Color color, const Position &pos)
    : ChessPiece(PieceType::QUEEN, color, pos) {}

std::vector<Position> Queen::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // Eight directions: horizontally, vertically, and diagonally
    const int directions[8][2] = {
        {-1, 0}, {0, 1}, {1, 0}, {0, -1}, // Rook-like moves
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1} // Bishop-like moves
    };

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

bool Queen::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = dest._row - _position._row;
    int colDiff = dest._col - _position._col;

    // Queen moves horizontally, vertically, or diagonally
    bool isHorizontalOrVertical = (rowDiff == 0 && colDiff != 0) || (rowDiff != 0 && colDiff == 0);
    bool isDiagonal = std::abs(rowDiff) == std::abs(colDiff) && rowDiff != 0;

    if (!isHorizontalOrVertical && !isDiagonal)
    {
        return false;
    }

    // Check if path is clear
    int rowStep, colStep;
    if (rowDiff == 0)
    {
        rowStep = 0;
        colStep = (colDiff > 0) ? 1 : -1;
    }
    else if (colDiff == 0)
    {
        rowStep = (rowDiff > 0) ? 1 : -1;
        colStep = 0;
    }
    else
    {
        // Diagonal move
        rowStep = (rowDiff > 0) ? 1 : -1;
        colStep = (colDiff > 0) ? 1 : -1;
    }

    int steps = std::max(std::abs(rowDiff), std::abs(colDiff));
    for (int i = 1; i < steps; ++i)
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
