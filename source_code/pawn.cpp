// pawn.cpp
#include "pawn.h"
#include "chess_board.h"
#include <cmath>

// Constructor cho lớp Pawn, nhận màu sắc và vị trí khởi tạo.
// Khởi tạo thêm biến _hasMoved để theo dõi xem quân tốt đã di chuyển lần nào chưa (cho phép đi 2 ô ở nước đầu).
Pawn::Pawn(Color color, const Position &pos)
    : ChessPiece(PieceType::PAWN, color, pos), _hasMoved(false) {}

// Phương thức trả về một vector chứa tất cả các vị trí mà quân tốt có thể di chuyển đến từ vị trí hiện tại trên bàn cờ.
std::vector<Position> Pawn::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;
    // Xác định hướng di chuyển của quân tốt dựa trên màu sắc.
    // Quân trắng đi lên (giảm số hàng), quân đen đi xuống (tăng số hàng).
    int direction = (_color == Color::WHITE) ? -1 : 1;

    // Nước đi một ô về phía trước (không ăn quân).
    Position oneForward(_position._row + direction, _position._col);
    // Kiểm tra xem vị trí phía trước có hợp lệ (trong bàn cờ) và có trống không.
    if (oneForward.isValid() && board.getPiece(oneForward) == nullptr)
    {
        moves.push_back(oneForward);

        // Nước đi hai ô về phía trước từ vị trí ban đầu (nếu quân tốt chưa di chuyển).
        if (!_hasMoved)
        {
            Position twoForward(_position._row + 2 * direction, _position._col);
            // Kiểm tra xem vị trí hai ô phía trước có hợp lệ và ô ở giữa cũng phải trống.
            if (twoForward.isValid() && board.getPiece(twoForward) == nullptr)
            {
                moves.push_back(twoForward);
            }
        }
    }

    // Nước đi ăn chéo (sang trái hoặc phải một ô).
    for (int colOffset : {-1, 1})
    {
        Position capturePos(_position._row + direction, _position._col + colOffset);
        // Kiểm tra xem vị trí ăn chéo có hợp lệ.
        if (capturePos.isValid())
        {
            // Lấy con cờ tại vị trí ăn chéo.
            ChessPiece *pieceAtDest = board.getPiece(capturePos);
            // Kiểm tra xem có quân cờ của đối phương ở đó không.
            if (pieceAtDest != nullptr && pieceAtDest->getColor() != _color)
            {
                moves.push_back(capturePos);
            }
        }
    }

    return moves;
}

// Phương thức kiểm tra xem một nước đi cụ thể đến vị trí 'dest' có hợp lệ đối với quân tốt hay không.
bool Pawn::isValidMove(const ChessBoard &board, const Position &dest) const
{
    // Tính toán hướng di chuyển và khoảng cách di chuyển theo hàng và cột.
    int direction = (_color == Color::WHITE) ? -1 : 1;
    int rowDiff = dest._row - _position._row;
    int colDiff = dest._col - _position._col;

    // Di chuyển thẳng về phía trước (không ăn quân).
    if (colDiff == 0)
    {
        // Đi một ô về phía trước.
        if (rowDiff == direction)
        {
            return board.getPiece(dest) == nullptr; // Ô đích phải trống.
        }
        // Đi hai ô về phía trước từ vị trí ban đầu.
        else if (rowDiff == 2 * direction && !_hasMoved)
        {
            // Kiểm tra xem cả ô ở giữa và ô đích đều trống.
            Position intermediate(_position._row + direction, _position._col);
            return board.getPiece(intermediate) == nullptr && board.getPiece(dest) == nullptr;
        }
    }
    // Ăn quân theo đường chéo.
    else if (std::abs(colDiff) == 1 && rowDiff == direction)
    {
        // Kiểm tra xem có quân cờ của đối phương ở ô đích không.
        ChessPiece *pieceAtDest = board.getPiece(dest);
        return pieceAtDest != nullptr && pieceAtDest->getColor() != _color;
    }

    return false; // Nước đi không hợp lệ.
}

// Phương thức để kiểm tra xem quân tốt có thể phong cấp ở vị trí hiện tại không.
bool Pawn::canPromote() const
{
    // Quân tốt trắng phong cấp khi đến hàng 0, quân tốt đen phong cấp khi đến hàng 7.
    return (_color == Color::WHITE && _position._row == 0) ||
           (_color == Color::BLACK && _position._row == 7);
}