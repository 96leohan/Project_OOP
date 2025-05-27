
// bishop.h
#ifndef BISHOP_H
#define BISHOP_H

#include "chess_piece.h"

class Bishop : public ChessPiece // Lớp Bishop kế thừa từ lớp ChessPiece.
{
public:
    Bishop(Color color, const Position &pos); // Constructor của lớp Bishop, nhận màu sắc và vị trí khởi tạo.

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    // Phương thức ghi đè (override) từ lớp cha ChessPiece.
    // Trả về một vector chứa tất cả các vị trí mà quân Tượng có thể di chuyển đến từ vị trí hiện tại trên bàn cờ đã cho.

    bool isValidMove(const ChessBoard &board, const Position &dest) const override;
    // Phương thức ghi đè từ lớp cha ChessPiece.
    // Kiểm tra xem một nước đi đến vị trí 'dest' trên bàn cờ 'board' có hợp lệ cho quân Tượng hiện tại hay không.
    // Trả về true nếu nước đi hợp lệ, false nếu không.
};
#endif