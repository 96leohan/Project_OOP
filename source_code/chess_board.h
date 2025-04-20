// update chesboard implementation
//  Cập nhật chess_board.h để thêm các include cần thiết
#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <string>
#include <memory>
#include "chess_piece.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

class ChessBoard
{
private:
    std::vector<std::vector<std::unique_ptr<ChessPiece>>> _board;
    Color _currentTurn;
    bool _gameOver;

    // Helper methods
    bool isInCheck(Color color) const;
    bool isCheckmate(Color color) const;

public:
    ChessBoard();
    ~ChessBoard() = default;

    void initializeBoard();
    void display() const;

    ChessPiece *getPiece(const Position &pos) const;
    bool movePiece(const Position &from, const Position &to);
    Color getCurrentTurn() const;
    bool isGameOver() const;
    void promotePawn(const Position &pos);
};

#endif // CHESS_BOARD_H
