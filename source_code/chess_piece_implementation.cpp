#include "chess_piece.h"
#include <cctype>

// Định nghĩa hàm tạo (constructor) của lớp ChessPiece
ChessPiece::ChessPiece(PieceType type, Color color, const Position &pos)
    : _type(type),   // Khởi tạo kiểu quân cờ
      _color(color), // Khởi tạo màu của quân cờ
      _position(pos)
{
} // Khởi tạo vị trí của quân cờ

// Định nghĩa hàm getType để lấy kiểu của quân cờ
PieceType ChessPiece::getType() const
{
    return _type; // Trả về kiểu quân cờ (PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING)
}

// Định nghĩa hàm getColor để lấy màu của quân cờ
Color ChessPiece::getColor() const
{
    return _color; // Trả về màu của quân cờ (WHITE hoặc BLACK)
}

// Định nghĩa hàm getPosition để lấy vị trí hiện tại của quân cờ
Position ChessPiece::getPosition() const
{
    return _position; // Trả về đối tượng Position chứa hàng và cột của quân cờ
}

// Định nghĩa hàm setPosition để đặt vị trí mới cho quân cờ
void ChessPiece::setPosition(const Position &pos)
{
    _position = pos; // Cập nhật vị trí hiện tại của quân cờ
}

// Định nghĩa hàm getSymbol để lấy ký hiệu đại diện cho quân cờ (cho hiển thị bàn cờ)
char ChessPiece::getSymbol() const
{
    char symbol;   // Biến để lưu trữ ký hiệu
    switch (_type) // Dựa vào kiểu quân cờ để gán ký hiệu tương ứng
    {
    case PieceType::PAWN:
        symbol = 'P'; // Tốt
        break;
    case PieceType::KNIGHT:
        symbol = 'N'; // Mã (viết tắt của Knight)
        break;
    case PieceType::BISHOP:
        symbol = 'B'; // Tượng
        break;
    case PieceType::ROOK:
        symbol = 'R'; // Xe
        break;
    case PieceType::QUEEN:
        symbol = 'Q'; // Hậu
        break;
    case PieceType::KING:
        symbol = 'K'; // Vua
        break;
    default:
        symbol = '?'; // Ký hiệu mặc định nếu kiểu quân cờ không xác định
    }
    // Trả về ký hiệu. Nếu quân cờ màu trắng, trả về chữ hoa. Nếu màu đen, trả về chữ thường.
    return _color == Color::WHITE ? symbol : std::tolower(symbol);
}