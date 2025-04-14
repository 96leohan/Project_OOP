#include "chess_board.h"
#include <iostream>

ChessBoard::ChessBoard()
    : _board(8, std::vector<std::unique_ptr<ChessPiece>>(8)),
      _currentTurn(Color::WHITE)
{
    initializeBoard();
}

void ChessBoard::initializeBoard()
{
    // This is a placeholder - in a complete implementation,
    // we would create actual piece instances here
    std::cout << "Chess board initialized (pieces would be placed in starting positions)" << std::endl;
}

void ChessBoard::display() const
{
    std::cout << "\n  a b c d e f g h\n";
    for (int i = 0; i < 8; i++)
    {
        std::cout << 8 - i << " ";
        for (int j = 0; j < 8; j++)
        {
            if (_board[i][j] == nullptr)
            {
                std::cout << (((i + j) % 2 == 0) ? "." : " ") << " ";
            }
            else
            {
                std::cout << _board[i][j]->getSymbol() << " ";
            }
        }
        std::cout << 8 - i << std::endl;
    }
    std::cout << "  a b c d e f g h\n";
}

ChessPiece *ChessBoard::getPiece(const Position &pos) const
{
    if (!pos.isValid())
        return nullptr;
    return _board[pos._row][pos._col].get();
}

bool ChessBoard::movePiece(const Position &from, const Position &to)
{
    ChessPiece *piece = getPiece(from);

    // Basic validations
    if (piece == nullptr || !to.isValid())
    {
        return false;
    }

    if (piece->getColor() != _currentTurn)
    {
        std::cout << "It's not your turn!" << std::endl;
        return false;
    }

    // Check if move is valid according to piece rules
    if (!piece->isValidMove(*this, to))
    {
        std::cout << "Invalid move for this piece!" << std::endl;
        return false;
    }

    // Move the piece
    auto movingPiece = std::move(_board[from._row][from._col]);
    _board[to._row][to._col] = std::move(movingPiece);
    piece->setPosition(to);

    // Switch turns
    _currentTurn = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return true;
}

Color ChessBoard::getCurrentTurn() const
{
    return _currentTurn;
}