// knight.cpp
#include "knight.h"
#include "chess_board.h"
#include <cmath>

// Constructor cho lớp Knight, nhận màu sắc và vị trí khởi tạo.
Knight::Knight(Color color, const Position &pos)
    : ChessPiece(PieceType::KNIGHT, color, pos) {}

// Phương thức trả về một vector chứa tất cả các vị trí mà quân Mã có thể di chuyển đến từ vị trí hiện tại trên bàn cờ.
std::vector<Position> Knight::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // Mảng chứa tất cả 8 khả năng di chuyển của quân Mã theo hình chữ L.
    // Mỗi phần tử là một cặp số nguyên biểu thị sự thay đổi về hàng và cột.
    const int knightMoves[8][2] = {
        {-2, -1}, // Lên 2, trái 1
        {-2, 1},  // Lên 2, phải 1
        {-1, -2}, // Lên 1, trái 2
        {-1, 2},  // Lên 1, phải 2
        {1, -2},  // Xuống 1, trái 2
        {1, 2},   // Xuống 1, phải 2
        {2, -1},  // Xuống 2, trái 1
        {2, 1}    // Xuống 2, phải 1
    };

    // Duyệt qua tất cả các khả năng di chuyển của quân Mã.
    for (const auto &move : knightMoves)
    {
        // Tính toán vị trí mới sau khi thực hiện một nước đi tiềm năng.
        Position newPos(_position._row + move[0], _position._col + move[1]);
        // Kiểm tra xem vị trí mới có nằm trong bàn cờ hay không.
        if (newPos.isValid())
        {
            // Lấy con cờ tại vị trí đích trên bàn cờ.
            ChessPiece *pieceAtDest = board.getPiece(newPos);
            // Kiểm tra xem ô đích có trống hay chứa quân cờ khác màu (để ăn quân đối phương).
            if (pieceAtDest == nullptr || pieceAtDest->getColor() != _color)
            {
                // Nếu điều kiện trên đúng, thì đây là một nước đi hợp lệ, thêm vị trí này vào vector các nước đi có thể.
                moves.push_back(newPos);
            }
        }
    }

    // Trả về vector chứa tất cả các nước đi hợp lệ của quân Mã.
    return moves;
}

// Phương thức kiểm tra xem một nước đi cụ thể đến vị trí 'dest' có hợp lệ đối với quân Mã hay không.
bool Knight::isValidMove(const ChessBoard &board, const Position &dest) const
{
    // Tính toán sự khác biệt tuyệt đối giữa hàng và cột của vị trí đích và vị trí hiện tại.
    int rowDiff = std::abs(dest._row - _position._row);
    int colDiff = std::abs(dest._col - _position._col);

    // Quân Mã di chuyển theo hình chữ L: 2 ô theo một hướng (ngang hoặc dọc) và 1 ô theo hướng vuông góc.
    bool isKnightMove = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);

    // Nếu không phải là nước đi hình chữ L, trả về false.
    if (!isKnightMove)
    {
        return false;
    }

    // Kiểm tra ô đích: phải trống hoặc chứa quân cờ khác màu.
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color;
}