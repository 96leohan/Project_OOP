#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <vector>     // Cần thiết cho std::vector để lưu trữ các nước đi có thể
#include <string>     // Có thể cần thiết cho các thao tác chuỗi (hiện tại không dùng trực tiếp trong header này)
#include "position.h" // Bao gồm định nghĩa của lớp Position để biểu diễn vị trí trên bàn cờ

// Forward declaration (khai báo trước)
class ChessBoard; // Khai báo trước lớp ChessBoard vì ChessPiece có các phương thức cần tham chiếu đến ChessBoard

// Định nghĩa enum PieceType để biểu thị các loại quân cờ
enum class PieceType
{
    PAWN,   // Tốt
    KNIGHT, // Mã
    BISHOP, // Tượng
    ROOK,   // Xe
    QUEEN,  // Hậu
    KING    // Vua
};

// Định nghĩa enum Color để biểu thị màu của quân cờ
enum class Color
{
    WHITE, // Trắng
    BLACK  // Đen
};

// Định nghĩa lớp cơ sở ChessPiece (quân cờ)
class ChessPiece
{
protected:
    PieceType _type;    // Kiểu của quân cờ (ví dụ: TỐT, MÃ, ...)
    Color _color;       // Màu của quân cờ (TRẮNG hoặc ĐEN)
    Position _position; // Vị trí hiện tại của quân cờ trên bàn cờ

public:
    // Hàm tạo (constructor) của lớp ChessPiece
    ChessPiece(PieceType type, Color color, const Position &pos);
    // Hàm hủy ảo (virtual destructor) để đảm bảo giải phóng tài nguyên đúng cách khi làm việc với con trỏ đến lớp cơ sở
    virtual ~ChessPiece() = default;

    // Phương thức ảo thuần túy (pure virtual function) để lấy tất cả các nước đi có thể của quân cờ
    // Các lớp con (Tốt, Mã, ...) sẽ phải triển khai phương thức này
    virtual std::vector<Position> getPossibleMoves(const ChessBoard &board) const = 0;

    // Phương thức ảo thuần túy để kiểm tra xem một nước đi đến vị trí đích có hợp lệ không
    // Các lớp con sẽ triển khai logic di chuyển cụ thể của từng loại quân cờ
    virtual bool isValidMove(const ChessBoard &board, const Position &dest) const = 0;

    // Các phương thức getter để lấy thông tin của quân cờ
    PieceType getType() const;    // Lấy kiểu của quân cờ
    Color getColor() const;       // Lấy màu của quân cờ
    Position getPosition() const; // Lấy vị trí hiện tại của quân cờ

    // Phương thức setter để đặt vị trí mới cho quân cờ
    void setPosition(const Position &pos);
    // Phương thức để lấy ký hiệu đại diện cho quân cờ (ví dụ: 'P' cho tốt trắng, 'p' cho tốt đen)
    char getSymbol() const;
};

#endif // CHESS_PIECE_H