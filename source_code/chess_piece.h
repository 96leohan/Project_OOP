// Lưu ý rằng chúng ta cần triển khai các lớp quân cờ cụ thể (Tốt, Mã, v.v.) kế thừa từ lớp cơ sở ChessPiece để làm cho trò chơi hoạt động đầy đủ.

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <vector>
#include <string>
#include "position.h"

// Forward declaration
class ChessBoard;

enum class PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum class Color
{
    WHITE,
    BLACK
};

class ChessPiece
{
protected:
    PieceType _type;
    Color _color;
    Position _position;

public:
    ChessPiece(PieceType type, Color color, const Position &pos);
    virtual ~ChessPiece() = default;

    virtual std::vector<Position> getPossibleMoves(const ChessBoard &board) const = 0;
    virtual bool isValidMove(const ChessBoard &board, const Position &dest) const = 0;

    PieceType getType() const;
    Color getColor() const;
    Position getPosition() const;

    void setPosition(const Position &pos);
    char getSymbol() const;
};

#endif // CHESS_PIECE_H