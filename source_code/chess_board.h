#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <string>
#include "chess_piece.h"

class ChessBoard
{
private:
    std::vector<std::vector<std::unique_ptr<ChessPiece>>> _board;
    Color _currentTurn;

public:
    ChessBoard();
    ~ChessBoard() = default;

    void initializeBoard();
    void display() const;

    ChessPiece *getPiece(const Position &pos) const;
    bool movePiece(const Position &from, const Position &to);
    Color getCurrentTurn() const;
};

#endif // CHESS_BOARD_H