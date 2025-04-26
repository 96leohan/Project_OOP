#ifndef KING_H
#define KING_H

#include "chess_piece.h"

// Định nghĩa lớp King (Vua), kế thừa từ lớp ChessPiece
class King : public ChessPiece
{
public:
    bool _hasMoved; // Biến để theo dõi xem vua đã di chuyển hay chưa (quan trọng cho nhập thành)

    // Hàm constructor của lớp King
    King(Color color, const Position &pos);

    // Phương thức ghi đè (override) từ lớp cơ sở ChessPiece để lấy tất cả các nước đi có thể của vua
    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    // Phương thức ghi đè để kiểm tra xem một nước đi cụ thể của vua có hợp lệ không
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;
    // Phương thức để kiểm tra xem vua đã di chuyển hay chưa
    bool hasMoved() const;

    // Các phương thức liên quan đến nhập thành (castling)
    bool canCastleKingside(const ChessBoard &board) const;  // Kiểm tra xem có thể nhập thành cánh vua không
    bool canCastleQueenside(const ChessBoard &board) const; // Kiểm tra xem có thể nhập thành cánh hậu không
    bool isCastlingMove(const Position &dest) const;        // Kiểm tra xem một nước đi đến vị trí đích có phải là nhập thành không
};

#endif