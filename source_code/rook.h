#ifndef ROOK_H
#define ROOK_H

#include "chess_piece.h"
#include <vector>

// Lớp Rook đại diện cho quân Xe trong cờ vua.
// Kế thừa từ lớp cơ sở ChessPiece.
class Rook : public ChessPiece
{
private:
    // Biến boolean để theo dõi xem quân Xe đã di chuyển lần nào chưa (cần cho việc nhập thành).
    bool _hasMoved;

public:
    // Constructor của lớp Rook, nhận màu sắc và vị trí khởi tạo.
    Rook(Color color, const Position &pos);

    // Phương thức ghi đè (override) từ lớp cơ sở ChessPiece.
    // Trả về một vector chứa tất cả các vị trí mà quân Xe có thể di chuyển đến từ vị trí hiện tại trên bàn cờ.
    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;

    // Phương thức ghi đè (override) từ lớp cơ sở ChessPiece.
    // Kiểm tra xem một nước đi cụ thể đến vị trí 'dest' có hợp lệ đối với quân Xe hay không.
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;

    // Phương thức trả về trạng thái đã di chuyển của quân Xe.
    bool hasMoved() const;

    // Phương thức setter để thiết lập trạng thái đã di chuyển của quân Xe.
    void setHasMoved(bool value) { _hasMoved = value; }
};

#endif