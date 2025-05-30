// chess_board.h
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
#include "move_history.h"

class ChessBoard
{
private:
    std::vector<std::vector<std::unique_ptr<ChessPiece>>> _board;
    Color _currentTurn;
    bool _gameOver;
    MoveHistory _moveHistory;

    // Các phương thức hỗ trợ
    bool checkGameEndConditions() const; // Renamed from isGameOver()
    bool isCheckmate(Color color);
    bool isStalemate(Color color);

public:
    ChessBoard();
    ~ChessBoard() = default;
    // Copy constructor
    ChessBoard(const ChessBoard &other);
    // Assignment operator
    ChessBoard &operator=(const ChessBoard &other);

    void initializeBoard();
    void display() const;

    ChessPiece *getPiece(const Position &pos) const;
    bool movePiece(const Position &from, const Position &to);
    Color getCurrentTurn() const;
    bool isGameOver() const; // Public interface
    void promotePawn(const Position &pos);

    // Phương thức hỗ trợ để lấy tất cả vị trí có quân cờ của một màu
    std::vector<Position> getAllPiecesPositions(Color color) const;

    // Phương thức hỗ trợ để lấy tất cả nước đi có thể của một quân cờ
    std::vector<Position> getAllPossibleMoves(const Position &from) const;

    // Các phương thức liên quan đến lịch sử nước đi
    void displayMoveHistory(bool detailed = false) const;
    bool saveMoveHistory(const std::string &filename) const;
    void clearMoveHistory();
    const MoveHistory &getMoveHistory() const;

    // Additional helper methods that might be missing
    bool isInCheck(Color color) const; // Likely needed for the implementation
};

#endif // CHESS_BOARD_H
